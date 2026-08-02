/*
 * bootloader.c
 *
 * Project : HexBoot_F0_DMA_PingPong_IAP
 *
 * Description:
 * Implements the bootloader startup sequence.
 *
 * Responsibilities:
 * - Validate application metadata.
 * - Verify firmware integrity.
 * - Configure application stack pointer.
 * - Jump to the user application.
 *
 *  Created on: 26-Apr-2026
 *      Author: brajo
 */

/* MCU */
#include "stm32f030x8.h"

/* Drivers */
#include "uart.h"
#include "flash.h"
#include "crc.h"
#include "dma.h"

/* Bootloader */
#include "bootloader.h"
#include "metadata.h"
#include "slot_manager.h"
#include "firmware_receiver.h"
#include "firmware_pingpong.h"

/* BSP */
#include "delay.h"
#include "bsp.h"
#include "systick.h"

#include <stdio.h>

#define SYSCFG_EN				(1U << 0)
#define UPDATE_TIMEOUT_MS	5000U
#define DEBUG_UART_BAUDRATE		19200U



typedef enum
{
    BOOT_WAIT_HEADER,
    BOOT_RECEIVE_FIRMWARE,
    BOOT_VERIFY,
    BOOT_JUMP
} bootloader_state_t;



/* Boot State */
static volatile bootloader_state_t boot_state =  BOOT_WAIT_HEADER;
static slot_t target_slot = SLOT_NONE;

/* Firmware Information */
static uint16_t payload_length = 0;
static uint16_t expected_crc = 0;
static uint16_t calculated_crc = 0;

/* Flash Programming */
static uint16_t chunk_index;

/* Boot Management */
static uint32_t last_activity_tick = 0;
static uint8_t boot_failed = 0;


/* Private Types */
typedef void (*app_entry_t)(void);



/* Private Functions Prototypes */
static firmware_info_t firmware_get_info(slot_t slot);
static void print_slot(slot_t slot);
static void bootloader_state(void);
static void flash_handle_status(flash_status_t status);
static int is_valid_app(uint32_t addr);
static void relocate_vector_table(uint32_t app_address);
static void jmp_to_app(uint32_t app_address);
static void jump(void);


/*=============================================================
 * Public Functions
 *============================================================*/
void bootloader_init(void)
{
    debug_uart_init(DEBUG_UART_BAUDRATE);

    dma_init();

    firmware_pingpong_init(&fw_pingpong);

    metadata_init(&metadata);

    firmware_receiver_init();

    systick_init(1000);        // 1 ms tick

    last_activity_tick = systick_get_tick();

	println("bootloader init");
}



void bootloader_run(void)
{

	if (dma_get_transfer_complete())
	{
		last_activity_tick = systick_get_tick();
		dma_clear_transfer_complete();
		firmware_rx_process();
		if(firmware_rx_get_state() != DISCARD_PAYLOAD)
		{
			bootloader_state();
		}
	}

	if(dma_get_transfer_error())
	{
	    dma_clear_transfer_error();

	    println("DMA ERROR");

	}

	if ((!boot_failed) && (systick_get_tick() - last_activity_tick) >= UPDATE_TIMEOUT_MS)
	{
		slot_t boot_slot = slot_manager_select_boot_slot(&metadata);

		if (boot_slot == SLOT_NONE)
		{
		    println("No bootable application.");
		    boot_failed = 1;
		    return;
		}
		jump();
	}

	if(firmware_rx_get_state() == FW_COMPLETE)
	{
		bootloader_state();
	}
}



/*=============================================================
 * Private Functions
 *============================================================*/
static void bootloader_state(void){

	switch(boot_state)
	{
	case BOOT_WAIT_HEADER:


		target_slot = slot_manager_get_inactive_slot(&metadata);
		firmware_info_t fw = firmware_get_info(target_slot);

		payload_length = fw.payload_length;
		expected_crc = fw.crc;

		flash_status_t flash_status;
		flash_status = flash_erase(slot_manager_get_slot_address(target_slot), payload_length);
		flash_handle_status(flash_status);

		chunk_index = 0;
		boot_state = BOOT_RECEIVE_FIRMWARE;

		if(target_slot == SLOT_A)
		{
		    firmware_set_payload_info(payload_length_A, expected_crc_A);
		    firmware_rx_set_state(RECEIVE_PAYLOAD);
		}
		else
		{
		    firmware_set_payload_info(payload_length_B, expected_crc_B);
		    firmware_rx_set_state(DISCARD_PAYLOAD);
		}
	        break;



	case BOOT_RECEIVE_FIRMWARE:

		if (fw_pingpong.prog_ready)
		{
			fw_pingpong.prog_ready = 0;
			uint32_t flash_address = (slot_manager_get_slot_address(target_slot) + (chunk_index * CHUNK_SIZE));

			/* Program chunk */
			flash_status = flash_program( flash_address,(uint16_t*)fw_pingpong.prog_buffer , ((program_chunk_size + 1)/2));
			flash_handle_status(flash_status);
			chunk_index++;
		}

		if (firmware_rx_get_state() == FW_COMPLETE){
			boot_state = BOOT_VERIFY;

		}
	        break;



	case BOOT_VERIFY:

		calculated_crc = crc16_calculate((uint8_t*)slot_manager_get_slot_address(target_slot), payload_length);

		if (calculated_crc == expected_crc) {
			println("CRC verified successfully");
			boot_state = BOOT_JUMP;
		}
		else	{
			println("CRC verification failed");
			while(1);
		}

	        break;



	case BOOT_JUMP:
	/*----------    WRITING META DATA    ---------*/
			slot_info_t *slot_info = slot_manager_get_slot_info(&metadata, target_slot);
			slot_info->confirmed = 1;
			slot_info->crc = calculated_crc;
			slot_info->is_valid = 1;
			slot_info->size = payload_length;
			slot_info->version ++ ;
			metadata.active_slot = target_slot;
			metadata.boot_state = BOOT_NORMAL;

			metadata_save(&metadata);

			jump();

	        break;
	}
}




static void flash_handle_status(flash_status_t status)
{
	switch(status)
	{
	case FLASH_OK:

		break;

	case FLASH_ERROR:
		println("FLASH_ERROR");
		break;

	case FLASH_TIMEOUT:
		println("FLASH_TIMEOUT");
		break;

	default:
		println("UNKNOWN_FLASH_STATE");
	}
}



static firmware_info_t firmware_get_info(slot_t slot)
{
    firmware_info_t info;

    switch(slot)
    			{
    			case SLOT_A:
    				info.payload_length = payload_length_A;
    				info.crc = expected_crc_A;
    			    break;

    			case SLOT_B:
    				info.payload_length = payload_length_B;
    				info.crc = expected_crc_B;
    			    break;

    			default:
    			    info.payload_length = 0;
    			    info.crc = 0;
    			    break;
    			}

    return info;
}



static void print_slot(slot_t slot){
    if (slot == SLOT_A)
    {
        println("Boot Slot  : A");
    }
    else
    {
        println("Boot Slot : B");
    }
}



static void jmp_to_app(uint32_t app_address)
{
	app_entry_t jump_to_app;
	delay_ms(300);

	if (is_valid_app(app_address))
	{

		__disable_irq();
		relocate_vector_table(app_address);

		/*Initialize main stack pointer */
		__set_MSP(*(uint32_t*) app_address);

		uint32_t app_start_address = *(uint32_t*) (app_address + 4);
		jump_to_app = (app_entry_t) (app_start_address);

		/*jump*/
		jump_to_app();

		println("jump fail");
		while (1);//Fail-safe design(If execution ever comes back, CPU gets stuck here safely)
	}
	else
	{
		println("No valid application found");
	}
}



static int is_valid_app(uint32_t addr)
{
	uint32_t msp = *(uint32_t*) addr;
	uint32_t reset = *(uint32_t*) (addr + 4);

	// MSP must be in SRAM
	if (msp < SRAM_START || msp > SRAM_END)
	{
		return 0;
	}

	// MSP must be aligned to 32 bit(4 byte)
	if (msp % 4)
	{
		return 0;
	}
	// Reset handler must be in Flash
	if (reset < FLASH_START || reset > FLASH_END)
	{
		return 0;
	}
	// Thumb bit check(Cortex-M supports only Thumb mode, Function address must have LSB=1)
	if ((reset & 1) == 0)
	{
		return 0;
	}

	return 1;
}



static void relocate_vector_table(uint32_t app_address)
{
	uint32_t *src = (uint32_t*) app_address;
	uint32_t *dst = (uint32_t*) SRAM_START;

	for (uint32_t i = 0; i < VECTOR_COUNT; i++) {   // copying of vectors
		dst[i] = src[i];
	}

	RCC->APB2ENR |= SYSCFG_EN;
	SYSCFG->CFGR1 &= ~(3 << 0);
	SYSCFG->CFGR1 |= (3 << 0);   // SRAM mapped at 0x00000000

	__DSB();   // Data Synchronization Barrier
	__ISB();   // Instruction Synchronization Barrier
}



static void jump(void){
    slot_t boot_slot = slot_manager_select_boot_slot(&metadata);

    print_slot(boot_slot);

    if (boot_slot == SLOT_NONE)
    {
        println("No bootable application.");
        return;
    }

    uint32_t app_address = slot_manager_get_slot_address(boot_slot);

    jmp_to_app(app_address);
}

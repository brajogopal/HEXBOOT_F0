/*
 * dma.c
 *
 * DMA driver.
 */

#include "stm32f030x8.h"

#include "dma.h"


/* Reception Status */
static volatile uint8_t dma_transfer_complete = 0;
static volatile uint8_t dma_transfer_error = 0;


/******************************************************************************
 * Public Functions
 ******************************************************************************/
void dma_init(void)
{
RCC->AHBENR |= RCC_DMA_EN;
USART2->CR3 |= USART_DMA_RE;
/*
 * To configure DMA Channel
 * DMA1_CSELR &= ~(0xFUL << 16U);
 * DMA1_CSELR |=  (0x9UL << 16U); // [1001] - To dedicate channel 5 to USART2_ RX
*/
DMA1_Channel5->CPAR = (uint32_t)(&(USART2->RDR));
DMA1_Channel5->CCR |= DMA_CCR_MINC | DMA_CCR_TEIE | DMA_CCR_TCIE ;

/* Configure NVIC for DMA */
/* (1) Enable Interrupt on DMA Channel 5 */
/* (2) Set priority for DMA Channel 5 */
NVIC_EnableIRQ(DMA1_Channel4_5_IRQn); /* (1) */
NVIC_SetPriority(DMA1_Channel4_5_IRQn, 0); /* (2) */
}



/*
 * Start a DMA reception.
 */
void dma_receive(void *buffer, uint16_t size)
{
	__disable_irq();

	DMA1_Channel5->CCR &= ~DMA_EN;

	DMA1_Channel5->CMAR = (uint32_t)buffer;
	DMA1_Channel5->CNDTR = size;

	DMA1_Channel5->CCR |= DMA_EN;

	__enable_irq();
}


uint8_t dma_get_transfer_complete(void)
{
    return dma_transfer_complete;
}

void dma_clear_transfer_complete(void)
{
    dma_transfer_complete = 0;
}

uint8_t dma_get_transfer_error(void)
{
	return dma_transfer_error;
}

void dma_clear_transfer_error(void)
{
	dma_transfer_error = 0;
}


void DMA1_CH4_5_IRQHandler(void)
{
    if(DMA1->ISR & DMA_ISR_TCIF5)
    {
        DMA1->IFCR |= DMA_IFCR_CGIF5;
        dma_transfer_complete = 1;
    }

    if(DMA1->ISR & DMA_ISR_TEIF5)
    {
    	dma_transfer_error = 1;
        DMA1->IFCR |= DMA_IFCR_CGIF5;
    }
}

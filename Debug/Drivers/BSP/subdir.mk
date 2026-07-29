################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/bsp.c 

OBJS += \
./Drivers/BSP/bsp.o 

C_DEPS += \
./Drivers/BSP/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/%.o Drivers/BSP/%.su Drivers/BSP/%.cyclo: ../Drivers/BSP/%.c Drivers/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F0 -DSTM32F030C8Tx -c -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Core/Inc" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/CMSIS/Device/ST/STM32F0xx/Include" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/CMSIS/Include" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Bootloader/Boot" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Bootloader/Common" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Bootloader/Metadata" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Bootloader/Receiver" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Bootloader/Slot" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Bootloader/Update" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Drivers/BSP" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Drivers/CRC" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Drivers/DMA" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Drivers/FLASH" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Drivers/GPIO" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Drivers/RCC" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Drivers/SYSTICK" -I"C:/Users/brajo/OneDrive/Desktop/Github/HEXBOOT_F0/Drivers/UART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP

clean-Drivers-2f-BSP:
	-$(RM) ./Drivers/BSP/bsp.cyclo ./Drivers/BSP/bsp.d ./Drivers/BSP/bsp.o ./Drivers/BSP/bsp.su

.PHONY: clean-Drivers-2f-BSP


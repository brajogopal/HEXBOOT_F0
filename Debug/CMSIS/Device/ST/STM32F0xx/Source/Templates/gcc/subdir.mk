################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x8.s 

OBJS += \
./CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x8.o 

S_DEPS += \
./CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x8.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/%.o: ../CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/%.s CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-CMSIS-2f-Device-2f-ST-2f-STM32F0xx-2f-Source-2f-Templates-2f-gcc

clean-CMSIS-2f-Device-2f-ST-2f-STM32F0xx-2f-Source-2f-Templates-2f-gcc:
	-$(RM) ./CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x8.d ./CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f030x8.o

.PHONY: clean-CMSIS-2f-Device-2f-ST-2f-STM32F0xx-2f-Source-2f-Templates-2f-gcc


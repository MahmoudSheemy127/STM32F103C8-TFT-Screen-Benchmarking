################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Drivers/SPI/SPI.c 

OBJS += \
./Src/Drivers/SPI/SPI.o 

C_DEPS += \
./Src/Drivers/SPI/SPI.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Drivers/SPI/%.o: ../Src/Drivers/SPI/%.c Src/Drivers/SPI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Drivers-2f-SPI

clean-Src-2f-Drivers-2f-SPI:
	-$(RM) ./Src/Drivers/SPI/SPI.d ./Src/Drivers/SPI/SPI.o

.PHONY: clean-Src-2f-Drivers-2f-SPI


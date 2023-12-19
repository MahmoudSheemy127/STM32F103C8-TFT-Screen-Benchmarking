################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/CortexM3/Cortex_M3_Core.c \
../Src/CortexM3/SYSTICK_M3.c 

OBJS += \
./Src/CortexM3/Cortex_M3_Core.o \
./Src/CortexM3/SYSTICK_M3.o 

C_DEPS += \
./Src/CortexM3/Cortex_M3_Core.d \
./Src/CortexM3/SYSTICK_M3.d 


# Each subdirectory must supply rules for building sources it contributes
Src/CortexM3/%.o: ../Src/CortexM3/%.c Src/CortexM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-CortexM3

clean-Src-2f-CortexM3:
	-$(RM) ./Src/CortexM3/Cortex_M3_Core.d ./Src/CortexM3/Cortex_M3_Core.o ./Src/CortexM3/SYSTICK_M3.d ./Src/CortexM3/SYSTICK_M3.o

.PHONY: clean-Src-2f-CortexM3


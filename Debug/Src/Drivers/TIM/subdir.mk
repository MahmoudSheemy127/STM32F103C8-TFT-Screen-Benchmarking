################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Drivers/TIM/TIM.c 

OBJS += \
./Src/Drivers/TIM/TIM.o 

C_DEPS += \
./Src/Drivers/TIM/TIM.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Drivers/TIM/%.o: ../Src/Drivers/TIM/%.c Src/Drivers/TIM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-Drivers-2f-TIM

clean-Src-2f-Drivers-2f-TIM:
	-$(RM) ./Src/Drivers/TIM/TIM.d ./Src/Drivers/TIM/TIM.o

.PHONY: clean-Src-2f-Drivers-2f-TIM


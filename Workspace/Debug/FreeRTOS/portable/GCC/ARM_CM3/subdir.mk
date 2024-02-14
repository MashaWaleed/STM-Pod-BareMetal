################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/GCC/ARM_CM3/port.c 

OBJS += \
./FreeRTOS/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./FreeRTOS/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/GCC/ARM_CM3/%.o FreeRTOS/portable/GCC/ARM_CM3/%.su FreeRTOS/portable/GCC/ARM_CM3/%.cyclo: ../FreeRTOS/portable/GCC/ARM_CM3/%.c FreeRTOS/portable/GCC/ARM_CM3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu/HAL/inc" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu/Drivers/include" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu/FreeRTOS/include" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu/FreeRTOS/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM3

clean-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM3:
	-$(RM) ./FreeRTOS/portable/GCC/ARM_CM3/port.cyclo ./FreeRTOS/portable/GCC/ARM_CM3/port.d ./FreeRTOS/portable/GCC/ARM_CM3/port.o ./FreeRTOS/portable/GCC/ARM_CM3/port.su

.PHONY: clean-FreeRTOS-2f-portable-2f-GCC-2f-ARM_CM3


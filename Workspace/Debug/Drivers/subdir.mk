################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ADC.c \
../Drivers/EXTI.c \
../Drivers/GPIO.c \
../Drivers/NVIC_Program.c \
../Drivers/PWM.c \
../Drivers/RCC_program.c \
../Drivers/SPI.c \
../Drivers/Ticker.c \
../Drivers/USART.c 

OBJS += \
./Drivers/ADC.o \
./Drivers/EXTI.o \
./Drivers/GPIO.o \
./Drivers/NVIC_Program.o \
./Drivers/PWM.o \
./Drivers/RCC_program.o \
./Drivers/SPI.o \
./Drivers/Ticker.o \
./Drivers/USART.o 

C_DEPS += \
./Drivers/ADC.d \
./Drivers/EXTI.d \
./Drivers/GPIO.d \
./Drivers/NVIC_Program.d \
./Drivers/PWM.d \
./Drivers/RCC_program.d \
./Drivers/SPI.d \
./Drivers/Ticker.d \
./Drivers/USART.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o Drivers/%.su Drivers/%.cyclo: ../Drivers/%.c Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu-f/HAL/inc" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu-f/Drivers/include" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu-f/FreeRTOS/include" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu-f/FreeRTOS/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers

clean-Drivers:
	-$(RM) ./Drivers/ADC.cyclo ./Drivers/ADC.d ./Drivers/ADC.o ./Drivers/ADC.su ./Drivers/EXTI.cyclo ./Drivers/EXTI.d ./Drivers/EXTI.o ./Drivers/EXTI.su ./Drivers/GPIO.cyclo ./Drivers/GPIO.d ./Drivers/GPIO.o ./Drivers/GPIO.su ./Drivers/NVIC_Program.cyclo ./Drivers/NVIC_Program.d ./Drivers/NVIC_Program.o ./Drivers/NVIC_Program.su ./Drivers/PWM.cyclo ./Drivers/PWM.d ./Drivers/PWM.o ./Drivers/PWM.su ./Drivers/RCC_program.cyclo ./Drivers/RCC_program.d ./Drivers/RCC_program.o ./Drivers/RCC_program.su ./Drivers/SPI.cyclo ./Drivers/SPI.d ./Drivers/SPI.o ./Drivers/SPI.su ./Drivers/Ticker.cyclo ./Drivers/Ticker.d ./Drivers/Ticker.o ./Drivers/Ticker.su ./Drivers/USART.cyclo ./Drivers/USART.d ./Drivers/USART.o ./Drivers/USART.su

.PHONY: clean-Drivers


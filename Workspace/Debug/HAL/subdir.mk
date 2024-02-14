################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/GFX_FUNCTIONS.c \
../HAL/LED.c \
../HAL/MP3.c \
../HAL/PushButton.c \
../HAL/Seg-5161BS.c \
../HAL/Tracks.c \
../HAL/fonts.c \
../HAL/keypad.c \
../HAL/lcd.c \
../HAL/st7735.c 

OBJS += \
./HAL/GFX_FUNCTIONS.o \
./HAL/LED.o \
./HAL/MP3.o \
./HAL/PushButton.o \
./HAL/Seg-5161BS.o \
./HAL/Tracks.o \
./HAL/fonts.o \
./HAL/keypad.o \
./HAL/lcd.o \
./HAL/st7735.o 

C_DEPS += \
./HAL/GFX_FUNCTIONS.d \
./HAL/LED.d \
./HAL/MP3.d \
./HAL/PushButton.d \
./HAL/Seg-5161BS.d \
./HAL/Tracks.d \
./HAL/fonts.d \
./HAL/keypad.d \
./HAL/lcd.d \
./HAL/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o HAL/%.su HAL/%.cyclo: ../HAL/%.c HAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu/HAL/inc" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu/Drivers/include" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu/FreeRTOS/include" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu/FreeRTOS/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL

clean-HAL:
	-$(RM) ./HAL/GFX_FUNCTIONS.cyclo ./HAL/GFX_FUNCTIONS.d ./HAL/GFX_FUNCTIONS.o ./HAL/GFX_FUNCTIONS.su ./HAL/LED.cyclo ./HAL/LED.d ./HAL/LED.o ./HAL/LED.su ./HAL/MP3.cyclo ./HAL/MP3.d ./HAL/MP3.o ./HAL/MP3.su ./HAL/PushButton.cyclo ./HAL/PushButton.d ./HAL/PushButton.o ./HAL/PushButton.su ./HAL/Seg-5161BS.cyclo ./HAL/Seg-5161BS.d ./HAL/Seg-5161BS.o ./HAL/Seg-5161BS.su ./HAL/Tracks.cyclo ./HAL/Tracks.d ./HAL/Tracks.o ./HAL/Tracks.su ./HAL/fonts.cyclo ./HAL/fonts.d ./HAL/fonts.o ./HAL/fonts.su ./HAL/keypad.cyclo ./HAL/keypad.d ./HAL/keypad.o ./HAL/keypad.su ./HAL/lcd.cyclo ./HAL/lcd.d ./HAL/lcd.o ./HAL/lcd.su ./HAL/st7735.cyclo ./HAL/st7735.d ./HAL/st7735.o ./HAL/st7735.su

.PHONY: clean-HAL


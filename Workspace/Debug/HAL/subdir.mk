################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/Buzzer.c \
../HAL/GFX_FUNCTIONS.c \
../HAL/MP3.c \
../HAL/Tracks.c \
../HAL/fonts.c \
../HAL/st7735.c 

OBJS += \
./HAL/Buzzer.o \
./HAL/GFX_FUNCTIONS.o \
./HAL/MP3.o \
./HAL/Tracks.o \
./HAL/fonts.o \
./HAL/st7735.o 

C_DEPS += \
./HAL/Buzzer.d \
./HAL/GFX_FUNCTIONS.d \
./HAL/MP3.d \
./HAL/Tracks.d \
./HAL/fonts.d \
./HAL/st7735.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o HAL/%.su HAL/%.cyclo: ../HAL/%.c HAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu-f/HAL/inc" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu-f/Drivers/include" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu-f/FreeRTOS/include" -I"C:/Users/mw296/STM32CubeIDE/workspace_1.13.0/FREE-RTOS-IMP-menu-f/FreeRTOS/portable/GCC/ARM_CM3" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL

clean-HAL:
	-$(RM) ./HAL/Buzzer.cyclo ./HAL/Buzzer.d ./HAL/Buzzer.o ./HAL/Buzzer.su ./HAL/GFX_FUNCTIONS.cyclo ./HAL/GFX_FUNCTIONS.d ./HAL/GFX_FUNCTIONS.o ./HAL/GFX_FUNCTIONS.su ./HAL/MP3.cyclo ./HAL/MP3.d ./HAL/MP3.o ./HAL/MP3.su ./HAL/Tracks.cyclo ./HAL/Tracks.d ./HAL/Tracks.o ./HAL/Tracks.su ./HAL/fonts.cyclo ./HAL/fonts.d ./HAL/fonts.o ./HAL/fonts.su ./HAL/st7735.cyclo ./HAL/st7735.d ./HAL/st7735.o ./HAL/st7735.su

.PHONY: clean-HAL


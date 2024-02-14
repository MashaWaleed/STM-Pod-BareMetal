################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include HAL/subdir.mk
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/GCC/ARM_CM3/subdir.mk
-include FreeRTOS/subdir.mk
-include Drivers/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := FREE-RTOS-IMP-menu
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
FREE-RTOS-IMP-menu.elf \

MAP_FILES += \
FREE-RTOS-IMP-menu.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
FREE-RTOS-IMP-menu.list \

OBJCOPY_HEX += \
FREE-RTOS-IMP-menu.hex \


# All Target
all: main-build

# Main-build Target
main-build: FREE-RTOS-IMP-menu.elf secondary-outputs

# Tool invocations
FREE-RTOS-IMP-menu.elf FREE-RTOS-IMP-menu.map: $(OBJS) $(USER_OBJS) C:\Users\mw296\STM32CubeIDE\workspace_1.13.0\FREE-RTOS-IMP-menu\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "FREE-RTOS-IMP-menu.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\mw296\STM32CubeIDE\workspace_1.13.0\FREE-RTOS-IMP-menu\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="FREE-RTOS-IMP-menu.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

FREE-RTOS-IMP-menu.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "FREE-RTOS-IMP-menu.list"
	@echo 'Finished building: $@'
	@echo ' '

FREE-RTOS-IMP-menu.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "FREE-RTOS-IMP-menu.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) FREE-RTOS-IMP-menu.elf FREE-RTOS-IMP-menu.hex FREE-RTOS-IMP-menu.list FREE-RTOS-IMP-menu.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

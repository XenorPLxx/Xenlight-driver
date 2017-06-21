################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Xenlight.lss \

FLASH_IMAGE += \
Xenlight.hex \

EEPROM_IMAGE += \
Xenlight.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Xenlight.elf secondary-outputs

# Tool invocations
Xenlight.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Xenlight.map -mmcu=atmega16 -o "Xenlight.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Xenlight.lss: Xenlight.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Xenlight.elf  >"Xenlight.lss"
	@echo 'Finished building: $@'
	@echo ' '

Xenlight.hex: Xenlight.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Xenlight.elf  "Xenlight.hex"
	@echo 'Finished building: $@'
	@echo ' '

Xenlight.eep: Xenlight.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Xenlight.elf  "Xenlight.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Xenlight.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 Xenlight.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) Xenlight.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

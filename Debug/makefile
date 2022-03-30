################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include Dave/Generated/SPI_MASTER/subdir.mk
-include Dave/Generated/I2C_MASTER/subdir.mk
-include Dave/Generated/DIGITAL_IO/subdir.mk
-include Dave/Generated/CPU_CTRL_XMC1/subdir.mk
-include Dave/Generated/CLOCK_XMC1/subdir.mk
-include Dave/Generated/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
RoverX.hex \

SECONDARY_LIST += \
RoverX.lst \

SECONDARY_SIZE += \
RoverX.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "RoverX.map"

TOOLCHAIN_ROOT=D:/Downloads/DAVE_4-4-2_64bit_2018-02-23/DAVE-IDE-4.4.2-64Bit/DAVE-IDE-4.4.2-64Bit/eclipse/ARM-GCC-49
PROJECT_LOC=C:/Workspaces/DAVE-4.4.2-64Bit/RoverX

# All Target
all: RoverX.elf secondary-outputs

# Tool invocations
RoverX.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map,$(MAP_FILE) -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "RoverX.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
RoverX.hex: RoverX.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "RoverX.elf" "RoverX.hex"
	@echo 'Finished building: $@'
	@echo.
RoverX.lst: RoverX.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "RoverX.elf" > "RoverX.lst"
	@echo 'Finished building: $@'
	@echo.
RoverX.siz: RoverX.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "RoverX.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) RoverX.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

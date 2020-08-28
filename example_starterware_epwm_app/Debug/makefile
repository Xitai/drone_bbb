################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/gcc-arm-none-eabi-7-2018-q2-update

GEN_OPTS__FLAG := @"configPkg/compiler.opt" 
GEN_CMDS__FLAG := -Wl,-T"configPkg/linker.cmd" 

ORDERED_OBJS += \
"./Code/epwm_app.o" \
"./Code/haptics_motor/haptics_motor_app_main.o" \
-Wl,-T"../am335x_ddr.lds" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-lrdimon \
-lgcc \
-lm \
-lnosys \
-lc \
-Wl,--end-group \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Code/subdir_vars.mk
-include Code/haptics_motor/subdir_vars.mk
-include subdir_rules.mk
-include Code/subdir_rules.mk
-include Code/haptics_motor/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
example_starterware_epwm_app.out \

EXE_OUTPUTS__QUOTED += \
"example_starterware_epwm_app.out" \

BIN_OUTPUTS += \
example_starterware_epwm_app.hex \

BIN_OUTPUTS__QUOTED += \
"example_starterware_epwm_app.hex" \


# All Target
all: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "example_starterware_epwm_app.out"

# Tool invocations
example_starterware_epwm_app.out: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: GNU Linker'
	"C:/ti/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-gcc-7.3.1.exe" -mtune=cortex-a8 -marm -DSOC_AM335X -DSOC_AM335x -DbbbAM335x -DUSE_BIOS -DCACHE_ENABLE -Dam3359 -Og -g -gdwarf-3 -gstrict-dwarf -Wall -mfloat-abi=hard -Wl,-Map,"example_starterware_epwm_app.map" -nostartfiles -static -Wl,--gc-sections -L"C:/ti/bios_6_76_03_01/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/hard" -Wl,--defsym,STACKSIZE=0x1C000 -Wl,--defsym,HEAPSIZE=0x400 --specs=nano.specs -o"example_starterware_epwm_app.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

example_starterware_epwm_app.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: GNU Objcopy Utility'
	"C:/ti/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-objcopy.exe"  $(EXE_OUTPUTS__QUOTED) "example_starterware_epwm_app.hex"
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Code\epwm_app.o" "Code\haptics_motor\haptics_motor_app_main.o" 
	-$(RM) "Code\epwm_app.d" "Code\haptics_motor\haptics_motor_app_main.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets


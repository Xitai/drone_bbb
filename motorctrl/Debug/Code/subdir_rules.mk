################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Code/%.o: ../Code/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-gcc-7.3.1.exe" -c -mcpu=cortex-a8 -march=armv7-a -mtune=cortex-a8 -marm -Dam3359 -I"C:/Workspace/Drone/ccs_workspace/motorctrl" -I"C:/ti/pdk_am335x_1_0_17/packages/ti/starterware/include/" -I"C:/ti/pdk_am335x_1_0_17/packages/ti/starterware/include/hw" -I"C:/ti/gcc-arm-none-eabi-7-2018-q2-update/arm-none-eabi/include" -Og -g -gdwarf-3 -gstrict-dwarf -Wall -specs="nosys.specs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



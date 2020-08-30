################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Code/haptics_motor/%.o: ../Code/haptics_motor/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"C:/ti/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-gcc-7.3.1.exe" -c -mcpu=cortex-a8 -march=armv7-a -mtune=cortex-a8 -marm -mfloat-abi=hard -DSOC_AM335X -DSOC_AM335x -DbbbAM335x -DUSE_BIOS -DCACHE_ENABLE -Dam3359 -I"C:/Workspace/ws_drone_v10/.git/drone_bbb/example_starterware_epwm_app/Code" -I"C:/ti/pdk_am335x_1_0_17/packages/ti/starterware/examples/example_utils" -I"C:/ti/pdk_am335x_1_0_17/packages/ti/starterware/include/hw" -I"C:/ti/pdk_am335x_1_0_17/packages/ti/starterware/include" -I"C:/ti/pdk_am335x_1_0_17/packages/ti/starterware/include/utils" -I"C:/ti/pdk_am335x_1_0_17/packages/ti/starterware/include/am335x" -I"C:/Workspace/ws_drone_v10/.git/drone_bbb/example_starterware_epwm_app" -I"C:/ti/bios_6_76_03_01/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/include/newlib-nano" -I"C:/ti/bios_6_76_03_01/packages/ti/posix/gcc" -I"C:/ti/gcc-arm-none-eabi-7-2018-q2-update/arm-none-eabi/include" -Og -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-370568049:
	@$(MAKE) --no-print-directory -Onone -f subdir_rules.mk build-370568049-inproc

build-370568049-inproc: ../app.cfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: XDCtools'
	"C:/ti/ccs1010/xdctools_3_61_02_27_core/xs" --xdcpath="C:/ti/bios_6_76_03_01/packages;C:/ti/pdk_am335x_1_0_17/packages;" xdc.tools.configuro -o configPkg -t gnu.targets.arm.A8F -p ti.platforms.beaglebone -r debug -c "C:/ti/gcc-arm-none-eabi-7-2018-q2-update" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

configPkg/linker.cmd: build-370568049 ../app.cfg
configPkg/compiler.opt: build-370568049
configPkg/: build-370568049



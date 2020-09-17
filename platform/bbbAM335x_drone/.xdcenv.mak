#
_XDCBUILDCOUNT = 4
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/libarch_1_0_0_0/packages;C:/ti/xdais_7_24_00_04/packages;C:/ti/xdais_7_24_00_04/examples;C:/ti/ctoolslib_2_2_0_0/packages;C:/ti/pdk_am335x_1_0_17/packages;C:/ti/bios_6_82_01_19/packages;C:/ti/ndk_3_61_01_01/packages;C:/ti/linalg_1_2_0_0/packages;C:/ti/edma3_lld_2_12_05_30E/packages;C:/ti/openmp_dsp_c667x_2_06_03_00/packages;C:/ti/pdk_c667x_2_0_16/packages;C:/ti/imglib_c66x_3_1_1_0/packages;C:/ti/framework_components_3_40_02_07/packages;C:/ti/framework_components_3_40_02_07/examples;C:/ti/ipc_3_50_04_08/packages;C:/ti/uia_2_30_01_02/packages;C:/ti/ccs1010/xdctools_3_61_02_27_core/packages
override XDCROOT = C:/ti/ccs1010/xdctools_3_61_02_27_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/libarch_1_0_0_0/packages;C:/ti/xdais_7_24_00_04/packages;C:/ti/xdais_7_24_00_04/examples;C:/ti/ctoolslib_2_2_0_0/packages;C:/ti/pdk_am335x_1_0_17/packages;C:/ti/bios_6_82_01_19/packages;C:/ti/ndk_3_61_01_01/packages;C:/ti/linalg_1_2_0_0/packages;C:/ti/edma3_lld_2_12_05_30E/packages;C:/ti/openmp_dsp_c667x_2_06_03_00/packages;C:/ti/pdk_c667x_2_0_16/packages;C:/ti/imglib_c66x_3_1_1_0/packages;C:/ti/framework_components_3_40_02_07/packages;C:/ti/framework_components_3_40_02_07/examples;C:/ti/ipc_3_50_04_08/packages;C:/ti/uia_2_30_01_02/packages;C:/ti/ccs1010/xdctools_3_61_02_27_core/packages;C:/ti/ccs1010/xdctools_3_61_02_27_core/packages;..
HOSTOS = Windows
endif

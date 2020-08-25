#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/bios_6_76_03_01/packages;C:/ti/pdk_am335x_1_0_17/packages;C:/Workspace/ws_drone_v10/drone_base/.config
override XDCROOT = C:/ti/ccs1010/xdctools_3_61_02_27_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/bios_6_76_03_01/packages;C:/ti/pdk_am335x_1_0_17/packages;C:/Workspace/ws_drone_v10/drone_base/.config;C:/ti/ccs1010/xdctools_3_61_02_27_core/packages;..
HOSTOS = Windows
endif

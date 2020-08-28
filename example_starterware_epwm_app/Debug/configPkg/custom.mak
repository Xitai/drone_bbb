## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,a8fg linker.cmd package/cfg/app_pa8fg.oa8fg

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/app_pa8fg.xdl
	$(SED) 's"^\"\(package/cfg/app_pa8fgcfg.cmd\)\"$""\"C:/Workspace/ws_drone_v10/example_starterware_epwm_app/Debug/configPkg/\1\""' package/cfg/app_pa8fg.xdl > $@
	-$(SETDATE) -r:max package/cfg/app_pa8fg.h compiler.opt compiler.opt.defs

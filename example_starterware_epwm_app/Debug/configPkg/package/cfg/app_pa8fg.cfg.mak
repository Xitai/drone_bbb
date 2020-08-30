# invoke SourceDir generated makefile for app.pa8fg
app.pa8fg: .libraries,app.pa8fg
.libraries,app.pa8fg: package/cfg/app_pa8fg.xdl
	$(MAKE) -f C:\Workspace\ws_drone_v10\.git\drone_bbb\example_starterware_epwm_app/src/makefile.libs

clean::
	$(MAKE) -f C:\Workspace\ws_drone_v10\.git\drone_bbb\example_starterware_epwm_app/src/makefile.libs clean


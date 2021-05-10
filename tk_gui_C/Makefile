# use with nmake
CL=cl.exe
LINK = link.exe

CFLAGS = /O /I C:\Users\mskocic\LocalApps\Miniconda3\Library\include
LFLAGS = C:\Users\mskocic\LocalApps\Miniconda3\Library\lib\tcl86t.lib C:\Users\mskocic\LocalApps\Miniconda3\Library\lib\tk86t.lib


all: tkgui_cl.exe

tkgui_cl.exe: tkgui_cl.obj
	$(LINK) $** $(LFLAGS) /out:$@

tkgui_cl.obj: tkgui.c
	$(CL) /c $** $(CFLAGS) /Fo$@


.PHONY: clean cleanall

clean:
	rm -f *.o *.obj
cleanall: clean
	rm -rf *.exe
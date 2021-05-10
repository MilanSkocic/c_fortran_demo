CC=gcc
# on windows platform use Tcl/Tk from Python
CFLAGS = -I C:\Users\mskocic\LocalApps\Miniconda3\Library\include
LFLAGS = C:\Users\mskocic\LocalApps\Miniconda3\Library\lib\tcl86t.lib C:\Users\mskocic\LocalApps\Miniconda3\Library\lib\tk86t.lib

# On linux/MacOS
CFLAGS = -I /usr/include/tcl
LFLAGS = -lX11 -ltcl8.6 -ltk8.6

all: tkgui_gcc.out

tkgui_gcc.out: tkgui_gcc.o
	$(CC) $^ $(LFLAGS) -o $@

tkgui_gcc.o: tkgui.c
	$(CC) -c $^ $(CFLAGS) -o $@

.PHONY: clean cleanall

clean:
	rm *.o

cleanall: clean
	rm *.out



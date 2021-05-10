CC=cl.exe
LINKER = link.exe
CFLAGS =
LDFLAGS =

all: gnuplot_gcc.exe

gnuplot_gcc.exe: gnuplot.obj
	$(LINKER) $** /out:$@

gnuplot.obj: gnuplot.c
	$(CC) $(CFLAGS) /c $** /Fo$@


.PHONY: run
run: all
	@echo "--> TESTING GNUPLOT <--"
	@./gnuplot_gcc

clean:
	rm gnuplot.obj

cleanall: clean
	rm *.exe
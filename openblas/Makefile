# use with nmake
# Use mkl on windows


ICL=icl.exe
XILINK = xilink.exe


all: test_blas_mkl_icl.exe array_icl_mkl.exe

test_blas_mkl_icl.exe: test_blas_mkl_icl.obj
	$(XILINK) $** /out:$@

test_blas_mkl_icl.obj: test_blas.c
	$(ICL) /Qmkl /c $** /Fo$@

array_icl_mkl.exe: array_icl_mkl.obj
	$(XILINK) $** /out:$@

array_icl_mkl.obj: array.c
	$(ICL) /Qmkl /c $** /Fo$@




.PHONY: clean cleanall

clean:
	rm -f *.o *.obj
cleanall: clean
	rm -rf *.exe

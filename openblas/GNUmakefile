# On windows use Openblas from msys2 or compile it from sources
win_root_lib = C:/msys64/mingw64/lib
win_root_include = C:/msys64/mingw64/include/OpenBLAS

# On linux/MacOS
unix_root_lib = /usr/local/opt/openblas/lib
unix_root_include = /usr/local/opt/openblas/include

CC=gcc
CFLAGS = -O3 -DADD_ -I $(unix_root_include)
LDFLAGS = -L $(unix_root_lib) -lopenblas

all: test_blas_openblas_gcc.out array_openblas_gcc.out

test_blas_openblas_gcc.out: test_blas_openblas_gcc.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_blas_openblas_gcc.o: test_blas.c
	$(CC) -o $@ -c $< $(CFLAGS)

array_openblas_gcc.out: array_openblas_gcc.o
	$(CC) -o $@ $^ $(LDFLAGS)

array_openblas_gcc.o: array.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: run
run: all
	@echo "--> TESTING OPENBLAS <--"
	@./test_blas_openblas_gcc
	@echo "--> TESTING ARRAY API <--"
	@./array_openblas_gcc

clean:
	rm *.o

cleanall: clean
	rm *.out

CC=gcc
FC=gfortran
CFLAGS= -Wall -std=c99 -g
FFLAGS=-O3 -std=f90


OBJ = tokenobject.o lexerobject.o parser.o main.o

all: prog.out

prog.out: $(OBJ)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $^

.PHONY: clean cleanall

clean:
	rm *.o

cleanall: clean
	rm prog.out


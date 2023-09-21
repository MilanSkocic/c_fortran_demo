CC=gcc
FC=gfortran
LINKER=gfortran
CFLAGS=-std=c11
FFLAGS=-std=f2008
LDFLAGS=
C_SOURCES=$(wildcard src/*.c)
F_SOURCES=$(wildcard src/*.f90)
C_OBJECTS=$(patsubst src/%.c, src/%.o, $(C_SOURCES))
F_OBJECTS=$(patsubst src/%.f90, src/%.o, $(F_SOURCES))
LIB=library.so

all: $(LIB)

$(LIB): $(C_OBJECTS) $(F_OBJECTS)
	$(LINKER) -shared $^ $(LDFLAGS) -o $@

$(C_OBJECTS): $(C_SOURCES)
	$(CC) -c -fPIC $(CFLAGS) $^ -o $@

$(F_OBJECTS): $(F_SOURCES)
	$(FC) -c -fPIC $(FFLAGS) $^ -o $@

clean:
	rm -f *.o
	rm -f app*
	rm -f library.so
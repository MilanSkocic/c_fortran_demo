include ../make.in

OBJ = src1.o utilities.o

all: $(LIB)

$(LIB): $(OBJ)
	$(ARCH) $(ARCHFLAGS) $(LIB) $(OBJ)
	$(RANLIB) $(LIB)

%.o: %.c
	$(CC) -c $^ $(CFLAGS) -I ../include -o $@

.PHONY: clean cleanall
	
clean:
	rm -f *.o

cleanall:
	rm -f ../lib/*.a


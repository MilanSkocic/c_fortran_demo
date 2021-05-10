include ../make.in

OBJ = example1.o

all: $(EXAMPLES)

$(EXAMPLES): $(OBJ)
	$(CC) $^ $(LIB) -lm -o $@

%.o: %.c
	$(CC) -c $^ $(CFLAGS) -I ../include -o $@

.PHONY: clean cleanall run

run:
	@./example1.out
	
clean:
	rm -f *.o

cleanall:
	rm -f *.out


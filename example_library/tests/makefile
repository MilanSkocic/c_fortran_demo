include ../make.in

OBJ = runtests.o

all: $(TESTS)

$(TESTS): $(OBJ)
	$(CC) $^ $(LIB) -lm -o $@

%.o: %.c
	$(CC) -c $^ $(CFLAGS) -I ../include -o $@

.PHONY: clean cleanall run

run:
	@./runtests.out
	
clean:
	rm -f *.o

cleanall:
	rm -f *.out


CC=gcc
CFLAGS=-std=c11
SOURCES=$(wildcard *.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))


all: ast.out

ast: $(OBJECTS)
	gcc $^ -o $@

%.o: %.c
	gcc -c $^ -o $@
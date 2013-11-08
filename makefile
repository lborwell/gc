CC = gcc
CFLAGS = -c

all:	stack.o gc

stack.o:	src/stack.c
	$(CC) $(CFLAGS) src/stack.c -g -o bin/stack.o

gc:	src/gc.c bin/stack.o
	$(CC) src/gc.c bin/stack.o -g -o bin/gc

clean:
	rm -f bin/*

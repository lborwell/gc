CC = gcc
CFLAGS = -c

all:	stack.o gc

stack.o:	src/stack.c
	$(CC) $(CFLAGS) src/stack.c -o bin/stack.o

gc:	src/gc.c bin/stack.o
	$(CC) src/gc.c bin/stack.o -o bin/gc

clean:
	rm -f bin/*

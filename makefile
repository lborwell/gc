CC = gcc
CFLAGS = -c

all:	heap.o stack.o gc

heap.o:		src/heap.c
	$(CC) $(CFLAGS) src/heap.c -g -o bin/heap.o

stack.o:	src/stack.c
	$(CC) $(CFLAGS) src/stack.c -g -o bin/stack.o

gc:	src/gc.c bin/stack.o bin/heap.o
	$(CC) src/gc.c bin/stack.o bin/heap.o -g -o bin/gc

clean:
	rm -f bin/*

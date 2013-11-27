CC = gcc
CFLAGS = -c -g

all:	heap.o stack.o gc.o test

heap.o:		src/heap.c
	$(CC) $(CFLAGS) src/heap.c -o bin/heap.o

stack.o:	src/stack.c
	$(CC) $(CFLAGS) src/stack.c -o bin/stack.o

gc.o:	src/gc.c
	$(CC) $(CFLAGS) src/gc.c -o bin/gc.o

test:	src/testgc.c bin/gc.o bin/stack.o bin/heap.o
	$(CC) -g bin/gc.o bin/stack.o bin/heap.o src/testgc.c -o bin/test

clean:
	rm -f bin/*

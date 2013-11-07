all : stack.o gc

stack.o : src/stack
	gcc -c src/stack.c -o bin/stack.o

gc : src/gc.c bin/stack.o
	gcc src/gc.c bin/stack.o -o bin/gc

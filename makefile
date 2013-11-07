all : gc

gc : src/gc
	gcc -std=c99 src/gc.c -o bin/gc

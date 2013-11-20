#include "stack.h"
#define HEAP_SIZE 256

typedef struct {
    int heap[HEAP_SIZE];
    int hpLimit;// = HEAP_SIZE/2;
    int hp;
} heap;

heap* heapCreate();
void heapAdd(heap*, type, void*);
void printHeap(heap*);

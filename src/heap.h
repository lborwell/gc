#include "stack.h"
#define HEAP_SIZE 256

typedef struct {
    int heap[HEAP_SIZE];
    int hpLimit;
    int hp;
} heap;

heap* heapCreate();
void heapAdd(heap*, type, void*);
void printHeap(heap*);
void simplePrintHeap(heap*);
heap* initHeaps();
void dataConsCreate();
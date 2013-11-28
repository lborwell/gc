#include "stack.h"
#include <string.h>

#define HEAP_SIZE 50

typedef struct {
    int heap[HEAP_SIZE];
    int hpLimit;
    int hp;
} heap;

heap* datacons;
heap* bigdataheap;
Stack* bigdataindex;

heap* heapCreate();
void heapAdd(heap*, type, void*);
void printHeap(heap*);
void simplePrintHeap(heap*);
heap* initHeaps();
void dataConsCreate();
void bigdataHeapCreate();
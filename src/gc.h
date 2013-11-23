#include "heap.h"
#include <string.h>

void collect(Stack*, heap**);
int evac(int, heap*, heap*);
void scavenge(heap*, heap*);

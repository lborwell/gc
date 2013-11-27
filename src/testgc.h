#include "gc.h"

typedef struct {
	Stack* s;
	heap* h;
} Test;

int main();
Test* test1();
void runTest(Test*);
void definePrims();
#include "gc.h"

int main(){
	int* i = malloc(sizeof(int));
	*i = 1;
	Stack* s = createNode(STRING, "hello");
	s->next = createNode(STRING, "pls");

	printStack(s);

    //puts("Collected mudafuka");
    return 0;
}


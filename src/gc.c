#include "gc.h"

int main(){
	int* i = malloc(sizeof(int));
	*i = 1;

	Stack* s = initStack();
	push(&s,STRING,"im");
	push(&s,STRING,"so");
	push(&s,STRING,"good");
	push(&s,INT,i);
	
	printStack(s);

    //puts("Collected mudafuka");
    return 0;
}


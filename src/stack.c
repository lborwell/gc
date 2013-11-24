#include "stack.h"

Stack* createNode(int data){
	Stack* s = malloc(sizeof(Stack));
	s->data = data;
	s->next = NULL;
	return s;
}

void push(Stack** s, int elem){
	Stack* n = createNode(elem);
	n->next = *s;
	*s = n;
}

int pop(Stack** s){
	if(!(*s))
		return -1;
	Stack* r = *s;
	*s = (*s)->next;
	//r->next = NULL;
	int d = r->data;
	free(r);
	return d;
}

Stack* stackCreate(){
	Stack* r = NULL;
	return r;
}

void freeStack(Stack* s){
	if(!s)
		return;
	freeStack(s->next);
	free(s);
}

void printStack(Stack* n){
	if(n->next)
		printStack(n->next);
	if(n)
		printNode(n);
}

void printNode(Stack* n){
	printf("%i\n",n->data);
}
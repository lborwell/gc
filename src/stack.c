#include "stack.h"

/*
*  Simple stack implementation for garbage collector.
*/

Stack* createNode(int data){
	Stack* s = malloc(sizeof(Stack));
	s->data = data;
	s->bdloc = 0;
	s->next = NULL;
	return s;
}

void push(Stack** s, int elem){
	Stack* n = createNode(elem);
	n->next = *s;
	*s = n;
}

//Push BigData information
void pushBD(Stack** s, int data, int bd){
	Stack* n = createNode(data);
	n->bdloc = bd;
	n->next = *s;
	*s = n;
}

int pop(Stack** s){
	if(!(*s))
		return -1;
	Stack* r = *s;
	*s = (*s)->next;
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
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
	Stack* r = *s;
	*s = (*s)->next;
	r->next = NULL;
	return r->data;
}

Stack* initStack(){
	Stack* r = NULL;
	return r;
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

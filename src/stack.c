#include "stack.h"

Stack* createNode(type t, void* data){
	Stack* s = malloc(sizeof(Stack));
	s->t = t;
	s->data = data;
	s->next = NULL;
	return s;
}

void push(Stack** s, type t, void* elem){
	Stack* n = createNode(t,elem);
	n->next = *s;
	*s = n;
}

void* pop(Stack** s){
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
	switch(n->t){
		case INT: printf("INT %i",*(int*)(n->data)); break;
		case BOOL: printf("BOOL %s",(*(int*)(n->data))?"TRUE":"FALSE"); break;
		case STRING: printf("STRING %s",(char*)(n->data)); break;
		case DATA: printf("DATA %i",(int*)(n->data)); break;
		case BIGDATA: printf("BIGDATA %i",(int*)(n->data)); break;
		case RANGE: printf("RANGE %i",(int*)(n->data)); break;
		case LAMBDA: printf("LAMBDA %s",(char*)(n->data)); break;
		case SOFT: printf("SOFT %s",(char*)(n->data)); break;
		case PHANTOM: printf("PHANTOM %s",(char*)(n->data)); break;
		case WEAK: printf("WEAK %s",(char*)(n->data)); break;
	}
	printf("\n");
	
}
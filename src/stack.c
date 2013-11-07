#include "stack.h"

Stack* createNode(type t, void* data){
	Stack* s = malloc(sizeof(Stack));
	s->t = t;
	s->data = data;
	s->next = NULL;
	return s;
}

void printStack(Stack* n){
	if(n->next)
		printNode(n->next);
	printNode(n);
}

void printNode(Stack* n){
	switch(n->t){
		case INT: printf("%i",*(int*)(n->data)); break;
		case BOOL: printf("%s",(*(int*)(n->data))?"TRUE":"FALSE"); break;
		case STRING: printf("%s",(char*)(n->data)); break;
		
	}
	printf("\n");
	
}
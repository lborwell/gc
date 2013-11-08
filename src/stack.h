#include <stdio.h>
#include <stdlib.h>
#include "data.h"

typedef enum { INT, 
	BOOL, 
	STRING,
	DATA,
	BIGDATA,
	RANGE,
	LAMBDA,
	SOFT,
	PHANTOM,
	WEAK
} type;

typedef struct snode{
	type t;
	void* data;
	struct snode* next;
} Stack;

Stack* createNode(type, void*);
void printStack(Stack*);
void printNode(Stack*);
Stack* initStack();
void push(Stack**,type,void*);
void* pop(Stack**);

int main();
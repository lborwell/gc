#include <stdio.h>
#include <stdlib.h>

typedef enum { INT, 
	BOOL, 
	STRING,
	DATA,
	BIGDATA,
	RANGE,
	LAMBDA,
	SOFT,
	PHANTOM,
	WEAK,
    FWD
} type;

typedef struct snode{
	int data;
	struct snode* next;
} Stack;

Stack* createNode(int);
void printStack(Stack*);
void printNode(Stack*);
Stack* initStack();
void push(Stack**,int);
int pop(Stack**);

int main();

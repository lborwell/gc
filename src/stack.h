#include <stdio.h>
#include <stdlib.h>

typedef enum { INT, 
	BOOL, 
	STRING,
	DATA,
	BIGDATA,
	RANGE,
	LAMDA,
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

int main();
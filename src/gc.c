#include "gc.h"

int main(){
	Stack* s = initStack();
	push(&s,1);
	push(&s,2);
	push(&s,3);
	push(&s,4);
	
    int* in = malloc(sizeof(int));
    *in = 10;
    char* str = malloc(sizeof(char)*6);
    str = "hello\0";
    int* boo = malloc(sizeof(int));
    *boo = 0;
    int bigdata[] = { 3,1,2,3,4 };
    int range[] = { 50,60 };
    int lambda[] = { 1,8,9 };
    int* soft = malloc(sizeof(int));
    *soft = 9;
    int* weak = malloc(sizeof(int));
    *weak = 2;

    heap* h = heapCreate();
    heapAdd(h,INT,in);
    heapAdd(h,STRING,str);
    heapAdd(h,BOOL,boo);
    heapAdd(h,BIGDATA,bigdata);
    heapAdd(h,RANGE,range);
    heapAdd(h,LAMBDA,lambda);
    heapAdd(h,SOFT,soft);
    heapAdd(h,WEAK,weak);
    puts("=========================================");
    printHeap(h);

    return 0;
}


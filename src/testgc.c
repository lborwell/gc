#include "testgc.h"

extern heap* bigdataheap;
extern int collectioncount;


int* inn;
char* str;
int* boo;

int main(){
	definePrims();
	
	Test* t = test1();
    runTest(t);



	return 0;
}

void definePrims(){
    inn = malloc(sizeof(int));
    *inn = 5;
    str = malloc(sizeof(char)*6);
    str = "hello";
    boo = malloc(sizeof(int));
    *boo = 0;
}

void runTest(Test* t){
	//print results
    puts("\nStarting heap:");
    puts("=========================================");
    printHeap(t->h);
    puts("\nStarting stack:");
    puts("=========================================");
    printStack(t->s);
    
    collect(t->s,&(t->h),0);

    puts("\nCollected heap:");
    puts("=========================================");
    printHeap(t->h);

    puts("\nCollected stack:");
    puts("=========================================");
    printStack(t->s);

    puts("\nBigdata heap:");
    puts("====================================");
    printHeap(bigdataheap);
}


Test* test1(){
	Test* t = malloc(sizeof(Test));

    t->s = stackCreate();
    push(&(t->s),24);
    push(&(t->s),13);
    push(&(t->s),0);

    collectioncount = 2;
    int data[] = { 2,4,28 };
    int bigdata[] = { 3,1,19,21,6 };
    int range[] = { 0,32 };
    int lambda[] = { 8,1,6 };
    int phantom[] = { 4,0 };
    int* soft = malloc(sizeof(int));
    *soft = 0;
    int* weak = malloc(sizeof(int));
    *weak = 2;

    //build test heap
    t->h = initHeaps();
    heap* h = t->h;
    heapAdd(h,INT,inn);
    heapAdd(h,BOOL,boo);
    heapAdd(h,WEAK,weak);
    heapAdd(h,STRING,str);
    heapAdd(h,BIGDATA,bigdata);
    heapAdd(h,LAMBDA,lambda);
    heapAdd(h,INT,inn);
    heapAdd(h,RANGE,range);
    heapAdd(h,DATA,data);
    heapAdd(h,SOFT,soft);
    heapAdd(h,BIGDATA,bigdata);
    heapAdd(h,PHANTOM,phantom);

    return t;
}
#include "testgc.h"

extern heap* bigdataheap;
extern int collectioncount;

//extern int counter;

int* inn;
char* str;
int* boo;

int main(){
	definePrims();
	
    testBasics();
    testScavenge();
    runTest(test1());
    runTest(test2());
    runTest(bigdatacoll());
    runTest(bigdatanocoll());

    /*int i = 1;
    while(i<85){
        puts("test");
        counter = 0;
        testComp(i);
        printf("%i, %i\n",i,counter);
        i++;
    }*/

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

void testComp(int i){
    Test* t = createTest();
    int j;
    int* r = malloc(sizeof(int)*2);
    r[0] = 0;
    for(j=0; j<i; j++){
        r[1] = (j+1)*3;
        heapAdd(t->h,RANGE,r);
    }
    //simplePrintHeap(t->h);
    push(&(t->s),0);
    collect(t->s, &(t->h), 0);
}

Test* createTest(){
    Test* t = malloc(sizeof(Test));
    t->h = initHeaps();
    t->s = stackCreate();
    return t;
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

void testScavenge(){
    runTest(scavengeBD());
    runTest(scavengeRange());
    runTest(scavengeLambda());
    runTest(scavengeWeakExists());
    runTest(scavengeWeakNoExists());
    runTest(scavengePhantomFinal());
    runTest(scavengePhantomNoFinal());
}

void testBasics(){
    runTest(testInt());
    runTest(testBool());
    runTest(testString());
    runTest(testData());
    runTest(testBigdata());
    runTest(testRange());
    runTest(testLambda());
    runTest(testSoft());
    runTest(testPhantom());
    runTest(testWeak());
}

Test* testInt(){
    Test* t = createTest();
    int* data = malloc(sizeof(int)); *data = 5;
    heapAdd(t->h,INT,data);
    push(&(t->s),0);
    return t;
}

Test* testBool(){
    Test* t = createTest();
    int* data = malloc(sizeof(int)); *data = 0;
    heapAdd(t->h,BOOL,data);
    data = malloc(sizeof(int)); *data = 1;
    heapAdd(t->h,BOOL,data);
    push(&(t->s),0);
    push(&(t->s),2);
    return t;
}

Test* testString(){
    Test* t = createTest();
    char* data = "hello";
    heapAdd(t->h,STRING,data);
    push(&(t->s),0);
    return t;
}

Test* testData(){
    Test* t = createTest();
    int data[] = { 2, 0, 0 };
    heapAdd(t->h,DATA,data);
    push(&(t->s),0);
    return t;
}

Test* testBigdata(){
    Test* t = createTest();
    int data[] = { 2, 0, 0, 0 };
    heapAdd(t->h,BIGDATA,data);
    push(&(t->s),0);
    return t;
}

Test* testRange(){
    Test* t = createTest();
    int data[] = { 0, 0 };
    heapAdd(t->h,RANGE,data);
    push(&(t->s),0);
    return t;
}

Test* testLambda(){
    Test* t = createTest();
    int data[] = { 0, 2, 0, 0 };
    heapAdd(t->h,LAMBDA,data);
    push(&(t->s),0);
    return t;
}

Test* testSoft(){
    Test* t = createTest();
    int* data = malloc(sizeof(int)); *data = 0;
    heapAdd(t->h,SOFT,data);
    push(&(t->s),0);
    return t;
}

Test* testPhantom(){
    Test* t = createTest();
    int data[] = { 0,1 };
    heapAdd(t->h,PHANTOM,data);
    int data1[] = { 0,0 };
    heapAdd(t->h,PHANTOM,data1);
    push(&(t->s),0);
    return t;
}

Test* testWeak(){
    Test* t = createTest();
    int* data = malloc(sizeof(int)); *data = 0;
    heapAdd(t->h,WEAK,data);
    push(&(t->s),0);
    return t;
}

Test* scavengeBD(){
    Test* t = createTest();

    int data[] = {2,0,0,2};
    heapAdd(t->h, INT, inn);
    heapAdd(t->h, BOOL, boo);
    heapAdd(t->h, BIGDATA, data);

    push(&(t->s),4);
    return t;
}

Test* scavengeRange(){
    Test* t = createTest();

    int data[] = { 0, 5};
    heapAdd(t->h, INT, inn);
    heapAdd(t->h, RANGE, data);
    heapAdd(t->h, STRING, str);

    push(&(t->s),2);
    return t;
}

Test* scavengeLambda(){
    Test* t = createTest();

    int data[] = {0,2,0,2};
    heapAdd(t->h, INT, inn);
    heapAdd(t->h, BOOL, boo);
    heapAdd(t->h, LAMBDA, data);

    push(&(t->s),4);
    return t;   
}

Test* scavengeWeakExists(){
    Test* t = createTest();
    int* data = malloc(sizeof(int)); *data = 0;
    heapAdd(t->h, INT, inn);
    heapAdd(t->h, WEAK, data);

    push(&(t->s), 0);
    push(&(t->s), 2);
    return t;
}

Test* scavengeWeakNoExists(){
    Test* t = createTest();
    int* data = malloc(sizeof(int)); *data = 0;
    heapAdd(t->h, INT, inn);
    heapAdd(t->h, WEAK, data);

    push(&(t->s), 2);
    return t;
}

Test* scavengePhantomFinal(){
    Test* t = createTest();
    int data[] = { 0,0 };

    heapAdd(t->h, INT, inn);
    heapAdd(t->h, PHANTOM, data);

    push(&(t->s), 2);
    return t;
}

Test* scavengePhantomNoFinal(){
    Test* t = createTest();
    int data[] = { 0,1 };

    heapAdd(t->h, INT, inn);
    heapAdd(t->h, PHANTOM, data);

    push(&(t->s), 2);
    return t;
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

Test* test2(){
    Test* t = createTest();
    push(&(t->s),24);
    push(&(t->s),13);
    push(&(t->s),0);

    collectioncount = 2;
    int data[] = { 2,4,28 };
    int bigdata[] = { 3,1,19,21,2 };
    int range[] = { 0,32 };
    int lambda[] = { 8,1,6 };
    int phantom[] = { 4,1 };
    int* soft = malloc(sizeof(int));
    *soft = 0;
    int* weak = malloc(sizeof(int));
    *weak = 2;

    //build test heap
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

Test* bigdatacoll(){
    Test* t = createTest();
    push(&(t->s),0);

    collectioncount = 2;
    int bigdata[] = { 3,1,0,0,0 };
    
    //build test heap
    heap* h = t->h;
    heapAdd(h,BIGDATA,bigdata);
    heapAdd(h,BIGDATA,bigdata);

    return t;
}

Test* bigdatanocoll(){
    Test* t = createTest();
    push(&(t->s),0);

    collectioncount = 1;
    int bigdata[] = { 3,1,0,0,0 };
    
    //build test heap
    heap* h = t->h;
    heapAdd(h,BIGDATA,bigdata);
    heapAdd(h,BIGDATA,bigdata);

    return t;
}
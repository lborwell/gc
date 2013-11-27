#include "gc.h"

typedef struct {
	Stack* s;
	heap* h;
} Test;

int main();

void runTest(Test*);
void definePrims();
void testBasics();
Test* createTest();
Test* test1();

Test* testInt();    
Test* testBool();   
Test* testString(); 
Test* testData();   
Test* testBigdata();
Test* testRange();  
Test* testLambda(); 
Test* testSoft();   
Test* testPhantom();
Test* testWeak();   
Test* scavengeBD();
Test* scavengeRange();
Test* scavengeLambda();
Test* scavengeWeakExists();
Test* scavengeWeakNoExists();
Test* scavengePhantomFinal();
Test* scavengePhantomNoFinal();
void testScavenge();
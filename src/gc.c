#include "gc.h"

int main(){
	Stack* s = initStack();
	push(&s,4);
	push(&s,2);
	push(&s,0);
	
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
    heapAdd(h,BOOL,boo);
    heapAdd(h,WEAK,weak);
    heapAdd(h,STRING,str);
    /*heapAdd(h,STRING,str);
    heapAdd(h,BOOL,boo);
    heapAdd(h,BIGDATA,bigdata);
    heapAdd(h,RANGE,range);
    heapAdd(h,LAMBDA,lambda);
    heapAdd(h,SOFT,soft);
    heapAdd(h,WEAK,weak);*/
    puts("=========================================");
    printHeap(h);
    puts("=========================================");
    collect(s,&h);
    printHeap(h);
    puts("====================================");
    simplePrintHeap(h);

    return 0;
}

void collect(Stack* s, heap** h){
    heap* to = heapCreate();
    
    do{
        s->data = evac(s->data, *h, to); 
    }while(s=s->next);

    free(*h);
    *h = to;
}

int evac(int pos, heap* from, heap* to){
    int* theap = to->heap;
    int* fheap = from->heap;

    int cpos = to->hp;
    theap[to->hp] = fheap[pos];

    switch(from->heap[pos]){
        case INT:
        case BOOL:
        case WEAK:
            theap[++(to->hp)] = fheap[pos+1];
            break;

        case RANGE:
            theap[++(to->hp)] = fheap[pos+1];
            theap[++(to->hp)] = fheap[pos+2];
            break;

        case STRING:
            {
                int x = 0;
                do{
                    theap[++(to->hp)] = fheap[x+pos];
                }while((char)fheap[(x++) + pos] != '\0');
                theap[++(to->hp)] = (int)'\0';
                break;
            }

        case BIGDATA:
        case LAMBDA:
            {
                int x;
                int lim = fheap[pos];

                theap[++(to->hp)] = fheap[pos];
                theap[++(to->hp)] = fheap[pos+1];

                for(x=0; x<lim; x++)
                    theap[++(to->hp)] = fheap[pos+x];

                break;
            }
    }

    to->hp++;
    fheap[pos] = FWD;
    fheap[pos+1] = cpos;

    return cpos;
}

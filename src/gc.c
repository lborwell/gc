#include "gc.h"

int main(){
	Stack* s = initStack();
    push(&s,21);
	push(&s,14);
	push(&s,2);
	push(&s,0);
	
    int* inn = malloc(sizeof(int));
    *inn = 5;
    int* in = malloc(sizeof(int));
    *in = 10;
    char* str = malloc(sizeof(char)*6);
    str = "hello\0";
    int* boo = malloc(sizeof(int));
    *boo = 0;
    int bigdata[] = { 3,1,25,0,0 };
    int range[] = { 50,60 };
    int lambda[] = { 8,1,2 };
    int* soft = malloc(sizeof(int));
    *soft = 9;
    int* weak = malloc(sizeof(int));
    *weak = 2;

    heap* h = heapCreate();
    heapAdd(h,INT,in);
    heapAdd(h,BOOL,boo);
    heapAdd(h,WEAK,weak);
    heapAdd(h,STRING,str);
    heapAdd(h,BIGDATA,bigdata);
    heapAdd(h,LAMBDA,lambda);
    heapAdd(h,INT,inn);
    puts("=========================================");
    printHeap(h);
    printStack(s);
    puts("=========================================");
    collect(s,&h);
    printHeap(h);
    printStack(s);
    puts("====================================");
    //simplePrintHeap(h);

    return 0;
}

void collect(Stack* s, heap** h){
    heap* to = heapCreate();
    
    //evacuate things pointed to from the stack
    do{
        s->data = evac(s->data, *h, to); 
    }while(s=s->next);

    //scavenge the to-space
    scavenge(*h,to);

    free(*h);
    *h = to;
}

int evac(int pos, heap* from, heap* to){
    int* theap = to->heap;
    int* fheap = from->heap;

    //if forwarding pointer, don't do a thing
    if(fheap[pos] == FWD)
        return fheap[pos+1];

    //cpos -- current position of hp (where we'll evac to)
    int cpos = to->hp;
    theap[to->hp] = fheap[pos];

    switch(from->heap[pos]){
        case INT:
        case BOOL:
        case WEAK:
            memcpy(&theap[++(to->hp)], &fheap[pos+1], sizeof(int));
            break;

        case RANGE:
            memcpy(&theap[++(to->hp)], &fheap[pos+1], 2*sizeof(int));
            (to->hp)++;
            break;

        case STRING:
            {
                int x = 1;
                do{
                    theap[++(to->hp)] = fheap[x+pos];
                }while((char)fheap[(x++) + pos] != '\0');
                theap[++(to->hp)] = (int)'\0';
                break;
            }

        case BIGDATA:
                memcpy(&theap[++(to->hp)], &fheap[pos+1], (fheap[pos+1]+2)*sizeof(int));
                to->hp += fheap[pos+1]+2;
                break;
        case LAMBDA:
                memcpy(&theap[++(to->hp)], &fheap[pos+1], (fheap[pos+2]+2)*sizeof(int));
                to->hp += fheap[pos+2]+2;
                break;
    }

    to->hp++;
    fheap[pos] = FWD;
    fheap[pos+1] = cpos;

    return cpos;
}

void scavenge(heap* from, heap* to){
    int i=0;
    while(i < to->hp){
//        printf("%i ",i);
        switch(to->heap[i]){
            case INT:
            case BOOL:
                i+=2;
                break;

            case STRING:
                i++;
                while((char)to->heap[i] != '\0')
                    i++;
                break;

            case RANGE:
                to->heap[i+1] = evac(to->heap[i+1], from, to);
                to->heap[i+2] = evac(to->heap[i+2], from, to);
                i+=3;
                break;

            case BIGDATA:
                {
                    int lim = i + to->heap[i+1] + 2;
                    i += 2;
                    while(i++ <= lim)
                        to->heap[i] = evac(to->heap[i], from, to);
                    break;
                }
            case LAMBDA:
                {
                    int lim = i + to->heap[i+2] + 2;
                    i+=2;
                    while(i++ <= lim)
                        to->heap[i] = evac(to->heap[i], from, to);
                    break;
                }

            case DATA:
            case SOFT:

            case PHANTOM:

            case WEAK:
                break;
        }
    }
}

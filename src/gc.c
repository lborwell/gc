#include "gc.h"

extern heap* datacons;
extern heap* bigdataheap;
extern Stack* bigdataindex;
Stack* weakptrs;
int collectioncount;

//int counter;

const int BIGDATACOLLECT = 2;

/*
* RUN THE COLLECTOR
* args
* Stack* s -- local variable stack
* heap** h -- current (pointer to pointer to) from-space
* int bd -- are we collecting BigData heap? (bool: 0 false, otherwise true)
*/
void collect(Stack* s, heap** h, int bd){
    heap* to = heapCreate();
    weakptrs = stackCreate();

    // If stack is empty, return empty heap
    if(!s){ 
        *h = to;
        return; 
    }

    //evacuate things pointed to from the stack, update stack references
    do{
        s->data = evac(s->data, *h, to);
    }while(s=s->next);

    // if collecting bigdata heap, no need to scavenge
    if(bd){
        *h = to;
        return;
    }

    //scavenge the to-space
    scavenge(*h,to);

    /*
    * Check weak pointer references. If data is already forwarded, we know
    * it's got another reference -- copy the forwarding pointer loc.
    * Otherwise, we collect the data.
    */
    int i;
    while((i = pop(&weakptrs)) != -1){
        if((*h)->heap[to->heap[i+1]] == FWD)
            to->heap[i+1] = (*h)->heap[to->heap[i+1]+1];
        else
            to->heap[i+1] = -1;
    }

    //Change reference of from-space to to-space
    free(*h);
    *h = to;

    //collect big data heap
    if(!(collectioncount % BIGDATACOLLECT)){
        if(!bigdataindex) return;

        collect(bigdataindex, &bigdataheap, 1);
        Stack* bdi = bigdataindex;
        do{
            (*h)->heap[bdi->bdloc] = bdi->data;
        }while(bdi=bdi->next);
    }
}

/*
* Evacuate. Copy value from from-space to to-space.
* End of switch assumes pointer at last element of object.
*/
int evac(int pos, heap* from, heap* to){
    //counter++;
    int* theap = to->heap;
    int* fheap = from->heap;

    //if forwarding pointer, don't do a thing
    if(fheap[pos] == FWD)
        return fheap[pos+1];

    //cpos -- current position of hp (where we'll evac to)
    int cpos = to->hp;
    theap[to->hp] = fheap[pos];

    switch(from->heap[pos]){
        // If it's weak, push it to the stack. We don't have to worry about
        // pushing the same weak pointer multiple times.
        case WEAK:
            push(&weakptrs, to->hp);
            memcpy(&theap[++(to->hp)], &fheap[pos+1], sizeof(int));
            break;

        case BIGDATA:
            if(!(collectioncount % BIGDATACOLLECT))
                pushBD(&bigdataindex, fheap[pos+1], to->hp + 1);

        case INT:
        case BOOL:
        case SOFT:
            memcpy(&theap[++(to->hp)], &fheap[pos+1], sizeof(int));
            break;

        case PHANTOM:
        case RANGE:
            memcpy(&theap[++(to->hp)], &fheap[pos+1], 2*sizeof(int));
            (to->hp)++;
            break;

        case STRING:
            {
                int x = 1;
                do{
                    theap[++(to->hp)] = fheap[x+pos];
                }while(fheap[(x++) + pos] != 0);
                break;
            }

        case LAMBDA:
            memcpy(&theap[++(to->hp)], &fheap[pos+1], (fheap[pos+2]+2)*sizeof(int));
            to->hp += fheap[pos+2]+1;
            break;

        case DATA:
            memcpy(&theap[++(to->hp)], &fheap[pos+1], (datacons->heap[fheap[pos+1]]+1)*sizeof(int));
            to->hp += datacons->heap[fheap[pos+1]];
            break;

        case BDHEAP:
        {
            memcpy(&theap[++(to->hp)], &fheap[pos+1], (fheap[pos+1]+2)*sizeof(int));
            int x = to->hp -1;
            to->hp += fheap[pos+1]+2;
            return x;
        }
    }

    to->hp++;
    fheap[pos] = FWD;
    fheap[pos+1] = cpos;

    return cpos;
}

/*
* Scavenge. Evacuate references found in the to-heap.
* End of switch assumes pointer at next tag.
*/
void scavenge(heap* from, heap* to){
    int i=0;
    while(i < to->hp){
        switch(to->heap[i]){
            // Don't need to do anything.
            case INT:
            case BOOL:
            case WEAK:
                i+=2;
                break;

            // Don't need to do anything.
            case STRING:
                i++;
                while(to->heap[i] != 0)
                    i++;
                i++;
                break;

            // Evac both references.
            case RANGE:
                to->heap[i+1] = evac(to->heap[i+1], from, to);
                to->heap[i+2] = evac(to->heap[i+2], from, to);
                i+=3;
                break;

            case BIGDATA:
                {
                    int* bdh = bigdataheap->heap;
                    i++;
                    int lim = bdh[to->heap[i] + 1] + to->heap[i] + 3;
                    int x = to->heap[i];
                    x+=2;
                    while(++x < lim)
                        bdh[x] = evac(bdh[x], from, to);
                    i++;
                    break;
                }
            case LAMBDA:
                {
                    int lim = i + to->heap[i+2] + 3;
                    i+=2;
                    while(++i < lim)
                        to->heap[i] = evac(to->heap[i], from, to);
                    break;
                }

            case DATA:
                {
                    int lim = i + datacons->heap[to->heap[i+1]] + 2;
                    i++;
                    while(++i < lim)
                        to->heap[i] = evac(to->heap[i], from, to);
                    break;
                }

            case SOFT:
                {
                    if(from->hp < from->hpLimit / 2)
                        //don't collect if >50% memory left
                        to->heap[i+1] = evac(to->heap[i+1],from,to);
                    else
                        to->heap[i+1] = -1;
                    i+=2;
                    break;
                }

            // If cons is false, don't collect value.
            case PHANTOM:
                to->heap[i+1] = to->heap[i+2] ? evac(to->heap[i+1], from, to) : -1;
                i+=3;
                break;
        }
    }
}
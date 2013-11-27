#include "heap.h"
#define nextelem h->heap[++(h->hp)]

/*
* Create heaps
*/
heap* initHeaps(){
    dataConsCreate();
    bigdataHeapCreate();
    bigdataindex = stackCreate();
    return heapCreate();
}

heap* heapCreate(){
    heap* h = malloc(sizeof(heap));
    h->hpLimit = HEAP_SIZE;
    h->hp = 0;
    return h;
}

void dataConsCreate(){
    datacons = malloc(sizeof(heap));
    datacons->hpLimit = HEAP_SIZE / 3;
    datacons->hp = 0;
}

void bigdataHeapCreate(){
    bigdataheap = malloc(sizeof(heap));
    bigdataheap->hpLimit = HEAP_SIZE / 4;
    bigdataheap->hp = 0;
}

/*
 * Add data to heap
 * Assumes space is available
 * After add, hp will point to next empty cell
 */
void heapAdd(heap* h, type t, void* data){
    // Set next elem to input flag
    h->heap[h->hp] = t;

    // Copy values to heap
    switch(t){
        // Simple cases -- only one value to be copied
        case INT:
        case BOOL:
        case SOFT:
        case WEAK:
            nextelem = *(int*)data;
            break;

        // Copy until terminating character
        case STRING:
            {
                char* p = (char*)data;
                nextelem = (int)p[0];
                while((char*)(p++)[0] != '\0')
                    nextelem = (int)p[0];
                break;
            }

        // Range and phantom -- 2 values to copy
        case RANGE:
        case PHANTOM:
            {   
                int* p = (int*)data;
                nextelem = p[0];
                nextelem = p[1];
                break;
            }

        // BigData and Lambda -- same structure, different order
        // of arguments.
        case LAMBDA:
            {
                int* p = (int*)data;
                nextelem = p[0];
                nextelem = p[1];
                int i = 0;
                while(i<p[1]){
                    nextelem = p[i+2];
                    i++;
                }
                break;
            }
        case BIGDATA: 
            {
                int* p = (int*)data;

                nextelem = bigdataheap->hp;

                bigdataheap->heap[bigdataheap->hp] = BDHEAP;
                (bigdataheap->hp)++;
                memcpy(&bigdataheap->heap[bigdataheap->hp], &p[0], sizeof(int)*(p[0]+2));
                bigdataheap->hp += p[0]+2;
                break;
            }

        // Data does not contain length information
        // copy value into constructor table, where length
        // can be found
        case DATA:
            {
                int* p = (int*)data;
                datacons->heap[datacons->hp] = p[0];
                nextelem = datacons->hp;
                int i=0;
                while(i<p[0]){
                    nextelem = p[i+1];
                    i++;
                }
                (datacons->hp)++;
                break;
            }
    }
    (h->hp)++;
}

/*
* Print each heap cell
*/
void simplePrintHeap(heap* h){
    int i;
    for(i=0; i<HEAP_SIZE; i++)
        printf("%i:%i ",i,h->heap[i]);
    puts("");
}

/*
* Pretty print the stack.
* Each object will be printed on a new line
* in a hopefully human-readable form.
* Pointer assumed to be to last element read at end of switch
*/
void printHeap(heap* h){
    int i=0;    //iterator
    int* heap = h->heap;

    while(i < h->hp){
        printf("%i ", i);   //current cell loc
        switch(heap[i]){
            case INT:
                printf("INT %i", heap[++i]);
                break;
            case BOOL:
                printf("BOOL %s", (int)heap[++i] ? "True" : "False");
                break;
            case STRING:
                printf("STRING ");
                while(heap[++i] != 0)
                    printf("%c",(char)heap[i]);
                break;

            case BIGDATA:
                {
                    int* bdh = bigdataheap->heap;
                    i++;
                    printf("BIGDATA n:%i c:%i", bdh[heap[i]+1], bdh[heap[i]+2]);

                    int lim = bdh[heap[i]+1];
                    int x = 0;
                    int c = heap[i]+3;
                    while(x < lim){
                        printf(" %i",bdh[c+x]);
                        x++;
                    }
                    break;
                }

            case BDHEAP:
                {
                    printf("BIGDATA n:%i c:%i", heap[i+1], heap[i+2]);
                    int lim = heap[i+1];
                    int x = 0;
                    i+=3;
                    while(x < lim){
                        printf(" %i",heap[i+x]);
                        x++;
                    }
                    i+=lim-1;
                    break;
                }

            case LAMBDA:
                {
                    printf("LAMBDA f:%i n:%i", heap[i+1], heap[i+2]);
                    int lim = heap[i+2];
                    int x = 0;
                    i+=3;
                    while(x < lim){
                        printf(" %i",heap[i+x]);
                        x++;
                    }
                    i+=lim-1;
                    break;
                }

            case SOFT:
                printf("SOFT %i",heap[++i]);
                break;
            case WEAK:
                printf("WEAK %i",heap[++i]);
                break;
            case PHANTOM:
                printf("PHANTOM %i c:%i",heap[i+1],heap[i+2]);
                i+=2;
                break;
            case RANGE:
                printf("RANGE %i %i",heap[i+1],heap[i+2]);
                i+=2;
                break;

            case DATA:
                {
                    printf("DATA c:%i", heap[i+1]);
                    int lim = datacons->heap[heap[i+1]];
                    int x = 0;
                    i+=2;
                    while(x < lim){
                        printf(" %i",heap[i+x]);
                        x++;
                    }
                    i+=lim-1;

                    break;
                }
        }
        printf("\n");
        i++;
    }
}

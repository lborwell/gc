#include "heap.h"
#define nextelem h->heap[++(h->hp)]

heap* datacons;

heap* initHeaps(){
    dataConsCreate();
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

/*
 * Add data to heap
 * Assumes spaces is available
 * Will overwrite to-space if not
 */
void heapAdd(heap* h, type t, void* data){
    h->heap[h->hp] = t;
    switch(t){
        case INT:
        case BOOL:
        case SOFT:
        case WEAK:
            nextelem = *(int*)data;
            break;

        case STRING:
            {
                char* p = (char*)data;
                nextelem = (int)p[0];
                while((char*)(p++)[0] != '\0')
                    nextelem = (int)p[0];
                break;
            }

        case RANGE:
        case PHANTOM:
            {   
                int* p = (int*)data;
                nextelem = p[0];
                nextelem = p[1];
                break;
            }

         
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
                nextelem = p[0];
                nextelem = p[1];
                int i = 0;
                while(i<p[0]){
                    nextelem = p[i+2];
                    i++;
                }
                break;
            }

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

void simplePrintHeap(heap* h){
    int i;
    for(i=0; i<HEAP_SIZE; i++)
        printf("%i:%i ",i,h->heap[i]);
    puts("");
}

void printHeap(heap* h){
    int i=0;
    int* heap = h->heap;
    while(i < h->hp){
        printf("%i ", i);
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
                    printf("LAMBDA c:%i n:%i", heap[i+1], heap[i+2]);
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
                printf("PHANTOM %i %i",heap[i+1],heap[i+2]);
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

#include "heap.h"
#define nextelem h->heap[++(h->hp)]

heap* heapCreate(){
    heap* h = malloc(sizeof(heap));
    h->hpLimit = HEAP_SIZE/2;
    return h;
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
                while((p++)[0] != '\0')
                    nextelem = (int)p[0];
                nextelem = (int)'\0';
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
        case BIGDATA:
            {
                int* p = (int*)data;
                nextelem = p[0];
                nextelem = p[1];
                int i = 0;
                while(i<=p[0]){
                    nextelem = p[i+2];
                    i++;
                }
                break;
            }

    }
    (h->hp)++;
}


void printHeap(heap* h){
    int i=0;
    int* heap = h->heap;
    while(i < h->hp){
        switch(heap[i]){
            case INT:
                printf("INT %i", heap[++i]);
                break;
            case BOOL:
                printf("BOOL %s", (int)heap[++i] ? "True" : "False");
                break;
            case STRING:
                printf("STRING ");
                while((char*)heap[i++] != '\0')
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
                    i+=lim;
                    break;
                }
            case LAMBDA:
                {
                    printf("LAMBDA n:%i c:%i", heap[i+1], heap[i+2]);
                    int lim = heap[i+1];
                    int x = 0;
                    i+=3;
                    while(x < lim){
                        printf(" %i",heap[i+x]);
                        x++;
                    }
                    i+=lim;
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
        }
        printf("\n");
        i++;
    }
}

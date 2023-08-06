#include <stdio.h>
#include <stdlib.h>
#include "allocations.h"


struct KeyEventData *createData(int t){
    struct KeyEventData* data = malloc(sizeof(struct KeyEventData) * t);
    return data;
}

void destroyData(struct KeyEventData *data){
    free(data);
    data = NULL;
}

int *keyOccurencesAlloc(int t){
    int * keyOccurencece = malloc(sizeof(int*)*t);
    for(int i=0;i<t;i++){
        keyOccurencece[i] = 0;
    }
    return keyOccurencece;
}
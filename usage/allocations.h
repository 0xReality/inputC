#ifndef ALLOCATIONS_H
#define ALLOCATIONS_H
#include "getFile.h"



/*
    getData: takes void 
    returns keyEventData pointer or null

*/
struct KeyEventData *createData();

/*
    getData  usage: keyEventData pt, returns keyEventData pointer or null

*/
struct KeyEventData *refreshData(struct KeyEventData *data, int lastUpdatePos);

/* 
    Allocate occurences
*/
int *keyOccurencesAlloc(int t);

/*
    destroyData  usage: keyEventData pt returns void

*/
void destroyData(struct KeyEventData *data);


#endif

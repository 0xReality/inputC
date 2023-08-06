#ifndef USEDATA_H
#define USEDATA_H
#include "getFile.h"

/*
    pv() takes data start and end, prints out values return void
*/
void pv(struct KeyEventData *data, int start, int end);


int highestKey(struct KeyEventData *data, int t);

int **keyOccurences(struct KeyEventData *data, int t);

double getMean(struct KeyEventData *data);

double getTimeDiff(struct KeyEventData *data);
#endif
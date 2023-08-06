#include <stdio.h>
#include <stdlib.h>
#include "getFile.h"
#include "allocations.h"

void pv(struct KeyEventData *data, int start, int end){
    int i;
    for (i = start; i < end; i++) {
        printf("%02d:%02d:%02d %d %.6lf\n",
            data[i].time.hour, data[i].time.minute, data[i].time.seconds,
            data[i].key_pressed, data[i].dwell_time);
    }
}

int highestKey(struct KeyEventData *data, int t){
    int i;
    int key = data[0].key_pressed;
    for(i=0;i<t;i++){
        if( data[i].key_pressed > key){
            key = data[i].key_pressed;
        }
    }
    return key;
}



double getMean(struct KeyEventData *data){
    int key = getLines(data);
    double sum = 0.f;
    for(int i =0;i<key;i++){
        sum+=data[i].dwell_time;
    }
    return sum / (double)key;
}

int compareTimes(const void *a, const void *b) {
    const struct KeyEventData *eventA = (const struct KeyEventData *)a;
    const struct KeyEventData *eventB = (const struct KeyEventData *)b;

    int timeA = eventA->time.hour * 3600 + eventA->time.minute * 60 + eventA->time.seconds;
    int timeB = eventB->time.hour * 3600 + eventB->time.minute * 60 + eventB->time.seconds;

    return timeA - timeB;
}


double getTimeDiff(struct KeyEventData *data){
    int key = getLines(data);
    qsort(data, key, sizeof(struct KeyEventData), compareTimes);

    double sumTimeDifference = 0.0;
    int numDifferences = 0;

    for (int i = 1; i < key; i++) {
        int prevTimeInSeconds = data[i - 1].time.hour * 3600 + data[i - 1].time.minute * 60 + data[i - 1].time.seconds;
        int currentTimeInSeconds = data[i].time.hour * 3600 + data[i].time.minute * 60 + data[i].time.seconds;
        int timeDifferenceInSeconds = currentTimeInSeconds - prevTimeInSeconds;

        // Only consider positive time differences
        if (timeDifferenceInSeconds >= 0) {
            sumTimeDifference += timeDifferenceInSeconds;
            numDifferences++;
        }
    }

    // Calculate the mean time difference
    double meanTimeDifference = 0.0;
    if (numDifferences > 0) {
        meanTimeDifference = (double)sumTimeDifference / numDifferences;
    }

    return meanTimeDifference;
}







int *keyOccurences(struct KeyEventData *data, int t){
    int i;
    int key_pressed;
    int *tab = keyOccurencesAlloc(t);
    for(i=0;i<t;i++){
        key_pressed = data[i].key_pressed;
        tab[key_pressed]++;        
    }
    return tab;
}
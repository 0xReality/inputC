#ifndef GETFILE_H
#define GETFILE_H

struct Time {
    int hour;
    int minute;
    int seconds;
};

struct KeyEventData {
    struct Time time;
    int key_pressed;
    double dwell_time;
    int size;
    char *fileName;
};

/*
    getData 
    returns keyEventData pointer or null

*/
struct KeyEventData *getData(char* filename);


int getLines(struct KeyEventData *data);

#endif

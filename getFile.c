#include <stdio.h>
#include <stdlib.h>
#include "getFile.h"
#include "allocations.h"
#define MAX_LINE_LENGTH 100



struct KeyEventData *getData(char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    int len = ftell(file);
    fseek(file, 0, SEEK_SET);
    int i =0;
    char line[MAX_LINE_LENGTH];
    struct KeyEventData* data = createData(len);
    while (fgets(line, sizeof(line), file)) {

        int hour, minute, seconds;
        double dwell_time;
        int key_pressed;
        // Parse the line and check for valid data
        if (sscanf(line, "%d:%d:%d %d %lf",
                   &hour, &minute, &seconds, &key_pressed, &dwell_time) == 5) {
            data[i].time.hour = hour;
            data[i].time.minute = minute;
            data[i].time.seconds = seconds;
            data[i].key_pressed = key_pressed;
            data[i].dwell_time = dwell_time;
            data->size = len;
            data->fileName = filename;
            i++;
        } else {
            printf("Invalid data format in line: %s, no more data being collected", line);
            break;
        }
    }
    fclose(file);
    printf("succefully initialized data, with %d indexes\n", i);
    return data;
}



int getLines(struct KeyEventData *data){
    FILE* file = fopen(data->fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
       int num_lines = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        num_lines++;
    }

    fclose(file);
    return num_lines;
}

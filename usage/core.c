#include <stdio.h>
#include <stdlib.h>
#include "allocations.h"
#include "getFile.h"
#include "useData.h"

int main()
{
    char* filename = "user_writing_data2.txt";
    struct KeyEventData *data = getData(filename);
    keyOccurences(data, 9430);
    printf("mean of data is: %lf\n", getMean(data));
    printf("time diff of data is: %lfs\n", getTimeDiff(data));
    destroyData(data);
    return 0;
}

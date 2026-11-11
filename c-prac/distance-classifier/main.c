#include <stdio.h>

#include "proximity.h"


int main(void) {
    //data to test our programs!
    int listDistances[] = {-90, 100, 200, 345, 18, 23, -21, -40, 100000, 10001, 405, 399};
    //size of an array is the size of the entire array / size of one element in the array
    size_t arraySize = sizeof(listDistances) /  sizeof(listDistances[0]);

    //initialize each member var to 0
    SensorHistory records = {0};


    printf("------------------\n");
    //loop through the data and call needed functions
    for (size_t i = 0; i < arraySize; i++) {
        SensorData classifyResult = classifyDistance(listDistances[i]);
        updateHistory(&classifyResult, &records);

        printf("Index: %zu\n", i);
        printf("Raw Distance %d\n", classifyResult.distance);
        printf("STATE: %s\n", enumToString(classifyResult.identifier));
        printf("VALID: %d\n", classifyResult.isValid);
        printf("------------------\n");
    }

    //print the content of the records
    printf("------------------\n");
    printf("History RECORDS\n");

    printf("Valid Readings: %d\n", records.validReadings);
    printf("Invalid Readings: %d\n", records.invalidReadings);
    printf("Transition Counts: %d\n", records.transitionsCount);


    return 0;
}



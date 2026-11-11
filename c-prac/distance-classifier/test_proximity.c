#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "proximity.h"


//testing suite make functions to run each ones

//test the classify distances
static void test_classify(void) {
    //printf("Testing the classify function with distances!\n");

    //check each identifier correlates to each distance bound
    assert(classifyDistance(401).identifier == ERROR);
    assert(classifyDistance(-1).identifier == ERROR);

    assert(classifyDistance(0).identifier == TOO_CLOSE);
    assert(classifyDistance(10).identifier == TOO_CLOSE);

    assert(classifyDistance(11).identifier == NEAR);
    assert(classifyDistance(30).identifier == NEAR);

    assert(classifyDistance(31).identifier == MEDIUM);
    assert(classifyDistance(100).identifier == MEDIUM);


    assert(classifyDistance(140).identifier == FAR);
    assert(classifyDistance(400).identifier == FAR);

    printf("Classify Test Success!\n");
}


static void test_convert(void) {
    ProximityState states[] = {FAR, MEDIUM, NEAR, TOO_CLOSE, ERROR};
    const char* expected[] = {"FAR", "MEDIUM", "NEAR", "TOO_CLOSE", "ERROR"};

    size_t arraySize = sizeof(states) / sizeof(states[0]);

    for (int i = 0; i < arraySize; i++) {
        assert(strcmp(enumToString(states[i]), expected[i]) == 0);
    }

    printf("Convert Test Success!\n");
}

static void test_history(void) {
    SensorHistory records = {0};
    
    SensorData data1 = classifyDistance(100);
    updateHistory(&data1, &records);

    //check that by adding a data with 100 distance it must be valid in our history
    assert(records.validReadings == 1);
    assert(records.prevState == MEDIUM);
    assert(records.transitionsCount == 0);
    assert(records.invalidReadings == 0);
    //this means its going to be MEDIUM, true, validReading++, transitionCount is equal to 0

    SensorData data2 = classifyDistance(-90);
    updateHistory(&data2, &records);
    assert(records.validReadings == 1);
    assert(records.prevState == ERROR);
    assert(records.transitionsCount == 1);
    assert(records.invalidReadings == 1);
    //this means invalid increments and transition increments and the prevState would now be error

    SensorData data3 = classifyDistance(-50);
    updateHistory(&data3, &records);
    assert(records.validReadings == 1);
    assert(records.prevState == ERROR);
    assert(records.transitionsCount == 1);
    assert(records.invalidReadings == 2);
    //getting an error distance means we increment invalid keep transition the same cause it was error last time and prevstate is still error

    SensorData data4 = classifyDistance(400);
    updateHistory(&data4, &records);
    assert(records.validReadings == 2);
    assert(records.prevState == FAR);
    assert(records.transitionsCount == 2);
    assert(records.invalidReadings == 2);
    //adding another valid 400 distance data results in  valid++ transition++ and prev is now FAR

    printf("History Test Success!\n");
}


int main(void) {

    printf("Starting each test cases!\n");

    test_classify();

    test_convert();

    test_history();


    return 0;
}
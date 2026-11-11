#include "proximity.h"

SensorData classifyDistance(int distance) {
    SensorData data;

    data.distance = distance;

    if (distance < 0 || distance > 400) {
        data.identifier = ERROR;
        data.isValid = false;
    }
    else if (distance >= 0 && distance <= 10) {
        data.identifier = TOO_CLOSE;
        data.isValid  = true;
    }
    else if (distance >= 11 && distance <= 30) {
        data.identifier = NEAR;
        data.isValid = true;
    }
    else if (distance >= 31 && distance <= 100) {
        data.identifier = MEDIUM;
        data.isValid = true;
    }
    else if (distance >= 101 && distance <=  400) {
        data.identifier = FAR;
        data.isValid = true;
    }

    return data;
}

//helper function to convert enum to string
const char* enumToString(ProximityState state) {
    const char* result;

    switch (state) {
        case FAR:
            result = "FAR";
            break;
        case MEDIUM:
            result = "MEDIUM";
            break;
        case NEAR:
            result = "NEAR";
            break;
        case TOO_CLOSE:
            result = "TOO_CLOSE";
            break;
        case ERROR:
            result = "ERROR";
            break;
        default:
            result = "UNKNOWN";
            break;
    }
    return result;
}

void updateHistory(SensorData* data, SensorHistory* history) {
    if (!data || !history) {
        return;
    }


    if (data->isValid) {
        history->validReadings++;
    } else {
        history->invalidReadings++;
    }


    int readingCount = history->invalidReadings + history->validReadings;
    if (history->prevState != data->identifier && readingCount > 1) {
       history->transitionsCount++;
    }
    history->prevState = data->identifier;
}
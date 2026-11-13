#ifndef PROXIMITY_H
#define PROXIMITY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FAR,
    MEDIUM,
    NEAR,
    TOO_CLOSE,
    ERROR,
} ProximityState;

typedef struct {
    int distance;
    bool isValid;
    ProximityState identifier;
} SensorData;

typedef struct {
    int validReadings;
    int invalidReadings;
    int transitionsCount;
    ProximityState prevState;
} SensorHistory;

// UpdateHistory helper function mutator
void updateHistory(SensorData* data, SensorHistory* history);

// Helper to convert the enum found into a string for display
const char* enumToString(ProximityState state);

SensorData classifyDistance(int distance);

#ifdef __cplusplus
}
#endif

#endif // PROXIMITY_H

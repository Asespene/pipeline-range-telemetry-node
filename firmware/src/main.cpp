#include <Arduino.h>

extern "C" {
  #include "proximity.h"
}


void setup() {
  Serial.begin(9600);

  delay(1500);

  const int testDistanceData[] = {300, 75, 20, 5, -1, 250};

  const int arraySize = sizeof(testDistanceData) / sizeof(testDistanceData[0]);

  SensorHistory records = {0};

  for (int i = 0; i < arraySize; i++) {
    Serial.print("Data #: ");
    Serial.print(i);
    Serial.print("(");
    Serial.print(testDistanceData[i]);
    Serial.print("): ");
    SensorData data = classifyDistance(testDistanceData[i]);
    Serial.println(enumToString(data.identifier));

    updateHistory(&data, &records);

    Serial.print("Valid Readings: ");
    Serial.println(records.validReadings);

    Serial.print("Invalid Readings: ");
    Serial.println(records.invalidReadings);

    Serial.print("Transition Counts: ");
    Serial.println(records.transitionsCount);

    Serial.println("------------------------");
  }

  Serial.println("Test done!");
}

void loop() {
  int analogValue = analogRead(A0);

  int distanceValue = map(analogValue, 0, 1023, -1000, 1000);

  SensorData data = classifyDistance(distanceValue);
  static SensorHistory liveRecords = {};

  updateHistory(&data, &liveRecords);

  static size_t counter = 0;

  Serial.print("Data #: ");
  Serial.println(counter);

  Serial.print("Distance: ");
  Serial.println(data.distance);

  Serial.print("STATE: ");
  Serial.println(enumToString(data.identifier));

  Serial.print("Valid Reading: ");
  Serial.println(liveRecords.validReadings);

  Serial.print("Invalid Reading: ");
  Serial.println(liveRecords.invalidReadings);

  Serial.print("Transition Counts: ");
  Serial.println(liveRecords.transitionsCount);



  Serial.println();

  counter++;
  delay(1000);
}

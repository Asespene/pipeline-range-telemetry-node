#include <Arduino.h>

extern "C" {
  #include "proximity.h"
}


void setup() {
  Serial.begin(9600);

  delay(1500);

  const int distanceData[] = {300, 75, 20, 5, -1, 250};

  const int arraySize = sizeof(distanceData) / sizeof(distanceData[0]);

  SensorHistory records = {0};

  for (int i = 0; i < arraySize; i++) {
    Serial.print("Data #: ");
    Serial.print(i);
    Serial.print("(");
    Serial.print(distanceData[i]);
    Serial.print("): ");
    SensorData data = classifyDistance(distanceData[i]);
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

}

void loop() {
 
}

#include <Arduino.h>

#define INCHES 0.0135 

//the trigPin triggers a soundwave that will be taken as an input by the echoPin
uint8_t trigPin = 10;
// the echoPin takes the sound wave from the trigPin activation as an input of the device and calculates the exact distance
uint8_t echoPin = 9;



void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Your code here
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);


  digitalWrite(trigPin, HIGH);
  //have the sensor create a signal, can only occur if it gets 5V for more than 10ms 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //returns the RTT of the sound wave signal from the trigPin.
  //listen at the echoPin for when it transitions from Low --> HIGH. This means that the soundwave was emitted and it came back.
  float roundTripTime = pulseIn(echoPin, HIGH, 30000);

  //calculation of distance in inches
  float oneWayDistance = (roundTripTime * INCHES) / 2;

  Serial.print("Distance: ");
  Serial.print(oneWayDistance);
  Serial.println(" in");

  delay(250);
}

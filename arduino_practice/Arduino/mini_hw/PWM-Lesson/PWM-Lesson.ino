const uint8_t ledPins[] = {9};

const int numberOfPins = sizeof(ledPins) / sizeof(ledPins[0]);


const int bright = 255;
const int off = 0;
 
void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < numberOfPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ledPins[0], bright);
}

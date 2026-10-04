const uint8_t ledPins[] = {9, 10};

const int numberOfPins = sizeof(ledPins) / sizeof(ledPins[0]);

//use numbers instead for analogWrite
const int maxBright = 255;
const int halfBright = 125;
const int halfHalfBright = 50;
const int dim = 25;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < numberOfPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //make  a program that goes from blank to dim to half bright to bright!

  for (int i = 0; i <= maxBright; i += 5) {
    analogWrite(ledPins[0], i);
    analogWrite(ledPins[1], i);
    delay(500);

    if (i == 255) {
      i = 0;
    }
  }

}

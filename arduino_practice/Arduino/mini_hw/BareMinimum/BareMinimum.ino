
//map each pins into an array instead
const int ledPins[4] = {7, 8, 9, 10};


void setup() {
  // put your setup code here, to run once:
 for (int i = 0; i < 4l i++) {
    pinMode(ledPins[i], OUTPUT);
 }

}

void loop() {
  // put your main code here, to run repeatedly:
 
  //creating a binary counter from 0 to 15
  //this represents each number from 0 to 15
  for (int counter = 0; counter < 16; counter++) {
    //now each number we have to represent each one using the 4 leds
    for (int bit = 0; bit < 4; bit++) {
        digitalWrite(ledPins[bit], LOW);
        delay(1000);
    }
  }
}

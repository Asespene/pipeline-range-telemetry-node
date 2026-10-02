
//map each pins into an array instead
const int ledPins[] = {7, 8, 9, 10};

const int number = 15;


const int numberOfPins = sizeof(ledPins) / sizeof(ledPins[0]);

void setup() {
  // put your setup code here, to run once:
 for (int i = 0; i < numberOfPins; i++) {
    pinMode(ledPins[i], OUTPUT);
 }

}

void loop() {
  //the counter represents our iteration to represent each numbers!
  for (int counter = 0; counter <= number; counter++) {
    for (int bit = 0; bit < numberOfPins; bit++) {
      bool bitStatus = bitRead(counter, bit);
      //if bitStatus is true meaning that value at that bit position is a 1, then return the value of the bit meaning 1 or tru
      digitalWrite(ledPins[bit], bitStatus);
    }
    delay(2000);
  }
}

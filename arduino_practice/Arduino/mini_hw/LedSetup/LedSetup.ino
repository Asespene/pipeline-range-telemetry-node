void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Red Blinks 5 Times
  for (int i = 0; i < 5; i++) {
    digitalWrite(8, HIGH);
    delay(250);
    digitalWrite(8, LOW);
    delay(250);
  }

  // Green Blinks 10 Times
  for (int i = 0; i < 10; i++) {
    digitalWrite(9, HIGH);
    delay(250);
    digitalWrite(9, LOW);
    delay(250);
  }

  // Blie Blinks 15 Times
  for (int i = 0; i < 15; i++) {
    digitalWrite(10, HIGH);
    delay(250);
    digitalWrite(10, LOW);
    delay(250);
  }
  
 

 
}

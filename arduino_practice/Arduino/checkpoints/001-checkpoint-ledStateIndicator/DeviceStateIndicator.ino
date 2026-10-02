const int ledPins[] = {7, 8, 9, 10, 11};

const int numberOfPins =sizeof(ledPins) / sizeof(ledPins[0]);


enum class NodeState : uint8_t {
  STATE_BOOTING = 0,
  STATE_READY = 1, 
  STATE_CLEAR = 2,
  STATE_CAUTION = 3,
  STATE_OBJECT_NEAR = 4,
  STATE_SENSOR_ERROR = 5,
  STATE_NETWORK_ERROR = 6,
  STATE_OFFLINE = 7,
};

void displayState(NodeState state) {
  uint8_t code = static_cast<uint8_t>(state);
  for (int bit = 0; bit < numberOfPins; bit++) {
    bool bitStatus = bitRead(code, bit);

    digitalWrite(ledPins[bit], bitStatus);
  }
}


void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < numberOfPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  NodeState obj = NodeState::STATE_CAUTION;

  displayState(obj);

}

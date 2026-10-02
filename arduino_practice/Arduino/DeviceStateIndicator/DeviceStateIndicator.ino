const int ledPins[] = {7, 8, 9, 10, 11};

const int numberOfPins =sizeof(ledPins) / sizeof(ledPins[0]);


enum class NodeState : uint8_t {
  STATE_BOOTING = 0,
  STATE_READY = 10, 
  STATE_CLEAR = 2,
  STATE_CAUTION = 15,
  STATE_OBJECT_NEAR = 13,
  STATE_SENSOR_ERROR = 27,
  STATE_NETWORK_ERROR = 28,
  STATE_OFFLINE = 31
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
  }const int maxNumberStatus = 4;

}

void loop() {
  // put your main code here, to run repeatedly:
  NodeState obj = NodeState::STATE_SENSOR_ERROR;

  displayState(obj);

}

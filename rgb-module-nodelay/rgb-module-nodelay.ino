const int RED_PIN =  10;
const int GREEN_PIN = 11;
const int BLUE_PIN = 12;

int stateLength = 7;
int ledStates[7][3] = {
  {HIGH, LOW, LOW},
  {LOW, HIGH, LOW},
  {LOW, LOW, HIGH},
  {HIGH, HIGH, LOW},
  {LOW, HIGH, HIGH},
  {HIGH, LOW, HIGH},
  {HIGH, HIGH, HIGH}
};

int tickCount = 0;
unsigned long previousMillis = 0; 
const long interval = 100;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int stateIndex = tickCount ++ % stateLength;

    digitalWrite(RED_PIN, ledStates[stateIndex][0]);
    digitalWrite(GREEN_PIN, ledStates[stateIndex][1]);
    digitalWrite(BLUE_PIN, ledStates[stateIndex][2]);
  }
}
#define LED_PIN 13
#define KEY 2
#define BUZZER_PIN 3
int keyStatus=0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(KEY, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
  scanKey();
  if (keyStatus == 1) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
}

void scanKey() {
  keyStatus = 0;
  if (digitalRead(KEY) == LOW) {
    delay(20);	// Delay to avoid inverting
    if (digitalRead(KEY) == LOW) {
      buzzerBeep();
      keyStatus = 1;
      while(digitalRead(KEY) == LOW);
    }
  }
}

void buzzerBeep() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}

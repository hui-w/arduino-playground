// Pins for seven-segment display
/*
 * const int b = 6;
 * const int c = 5;
 * const int d = 11;
 * const int e = 10;
 * const int f = 8;
 * const int g = 9;
 * const int dp = 4;
*/
const int SEGMENT_PINS[8] = {7, 6, 5, 11, 10, 8, 9, 4};

// Digits encoding
const unsigned char DIGITS_ENCODING[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 0, 0, 0, 0}, {1, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 0, 0, 1}, {0, 1, 1, 0, 0, 1, 1}, {1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}};

// Show digit
void showDigit(unsigned char digit) {
  unsigned char encoding[7] = DIGITS_ENCODING[digit % 10];
  for (unsigned char i = 0; i < 7; i++) {
    digitalWrite(SEGMENT_PINS[i], encoding[i] == 1 ? HIGH : LOW);
  }

  // Blur the dot
  digitalWrite(dp, LOW);
}

void setup() {
  int i;
  for (i = 4; i <= 11; i++) {
    pinMode(i, OUTPUT);  // Set pin 4-11 as output
  }
}

void loop() {
  while (1) {
    showDigit(0);
    delay(1000);
    showDigit(1);
    delay(1000);
    showDigit(2);
    delay(1000);
    showDigit(3);
    delay(1000);
    showDigit(4);
    delay(1000);
    showDigit(5);
    delay(1000);
    showDigit(6);
    delay(1000);
    showDigit(7);
    delay(1000);
    showDigit(8);
    delay(1000);
    showDigit(9);
    delay(1000);
  }
}

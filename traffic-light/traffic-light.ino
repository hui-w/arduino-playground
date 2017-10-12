// Pins for LEDs
// [RED, YELLOW, GREEN]
const int LED_PINS[3] = {2, 3, 12};

// Pins for seven-segment display
// [a, b, c, d, e, f, g, dp]
const int SEGMENT_PINS[8] = {7, 6, 5, 11, 10, 8, 9, 4};

// Digits encoding
const unsigned char DIGITS_ENCODING[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, {0, 1, 1, 0, 0, 0, 0}, {1, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 0, 0, 1}, {0, 1, 1, 0, 0, 1, 1}, {1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}};

// Show digit
void showDigit(unsigned char digit) {
  unsigned char j = digit % 10;
  for (unsigned char i = 0; i < 7; i++) {
    digitalWrite(SEGMENT_PINS[i], DIGITS_ENCODING[j][i] == 1 ? HIGH : LOW);
  }

  // Blur the dot
  digitalWrite(SEGMENT_PINS[7], LOW);
}

// Luminate LED
// Set ledIndex = -1 to luminate none LED
void luminateLED(unsigned char ledIndex) {
  for (unsigned char i = 0; i < 3; i++) {
    if (ledIndex == i) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
}

// Count down
void countDown(unsigned char start) {
  unsigned char j = start % 10;
  for (unsigned char i = j; i > 0; i--) {
    showDigit(i);
    delay(500);
  }
}

void setup() {
  int i;
  for (i = 2; i <= 12; i++) {
    pinMode(i, OUTPUT);  // Set pin 4-11 as output
  }
}

void loop() {
  while (1) {
    luminateLED(0);
    countDown(9);
    luminateLED(1);
    countDown(9);
    luminateLED(2);
    countDown(9);
  }
}

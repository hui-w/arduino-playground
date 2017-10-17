#include "driver.h"

void setup() {
  // Set the digital pins as output
  /*
   * On UNO, digitalWrite() works on pins 3, 5, 6, 9, 10, and 11.
   * https://www.arduino.cc/en/Reference/analogWrite
   */
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      pinMode(DIGITAL_PINS[i][j], OUTPUT);
    }
  }

  // Use input pullup for button pin
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH); 

  // Freeze for 2 seconds before starting
  delay(2000);
  
  digitalWrite(13, LOW);

  // Go backward
  driveCar(BACKWARD, BACKWARD, 20);
  driveCar(BREAK, BREAK, 10);

  // Go forward
  driveCar(FORWARD, FORWARD, 20);
  driveCar(BREAK, BREAK, 10);

  // Turn left; Turn right; Break
  driveCar(BREAK, FORWARD, 40);
  driveCar(FORWARD, BREAK, 40);
  driveCar(BREAK, BREAK, 10);

  // Spin right; Spin left; Break
  driveCar(FORWARD, BACKWARD, 80);
  driveCar(BACKWARD, FORWARD, 80);
  driveCar(BREAK, BREAK, 10);
}
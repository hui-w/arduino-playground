/*
 * The basic control to the car:
 * Go forward, go backward, turn left and turn right
 */

const int MOTOR_LEFT = 0;
const int MOTOR_RIGHT = 1;
const int BACKWARD = -1;
const int BREAK = 0;
const int FORWARD = 1;

/*
 * 9 - Left motor backward (IN1)
 * 5 - Left motor forward (IN2)
 * 6 - Right motor forward (IN3)
 * 10 - Right motor backward (IN4)
 */
const int DIGITAL_PINS[2][2] = { { 5, 9 }, { 6, 10 }};

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
}

void loop() {
  // Freeze for 2 seconds before starting
  delay(2000);

  // Go backward
  driveCar(BACKWARD, BACKWARD, 5);
  driveCar(BREAK, BREAK, 10);

  // Go forward
  driveCar(FORWARD, FORWARD, 5);
  driveCar(BREAK, BREAK, 10);

  // Turn left; Turn right; Break
  driveCar(BREAK, FORWARD, 10);
  driveCar(FORWARD, BREAK, 10);
  driveCar(BREAK, BREAK, 10);

  // Spin right; Spin left; Break
  driveCar(FORWARD, BACKWARD, 20);
  driveCar(BACKWARD, FORWARD, 20);
  driveCar(BREAK, BREAK, 10);
}

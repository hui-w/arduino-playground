/*
 * The basic control to the car:
 * Go forward, go backward, turn left and turn right
 */

/*
 * 9 - Left motor backward (IN1)
 * 5 - Left motor forward (IN2)
 * 6 - Right motor forward (IN3)
 * 10 - Right motor backward (IN4)
 */
int pins[2][2] = {
  { 5, 9 },
  { 6, 10 }
};

/*
 * Drive the motor
 *
 * motorIndex  >>                0: left;    1: right
 * driveMode   >>  -1: backward; 0: break;   1: forward
 */
void driveMotor(int motorIndex, int driveMode) {
  int pinForward = pins[motorIndex][0];
  int pinBackward = pins[motorIndex][1];

  if (driveMode == -1) {
    // Backward
    digitalWrite(pinForward, LOW);
    digitalWrite(pinBackward, HIGH);
    /*
     * Writes an analog value (PWM wave) to a pin drive a motor at various speeds.
     * PWM: Pulse Width Modulation (0~255)
     * https://www.arduino.cc/en/Tutorial/PWM
     */
    analogWrite(pinForward, 0);
    analogWrite(pinBackward, 200);
  } else if (driveMode == 0) {
    // Break
    digitalWrite(pinForward, LOW);
    digitalWrite(pinBackward, LOW);
    analogWrite(pinForward, 0);
    analogWrite(pinBackward, 0);
  } else if (driveMode == 1) {
    // Forward
    digitalWrite(pinForward, HIGH);
    digitalWrite(pinBackward, LOW);
    analogWrite(pinForward, 200);
    analogWrite(pinBackward, 0);
  }
}

/*
 * Drive the car
 *
 * leftMode   >>  -1: backward; 0: break;   1: forward
 * rightMode  >>  -1: backward; 0: break;   1: forward
 * time       >>  seconds
 */
void driveCar(int leftMode, int rightMode, int time) {
  driveMotor(0, leftMode);
  driveMotor(0, rightMode);
  delay(time * 1000);
}

void setup() {
  // Set the digital pins as output
  /*
   * On UNO, digitalWrite() works on pins 3, 5, 6, 9, 10, and 11.
   * https://www.arduino.cc/en/Reference/analogWrite
   */
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      pinMode(pins[i][j], OUTPUT);
    }
  }
}

void loop() {
  // Freeze for 2 seconds before starting
  delay(2000);

  // Go forward
  driveCar(-1, -1, 0.5);

  // Go forward
  driveCar(1, 1, 0.5);

  // Turn left; Turn right; Break
  driveCar(0, 1, 1);
  driveCar(1, 0, 1);
  driveCar(0, 0, 1);

  // Spin right; Spin left; Break
  driveCar(1, -1, 2);
  driveCar(-1, 1, 2);
  driveCar(0, 0, 1);
}
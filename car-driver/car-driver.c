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

/*
 * Drive the motor
 *
 * motorIndex  >>                 0: left;    1: right
 * driveMode   >>  -1: backward;  0: break;   1: forward
 */
void driveMotor(int motorIndex, int driveMode) {
  int pinForward = DIGITAL_PINS[motorIndex][0];
  int pinBackward = DIGITAL_PINS[motorIndex][1];

  switch (driveMode) {
  case BACKWARD:
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
    break;
  case BREAK:
    // Break
    digitalWrite(pinForward, LOW);
    digitalWrite(pinBackward, LOW);
    analogWrite(pinForward, 0);
    analogWrite(pinBackward, 0);
    break;
  case FORWARD:
    // Forward
    digitalWrite(pinForward, HIGH);
    digitalWrite(pinBackward, LOW);
    analogWrite(pinForward, 200);
    analogWrite(pinBackward, 0);
    break;
  default:
    break;
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
  driveMotor(MOTOR_LEFT, leftMode);
  driveMotor(MOTOR_RIGHT, rightMode);
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
      pinMode(DIGITAL_PINS[i][j], OUTPUT);
    }
  }
}

void loop() {
  // Freeze for 2 seconds before starting
  delay(2000);

  // Go backward
  driveCar(BACKWARD, BACKWARD, 0.5);

  // Go forward
  driveCar(FORWARD, FORWARD, 0.5);

  // Turn left; Turn right; Break
  driveCar(BREAK, FORWARD, 1);
  driveCar(FORWARD, BREAK, 1);
  driveCar(BREAK, BREAK, 1);

  // Spin right; Spin left; Break
  driveCar(FORWARD, BACKWARD, 2);
  driveCar(BACKWARD, FORWARD, 2);
  driveCar(BREAK, BREAK, 1);
}
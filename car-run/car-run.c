/*
 * The basic control to the car:
 * Go forward, go backward, turn left and turn right
 */
int leftMotorBackwardPin = 9; // Left motor backward (IN1)
int leftMotorForwardPin = 5; // Left motor forward (IN2)

int rightMotorForwardPin = 6; // Right motor forward (IN3)
int rightMotorBackwardPin = 10; // Right motor backward (IN4)

/*
 * Go forward
 */
void goForward(int time) {
  // Right motor goes forward
  digitalWrite(rightMotorForwardPin, HIGH);
  digitalWrite(rightMotorBackwardPin, LOW);

  /*
   * Writes an analog value (PWM wave) to a pin drive a motor at various speeds.
   * PWM: Pulse Width Modulation (0~255)
   * https://www.arduino.cc/en/Tutorial/PWM
   */
  analogWrite(rightMotorForwardPin, 200);
  analogWrite(rightMotorBackwardPin, 0);

  // Left motor goes forward
  digitalWrite(leftMotorForwardPin, HIGH);
  digitalWrite(leftMotorBackwardPin, LOW);
  analogWrite(leftMotorForwardPin, 200);
  analogWrite(leftMotorBackwardPin, 0);

  delay(time * 1000);
}

/*
 * Break
 */
void brake(int time) {
  digitalWrite(rightMotorForwardPin, LOW);
  digitalWrite(rightMotorBackwardPin, LOW);
  digitalWrite(leftMotorForwardPin, LOW);
  digitalWrite(leftMotorBackwardPin, LOW);

  delay(time * 1000);
}

/*
 * Turn left
 */
void turnLeft(int time) {
  // Right motor goes forward
  digitalWrite(rightMotorForwardPin, HIGH);
  digitalWrite(rightMotorBackwardPin, LOW);
  analogWrite(rightMotorForwardPin, 200);
  analogWrite(rightMotorBackwardPin, 0);

  // Left motor breaks
  digitalWrite(leftMotorForwardPin, LOW);
  digitalWrite(leftMotorBackwardPin, LOW);
  analogWrite(leftMotorForwardPin, 0);
  analogWrite(leftMotorBackwardPin, 0);

  delay(time * 1000);
}

/*
 * Spn left
 */
void spinLeft(int time) {
  // Right motor goes forward
  digitalWrite(rightMotorForwardPin, HIGH);
  digitalWrite(rightMotorBackwardPin, LOW);
  analogWrite(rightMotorForwardPin, 200);
  analogWrite(rightMotorBackwardPin, 0);

  // Left motor goes backward
  digitalWrite(leftMotorForwardPin, LOW);
  digitalWrite(leftMotorBackwardPin, HIGH);
  analogWrite(leftMotorForwardPin, 0);
  analogWrite(leftMotorBackwardPin, 200);
  delay(time * 1000);
}

/*
 * Turn right
 */
void turnRight(int time) {
  // Right motor breaks
  digitalWrite(rightMotorForwardPin, LOW);
  digitalWrite(rightMotorBackwardPin, LOW);
  analogWrite(rightMotorForwardPin, 0);
  analogWrite(rightMotorBackwardPin, 0);

  // Left motor goes forward
  digitalWrite(leftMotorForwardPin, HIGH);
  digitalWrite(leftMotorBackwardPin, LOW);
  analogWrite(leftMotorForwardPin, 200);
  analogWrite(leftMotorBackwardPin, 0);

  delay(time * 1000);
}

/*
 * Spin right
 */
void spinRight(int time) {
  // Right motor goes backward
  digitalWrite(rightMotorForwardPin, LOW);
  digitalWrite(rightMotorBackwardPin, HIGH);
  analogWrite(rightMotorForwardPin, 0);
  analogWrite(rightMotorBackwardPin, 200);

  // Left motor goes forward
  digitalWrite(leftMotorForwardPin, HIGH);
  digitalWrite(leftMotorBackwardPin, LOW);
  analogWrite(leftMotorForwardPin, 200);
  analogWrite(leftMotorBackwardPin, 0);
  delay(time * 1000);
}

/*
 * Go backward
 */
void goBack(int time) {
  // Right motor goes backward
  digitalWrite(rightMotorForwardPin, LOW);
  digitalWrite(rightMotorBackwardPin, HIGH);
  analogWrite(rightMotorForwardPin, 0);
  analogWrite(rightMotorBackwardPin, 150);
  digitalWrite(leftMotorForwardPin, LOW);

  // Left motor goes backward
  digitalWrite(leftMotorBackwardPin, HIGH);
  analogWrite(leftMotorForwardPin, 0);
  analogWrite(leftMotorBackwardPin, 150);
  delay(time * 1000);
}

void setup() {
  // Set the digital pins as output
  /*
   * On UNO, digitalWrite() works on pins 3, 5, 6, 9, 10, and 11.
   * https://www.arduino.cc/en/Reference/analogWrite
   */
  pinMode(leftMotorForwardPin, OUTPUT); // PIN 5
  pinMode(leftMotorBackwardPin, OUTPUT); // PIN 9
  pinMode(rightMotorForwardPin, OUTPUT); // PIN 6
  pinMode(rightMotorBackwardPin, OUTPUT); // PIN 10
}

void loop() {
  // Freeze for 2 seconds before starting
  delay(2000);

  goBack(1);
  brake(0.5);

  goForward(1);
  brake(0.5);

  turnLeft(1);
  turnRight(1);
  brake(0.5);

  spinRight(2);
  spinLeft(2);
  brake(0.5);

  brake(0.5);
}
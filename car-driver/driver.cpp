#include <arduino.h>
#include "driver.h"

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


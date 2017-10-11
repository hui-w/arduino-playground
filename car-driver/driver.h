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
 * Functions
 */
void driveMotor(int motorIndex, int driveMode);
void driveCar(int leftMode, int rightMode, int time);


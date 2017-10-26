/*
 * Connections:
 * ULN2003 Arduino
 * +       5V
 * -       GND
 * IN1     8
 * IN2     9
 * IN3     10
 * IN4     11
*/

#include <Stepper.h>

// Steps per cycle
const int stepsPerCycle = 64;

// Init the stepper
Stepper stepper(stepsPerCycle, 8, 10, 9, 11);

/*
// the previous reading from the analog input
int previous = 0;
*/

void setup() {
  // Set the speed, round/min
  stepper.setSpeed(60);

  // 初始化串口
  Serial.begin(9600);
}

void loop() {
  // CCW
  Serial.println("counterclockwise");
  stepper.step(-stepsPerCycle);
  delay(500);

  // CW
  Serial.println("counterclockwise");
  stepper.step(-stepsPerCycle);
  delay(500);

  /*
  // get the sensor value
  int val = analogRead(0);

  // move a number of steps equal to the change in the
  // sensor reading
  stepper.step(val - previous);


  // remember the previous value of the sensor
  previous = val;
  */
}



/*
int Pin0 = 8;
int Pin1 = 9;
int Pin2 = 10;
int Pin3 = 11;
int _step = 0;
boolean dir = true;    //正反转的 flag
int stepperSpeed = 1;  //电机转速,1ms一步
void setup() {
  pinMode(Pin0, OUTPUT);
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
}
//用下面的代码仿照PWM输出,看看类不累..哈哈.._step 从0 加到7 再变成0,
//就这样一直循环下去.
void loop() {
  switch (_step) {
    case 0:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      break;
    case 1:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, HIGH);
      break;
    case 2:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      break;
    case 3:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, HIGH);
      digitalWrite(Pin3, LOW);
      break;
    case 4:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      break;
    case 5:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, HIGH);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      break;
    case 6:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      break;
    case 7:
      digitalWrite(Pin0, HIGH);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, HIGH);
      break;
    default:
      digitalWrite(Pin0, LOW);
      digitalWrite(Pin1, LOW);
      digitalWrite(Pin2, LOW);
      digitalWrite(Pin3, LOW);
      break;
  }
  if (dir) {
    _step++;
  } else {
    _step--;
  }
  if (_step > 7) {  //请注意,这边_step>
                    //7的时候,已经是在上面的那个判断里面从7加到8了.但是,
                    //最后一次执行的时候,还是7 !!!
    _step = 0;
    　　  //所以这里变成0 是必须的.
  }
  if (_step < 0) {  //同理
    _step = 7;
  }
  delay(stepperSpeed);  //电机休息一下,用来调速用的.
}
*/

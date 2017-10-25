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

#include<Stepper.h>
  
const int stepsPerRevolution = 512;//电机每一转步数(每转走多少步）
  
// 初始化步进电机要使用的Arduino的引脚编号
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
  
void setup()
{
     // 设置转速，单位r/min
     myStepper.setSpeed(60);
  
     // 初始化串口
     Serial.begin(9600);
}
  
void loop()
{
     // 顺时针一次旋转
     for (int i = 0; i < 4; i ++) {
       Serial.println("clockwise");
       myStepper.step(stepsPerRevolution);
     }

     delay(500);
  
     // 逆时针一次旋转
     Serial.println("counterclockwise");
     myStepper.step(-stepsPerRevolution);
     delay(500);

     // 逆时针一次旋转
     Serial.println("counterclockwise");
     myStepper.step(-stepsPerRevolution);
     delay(500);
}

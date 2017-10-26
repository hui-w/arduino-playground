/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/
/*
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  myservo.write(0); 
  delay(1000);
  myservo.write(90); 
  delay(1000);
  myservo.write(180); 
  delay(1000);
  myservo.write(90); 
  delay(1000);
}

*/


//UART send 1~9==>20~180 degree
int servopin=9;//设置舵机驱动脚到数字口9
int myangle;//定义角度变量
int pulsewidth;//定义脉宽变量
int val;
void servopulse(int servopin,int myangle)/*定义一个脉冲函数，用来模拟方式产生PWM值*/
{
  pulsewidth=(myangle*11)+500;//将角度转化为500-2480 的脉宽值
  digitalWrite(servopin,HIGH);//将舵机接口电平置高
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
  digitalWrite(servopin,LOW);//将舵机接口电平置低
  delay(20-pulsewidth/1000);//延时周期内剩余时间
}
void setup()
{
  pinMode(servopin,OUTPUT);//设定舵机接口为输出接口
  Serial.begin(9600);//设置波特率为9600
  Serial.println("servo=o_seral_simple ready" ) ;
}
void loop()
{
  /*
  val=Serial.read();//读取串口收到的数据
  if(val>'0'&&val<='9')//判断收到数据值是否符合范围
  {
    val=val-'0';//将ASCII码转换成数值，例'9'-'0'=0x39-0x30=9
    val=val*(180/9);//将数字转化为角度，例9*（180/9）=180
    Serial.print("moving servo to ");
    Serial.print(val,DEC);
    Serial.println();
    for(int i=0;i<=50;i++) //产生PWM个数，等效延时以保证能转到响应角度
    {
      servopulse(servopin,val);//模拟产生PWM
    }
  }
  */

    //val=Serial.read();//读取串口收到的数据
  //if(val>'0'&&val<='9')//判断收到数据值是否符合范围

  for (val = 0 ; val <= 9; val ++)
  {
    int a=val*(180/9);//将数字转化为角度，例9*（180/9）=180
    Serial.print("moving servo to ");
    Serial.print(a,DEC);
    Serial.println();
    for(int i=0;i<=50;i++) //产生PWM个数，等效延时以保证能转到响应角度
    {
      servopulse(servopin,a);//模拟产生PWM
    }
  }
}


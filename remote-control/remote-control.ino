#include <IRremote.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int RECV_PIN = A4;  //端口声明
IRrecv irrecv(RECV_PIN);

decode_results results;  //结构声明
int on = 0;              //标志位
unsigned long last = millis();

long remote_key_1 = 0x00ff30CF;
long remote_key_2 = 0x00FF18E7;
long remote_key_3 = 0x00FF7A85;
long remote_key_4 = 0x00FF10EF;
long remote_key_5 = 0x00FF38C7;
long remote_key_6 = 0x00FF5AA5;
long remote_key_7 = 0x00FF52AD;
long remote_key_8 = 0x00FF4AB5;
long remote_key_9 = 0x00FF42BD;

//==============================
int Left_motor_back = 9;    //左电机后退(IN1)
int Left_motor_go = 5;      //左电机前进(IN2)
int Right_motor_go = 6;     // 右电机前进(IN3)
int Right_motor_back = 10;  // 右电机后退(IN4)

void setup() {
  myservo.attach(11);  // attaches the servo on pin 11 to the servo object
  //初始化电机驱动IO为输出方式
  pinMode(Left_motor_go, OUTPUT);     // PIN 5 (PWM)
  pinMode(Left_motor_back, OUTPUT);   // PIN 9 (PWM)
  pinMode(Right_motor_go, OUTPUT);    // PIN 6 (PWM)
  pinMode(Right_motor_back, OUTPUT);  // PIN 10 (PWM)
  pinMode(13, OUTPUT);                ////端口模式，输出
  Serial.begin(9600);                 //波特率9600
  irrecv.enableIRIn();                // Start the receiver
}
void run()  // 前进
{
  digitalWrite(Right_motor_go, HIGH);  // 右电机前进
  digitalWrite(Right_motor_back, LOW);
  // analogWrite(Right_motor_go,200);//PWM比例0~255调速，左右轮差异略增减
  // analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go, HIGH);  // 左电机前进
  digitalWrite(Left_motor_back, LOW);
  // analogWrite(Left_motor_go,200);//PWM比例0~255调速，左右轮差异略增减
  // analogWrite(Left_motor_back,0);
  // delay(time * 100);   //执行时间，可以调整
}

void brake()  //刹车，停车
{
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
  // delay(time * 100);//执行时间，可以调整
}

void left()  //左转(左轮不动，右轮前进)
{
  digitalWrite(Right_motor_go, HIGH);  // 右电机前进
  digitalWrite(Right_motor_back, LOW);
  // analogWrite(Right_motor_go,200);
  // analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW);  //左轮不动
  digitalWrite(Left_motor_back, LOW);
  // analogWrite(Left_motor_go,0);
  // analogWrite(Left_motor_back,0);//PWM比例0~255调速
  // delay(time * 100); //执行时间，可以调整
}

void spin_left()  //左转(左轮后退，右轮前进)
{
  digitalWrite(Right_motor_go, HIGH);  // 右电机前进
  digitalWrite(Right_motor_back, LOW);
  // analogWrite(Right_motor_go,200);
  // analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW);  //左轮后退
  digitalWrite(Left_motor_back, HIGH);
  // analogWrite(Left_motor_go,0);
  // analogWrite(Left_motor_back,200);//PWM比例0~255调速
  // delay(time * 100); //执行时间，可以调整
}

void right()  //右转(右轮不动，左轮前进)
{
  digitalWrite(Right_motor_go, LOW);  //右电机不动
  digitalWrite(Right_motor_back, LOW);
  // analogWrite(Right_motor_go,0);
  // analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go, HIGH);  //左电机前进
  digitalWrite(Left_motor_back, LOW);
  // analogWrite(Left_motor_go,200);
  // analogWrite(Left_motor_back,0);//PWM比例0~255调速
  // delay(time * 100); //执行时间，可以调整
}

void spin_right()  //右转(右轮后退，左轮前进)
{
  digitalWrite(Right_motor_go, LOW);  //右电机后退
  digitalWrite(Right_motor_back, HIGH);
  // analogWrite(Right_motor_go,0);
  // analogWrite(Right_motor_back,200);//PWM比例0~255调速
  digitalWrite(Left_motor_go, HIGH);  //左电机前进
  digitalWrite(Left_motor_back, LOW);
  // analogWrite(Left_motor_go,200);
  // analogWrite(Left_motor_back,0);//PWM比例0~255调速
  // delay(time * 100); //执行时间，可以调整
}

void back()  //后退
{
  digitalWrite(Right_motor_go, LOW);  //右轮后退
  digitalWrite(Right_motor_back, HIGH);
  // analogWrite(Right_motor_go,0);
  // analogWrite(Right_motor_back,150);//PWM比例0~255调速
  digitalWrite(Left_motor_go, LOW);  //左轮后退
  digitalWrite(Left_motor_back, HIGH);
  // analogWrite(Left_motor_go,0);
  // analogWrite(Left_motor_back,150);//PWM比例0~255调速
  // delay(time * 100);     //执行时间，可以调整
}

void dump(decode_results* results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    // Serial.println("Could not decode message");
    brake();
  }
  //串口打印，调试时可以打开，实际运行中会影响反应速度，建议屏蔽
  /*
    else
    {

      if (results->decode_type == NEC)
      {
        Serial.print("Decoded NEC: ");
      }
      else if (results->decode_type == SONY)
      {
        Serial.print("Decoded SONY: ");
      }
      else if (results->decode_type == RC5)
      {
        Serial.print("Decoded RC5: ");
      }
      else if (results->decode_type == RC6)
      {
        Serial.print("Decoded RC6: ");
      }
      Serial.print(results->value, HEX);
      Serial.print(" (");
      Serial.print(results->bits, DEC);
      Serial.println(" bits)");

    }
    Serial.print("Raw (");
    Serial.print(count, DEC);
    Serial.print("): ");

    for (int i = 0; i < count; i++)
    {
      if ((i % 2) == 1)
      {
        Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
      }
      else
      {
        Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
      }
      Serial.print(" ");
    }
    Serial.println("");
  */
}

void loop() {
  if (irrecv.decode(&results))  //调用库函数：解码
  {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250)  //确定接收到信号
    {
      on = !on;                           //标志位置反
      digitalWrite(13, on ? HIGH : LOW);  //板子上接收到信号闪烁一下led
      dump(&results);                     //解码红外信号
    }

    switch (results.value) {
      case remote_key_1:
        spin_left();
        break;
      case remote_key_2:
        run();
        break;
      case remote_key_3:
        spin_right();
        break;
      case remote_key_4:
        left();
        break;
      case remote_key_5:
        brake();
        break;
      case remote_key_6:
        right();
        break;
      case remote_key_7:
        myservo.write(0);
        delay(10);
        break;
      case remote_key_8:
        back();
        break;
      case remote_key_9:
        myservo.write(180);
        delay(10);
        break;
      default:
        break;
    }

    Serial.println(results.value);
    last = millis();
    irrecv.resume();  // Receive the next value
  }
}

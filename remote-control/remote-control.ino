#include <IRremote.h>
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

int RECV_PIN = A4;//端口声明
IRrecv irrecv(RECV_PIN);
decode_results results;//结构声明
int on = 0;//标志位
unsigned long last = millis();

long run_car = 0x00FF18E7;//按键2
long back_car = 0x00FF4AB5;//按键8
long left_car = 0x00FF10EF;//按键4
long right_car = 0x00FF5AA5;//按键6
long stop_car = 0x00FF38C7;//按键5
long left_turn = 0x00ff30CF;//按键1
long right_turn = 0x00FF7A85;//按键3
//==============================
int Left_motor_back=9;     //左电机后退(IN1)
int Left_motor_go=5;     //左电机前进(IN2)
int Right_motor_go=6;    // 右电机前进(IN3)
int Right_motor_back=10;    // 右电机后退(IN4)

void setup()
{
  myservo.attach(11);  // attaches the servo on pin 11 to the servo object
  //初始化电机驱动IO为输出方式
  pinMode(Left_motor_go,OUTPUT); // PIN 5 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 6 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 10 (PWM)
  pinMode(13, OUTPUT);////端口模式，输出
  Serial.begin(9600);	//波特率9600
  irrecv.enableIRIn(); // Start the receiver
}
void run()     // 前进
{
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);     
  //analogWrite(Right_motor_go,200);//PWM比例0~255调速，左右轮差异略增减
  //analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,HIGH);  // 左电机前进
  digitalWrite(Left_motor_back,LOW);
  //analogWrite(Left_motor_go,200);//PWM比例0~255调速，左右轮差异略增减
  //analogWrite(Left_motor_back,0);
  //delay(time * 100);   //执行时间，可以调整  
}

void brake()         //刹车，停车
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  //delay(time * 100);//执行时间，可以调整  
}

void left()         //左转(左轮不动，右轮前进)
{
  digitalWrite(Right_motor_go,HIGH);	// 右电机前进
  digitalWrite(Right_motor_back,LOW);
  //analogWrite(Right_motor_go,200); 
  //analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);   //左轮不动
  digitalWrite(Left_motor_back,LOW);
  //analogWrite(Left_motor_go,0); 
  //analogWrite(Left_motor_back,0);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整  
}

void spin_left()         //左转(左轮后退，右轮前进)
{
  digitalWrite(Right_motor_go,HIGH);	// 右电机前进
  digitalWrite(Right_motor_back,LOW);
  //analogWrite(Right_motor_go,200); 
  //analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);   //左轮后退
  digitalWrite(Left_motor_back,HIGH);
  //analogWrite(Left_motor_go,0); 
  //analogWrite(Left_motor_back,200);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整  
}

void right()        //右转(右轮不动，左轮前进)
{
  digitalWrite(Right_motor_go,LOW);   //右电机不动
  digitalWrite(Right_motor_back,LOW);
  //analogWrite(Right_motor_go,0); 
  //analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);//左电机前进
  digitalWrite(Left_motor_back,LOW);
  //analogWrite(Left_motor_go,200); 
  //analogWrite(Left_motor_back,0);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整  
}

void spin_right()        //右转(右轮后退，左轮前进)
{
  digitalWrite(Right_motor_go,LOW);   //右电机后退
  digitalWrite(Right_motor_back,HIGH);
  //analogWrite(Right_motor_go,0); 
  //analogWrite(Right_motor_back,200);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);//左电机前进
  digitalWrite(Left_motor_back,LOW);
  //analogWrite(Left_motor_go,200); 
  //analogWrite(Left_motor_back,0);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整  
}

void back()          //后退
{
  digitalWrite(Right_motor_go,LOW);  //右轮后退
  digitalWrite(Right_motor_back,HIGH);
  //analogWrite(Right_motor_go,0);
  //analogWrite(Right_motor_back,150);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);  //左轮后退
  digitalWrite(Left_motor_back,HIGH);
  //analogWrite(Left_motor_go,0);
  //analogWrite(Left_motor_back,150);//PWM比例0~255调速
  //delay(time * 100);     //执行时间，可以调整  
}

void dump(decode_results *results)
{
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) 
  {
    //Serial.println("Could not decode message");
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

void loop()
{ 
  if (irrecv.decode(&results)) //调用库函数：解码
  {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250) //确定接收到信号
    {
      on = !on;//标志位置反
      digitalWrite(13, on ? HIGH : LOW);//板子上接收到信号闪烁一下led
      dump(&results);//解码红外信号
    }
    if (results.value == run_car )//按键2
      run();//前进
    if (results.value == back_car )//按键8
      back();//后退
    if (results.value == left_car )//按键4
      left();//左转
    if (results.value == right_car )//按键6
      right();//右转
    if (results.value == stop_car )//按键5
      brake();//停车
    if (results.value == left_turn )//按键1
      spin_left();//左旋转
    if (results.value == right_turn )//按键3
        spin_right();//右旋转

    if (results.value == 16728765) {
      myservo.write(180);
      delay(10);
    }

    if (results.value == 16730805) {
      myservo.write(90);
      delay(10);
    }

    if (results.value == 16732845) {
      myservo.write(0);
      delay(10,,,,,);
    }
    
    Serial.println(results.value);
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
}




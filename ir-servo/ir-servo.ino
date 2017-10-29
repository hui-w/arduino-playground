#include <IRremote.h>

// Define the PINs
const int IR_RECV_PIN = 4;
const int SERVO_A_PIN = 9;
const int SERVO_B_PIN = 10;

// Define the remove key codes
const long REMOTE_KEY_1 = 0x00ff30CF;
const long REMOTE_KEY_2 = 0x00FF18E7;
const long REMOTE_KEY_3 = 0x00FF7A85;
const long REMOTE_KEY_4 = 0x00FF10EF;
const long REMOTE_KEY_5 = 0x00FF38C7;
const long REMOTE_KEY_6 = 0x00FF5AA5;
const long REMOTE_KEY_7 = 0x00FF52AD;
const long REMOTE_KEY_8 = 0x00FF4AB5;
const long REMOTE_KEY_9 = 0x00FF42BD;

// Init the IR receiver
IRrecv irrecv(IR_RECV_PIN);
decode_results results;
int on = 0;
unsigned long last = millis();

void setup() {
  pinMode(SERVO_A_PIN, OUTPUT);
  pinMode(SERVO_B_PIN, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {   
  if (irrecv.decode(&results)) {

    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250)
    {
      on = !on;
      digitalWrite(13, on ? HIGH : LOW);
    }

    switch (results.value) {
      case REMOTE_KEY_1:
        // Servo B -> 180
        for(int i = 0; i <= 50; i++) {
          servoPulse(SERVO_B_PIN, 160);
        }
        break;
      case REMOTE_KEY_2:
        for(int i = 0; i <= 50; i++) {
          servoPulse(SERVO_B_PIN, 90);
        }
        break;
      case REMOTE_KEY_3:
        // Servo B -> 0
        for(int i = 0; i <= 50; i++) {
          servoPulse(SERVO_B_PIN, 20);
        }
        break;
      case REMOTE_KEY_4:
        // Servo A -> 0
        for(int i = 0; i <= 50; i++) {
          servoPulse(SERVO_A_PIN, 180);
        }
        break;
      case REMOTE_KEY_5:
        for(int i = 0; i <= 50; i++) {
          servoPulse(SERVO_A_PIN, 90);
        }     
        break;
      case REMOTE_KEY_6:
        // Servo A -> 180
        for(int i = 0; i <= 50; i++) {
          servoPulse(SERVO_A_PIN, 0);
        }
        break;
      case REMOTE_KEY_7:
        
        break;
      case REMOTE_KEY_8:
        
        break;
      case REMOTE_KEY_9:
        
        break;
      default:
        break;
    }

    Serial.println(results.value);
    last = millis();

    // Receive the next value
    irrecv.resume();
  }
}

void servoPulse(int pin,int angle)
{
  // Calculate the pulse width according to the angle
  // pulseWidth = (angle * 11 ) + 500;
  int pulseWidth = map(angle, 0, 180, 500, 2480);

  // High
  digitalWrite(pin, HIGH);
  delayMicroseconds(pulseWidth);

  // Low
  digitalWrite(pin, LOW);
  delay(20 - pulseWidth / 1000);
}

int pulsewidth;//定义脉宽变量
void servoPulse2(int servopin,int myangle)//定义一个脉冲函数
{
  pulsewidth=(myangle*11)+500;//将角度转化为500-2480的脉宽值
  digitalWrite(servopin,HIGH);//将舵机接口电平至高
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
  digitalWrite(servopin,LOW);//将舵机接口电平至低
  delay(20-pulsewidth/1000);
}


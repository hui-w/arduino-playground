#include <Servo.h>
Servo myservo;
int SERVO_PIN = 9;
int TONE_PIN = 6;
int RED_LED_PIN = 11;
int GREEN_LED_PIN = 12;
int BUTTON_PIN = 10;
int SENSOR_PIN = 8;

int posStart = 70;
int posEnd = 170;
int servoSpeed = 10;

int preBlockingBeepCount = 4;
int blockingBeepCount = 10;
bool isAlarmLedOn = false;

void setup()
{
  myservo.attach(SERVO_PIN);
  myservo.write(posStart);

  pinMode(TONE_PIN,OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(SENSOR_PIN,INPUT);

  digitalWrite(GREEN_LED_PIN, HIGH);
}

void tones(int count, bool beepAtEnd = false)
{
  for (int i = 0; i < count; i++)
  {
    tone();
    delay(500);
  }
  if (beepAtEnd) {
    tone();
  }
}

void tone()
{
  digitalWrite(RED_LED_PIN, isAlarmLedOn ? LOW : HIGH);
  isAlarmLedOn = !isAlarmLedOn;
  for(int i = 0;i < 40; i ++)
  {
    digitalWrite(TONE_PIN, HIGH);
    delay(1);
    digitalWrite(TONE_PIN, LOW);
    delay(1);
  }
}

void loop()
{
  bool isButtonPressed = digitalRead(BUTTON_PIN) == LOW;
  bool isSensorTriggered = digitalRead(SENSOR_PIN) == LOW;

  if (isButtonPressed || isSensorTriggered) {
    blockTraffic();
  }
}

void blockTraffic()
{
    digitalWrite(GREEN_LED_PIN, LOW);
    tones(preBlockingBeepCount, true);
    for (int pos = posStart; pos <= posEnd;pos ++)
    {
      myservo.write(pos);
      delay(servoSpeed);
      if (pos - posStart == 50){
        tone();
      }
    }
  
    tones(blockingBeepCount);
          
    for (int pos = posEnd; pos >= posStart; pos --)
    {
      myservo.write(pos);
      delay(servoSpeed);
    }

    digitalWrite(GREEN_LED_PIN, HIGH);
}

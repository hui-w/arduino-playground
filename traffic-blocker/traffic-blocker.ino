#include <Servo.h>
#define TONE_NOTE 3729
#define NOTE_DURATION 250

Servo servoInstance;
int SERVO_PIN = 9;
int TONE_PIN = 6;
int RED_LED_PIN = 11;
int GREEN_LED_PIN = 12;
int BUTTON_PIN = 10;
int SENSOR_PIN = 8;

int posStart = 70;
int posEnd = 170;
int servoSpeed = 10;

int preBlockingBeepCount = 2;
int blockingBeepCount = 6;
bool isAlarmLedOn = false;

void setup()
{
  servoInstance.attach(SERVO_PIN);
  servoInstance.write(posStart);

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
    playBeep();
    delay(500);
  }
  if (beepAtEnd) {
    playBeep();
  }
}

void playBeep()
{
  digitalWrite(RED_LED_PIN, isAlarmLedOn ? LOW : HIGH);
  isAlarmLedOn = !isAlarmLedOn;

  tone(6, TONE_NOTE, NOTE_DURATION);
  delay(NOTE_DURATION + 30);
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
      servoInstance.write(pos);
      delay(servoSpeed);
      if (pos - posStart == 50){
        playBeep();
      }
    }
  
    tones(blockingBeepCount);
          
    for (int pos = posEnd; pos >= posStart; pos --)
    {
      servoInstance.write(pos);
      delay(servoSpeed);
    }

    digitalWrite(GREEN_LED_PIN, HIGH);
}

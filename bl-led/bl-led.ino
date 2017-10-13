/*
Arduino   HC-06
5V(3.3V)  VCC
GND       GND
TX        RXD
RX        TXD

D13       LED
*/

void setup() {
  // HC-06: 9600
  // HC-05: 38400
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '1') {
      Serial.println("Hello message.");

      // Send message to the sender
      Serial.write("Serial--13--high");
      digitalWrite(13, HIGH);
    }
    if (c == '2') {
      Serial.write("Serial--13--low");
      digitalWrite(13, LOW);
    }
  }
}


/*
// http://zhongbest.com/2016/09/01/%E8%93%9D%E7%89%99%E6%A8%A1%E5%9D%97hc05/
// http://zhongbest.com/2016/09/01/%E8%93%9D%E7%89%99%E6%A8%A1%E5%9D%97hc06/
*/
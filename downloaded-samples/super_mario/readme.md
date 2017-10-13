=== Hardware requirements
- An Arduino(I used an Arduino Nano, any other is fine)
- Piezo buzzer
- 1 k ohm resistor(any resistor between 333 ohm to 1 k  should be fine in this project)
- A breadboard
- Some breadboard cable(s)

=== Connecting the components
If you have an Arduino Uno(which most people have), connect the components with the help of the image below. If you have an Arduino Nano, look the the image in “Using an Arduino Nano”.

Connect the positive side of the buzzer to digital pin 3, then the negative side to a 1k ohm resistor. Connect the other side of the 1 k ohm resistor to ground(GND) pin on the Arduino. Remember to connect the buzzer the right way, the buzzer has positive and negative pins!

So basically the buzzer, 1 k ohm resistor and Arduino should be connected like this:
Arduino digital pin 3 –> Buzzer –> 1 k ohm resisotor –> Arduino ground(GND) pin.

You can actually do without the 1 k ohm resistor! If you connect without the resistor, the buzzer will be a lot louder, and the sound quality might degrade. But you can also lower the resistance to get a little louder sound, and keep the sound quality. Another idea is using a potentiometer instead of a resistor to act as a volume controller! For this tutorial we’ll just be using a 1 k ohm resistor.

=== URL
http://www.princetronics.com/supermariothemesong/
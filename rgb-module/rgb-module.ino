int redPin = 10; 
int greenPin = 11; 
int bluePin = 12;

void setup()
{
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
}
void loop()
{
  setColor(250,105,0); //Yellow
  delay(1000); 
  
  setColor(250,40,0); // Orange 
  delay(1000); 
  
  setColor(255,0,0); // Red 
  delay(1000); 
  
  setColor(10,10,255); // Blue 
  delay(1000); 
  
  setColor(255,0,100); // Pink 
  delay(1000); 
  
  setColor(200,0,255); // Purple 
  delay(1000); 
  
  setColor(0,255,0); // Green 
  delay(1000); 
  
  setColor(255,255,255); // White 
  delay(1000); 
}
void setColor(int red,int green,int blue)
{
  analogWrite(redPin,255-red); 
  analogWrite(greenPin,255-green); 
  analogWrite(bluePin,255-blue); 
}
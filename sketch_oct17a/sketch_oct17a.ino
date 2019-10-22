int redPin = 5;
int greenPin = 6;
int bluePin = 7;

 
//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
 
void loop()
{
  for(int i = 0; i < 255; i++)
  {
    setColor(i, 255, 0);  // red
    delay(10);
  }
  
  delay(500);

  for(int i = 255; i > 0; i--)
  {
    setColor(255, i, 0);  // red
    delay(10);
  }

   delay(500);

  for(int i = 0; i < 255; i++)
  {
    setColor(255, 0, i);  // red
    delay(10);
  }

  delay(500);

  for(int i = 255; i > 0; i--)
  {
    setColor(i, 0, 255);
    delay(10);
  }

  delay(500);

  for(int i = 0; i < 255; i++)
  {
    setColor(0, i, 255);  // red
    delay(10);
  }

  delay(500);

  for(int i = 255; i > 0; i--)
  {
    setColor(0, 255, i);
    delay(10);
  }

  delay(500);
 



}
 
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

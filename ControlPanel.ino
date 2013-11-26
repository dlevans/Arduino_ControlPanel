#include <Adafruit_NeoPixel.h>
#include <MeetAndroid.h>
#include <Wire.h>
#include <SoftwareSerial.h>
// RX TX Baudrate
MeetAndroid meetAndroid(8, 9, 57600);
#define PIN 12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

int pattern = 8;              // everything off = 8
int spd = 10;
int cc1red, cc1green, cc1blue;
int cc2red, cc2green, cc2blue;
int cc3red, cc3green, cc3blue;
int cc4red, cc4green, cc4blue;
uint32_t c1, c2, c3, c4;

//spectrum stuff
int strobe = 4; // strobe pins on digital 4
int res = 5; // reset pins on digital 5
// store band values in these arrays
int left[7]; 
int right[7];
int band;
int leftledsize[7];
int rightledsize[7];
int hackerspacevu[7];
int partyvu[7];

void setup() {
  strip.show();
  strip.begin();
  Serial.begin(57600);
  pinMode(res, OUTPUT); // reset
  pinMode(strobe, OUTPUT); // strobe
  digitalWrite(res,LOW); // reset low
  digitalWrite(strobe,HIGH); //pin 5 is RESET on the shield
  delay(100);
  meetAndroid.send("Options: ");
  meetAndroid.send("S + 1 - 255: speed");
  meetAndroid.send("P + 0 - 3: pattern");
  meetAndroid.send("C + 0 - 255: Color 1 Red");
  meetAndroid.send("D + 0 - 255: Color 1 Green");
  meetAndroid.send("E + 0 - 255: Color 1 Blue");
  meetAndroid.send("F + 0 - 255: Color 2 Red");
  meetAndroid.send("G + 0 - 255: Color 2 Green");
  meetAndroid.send("H + 0 - 255: Color 2 Blue");
  meetAndroid.send("I + 0 - 255: Color 3 Red");
  meetAndroid.send("J + 0 - 255: Color 3 Green");
  meetAndroid.send("K + 0 - 255: Color 3 Blue");
  meetAndroid.send("M + 0 - 255: Color 4 Red");
  meetAndroid.send("N + 0 - 255: Color 4 Green");
  meetAndroid.send("O + 0 - 255: Color 4 Blue");
  meetAndroid.registerFunction(setColor1Red, 'C');
  meetAndroid.registerFunction(setColor1Blue, 'D');
  meetAndroid.registerFunction(setColor1Green, 'E');
  meetAndroid.registerFunction(setColor2Red, 'F');
  meetAndroid.registerFunction(setColor2Blue, 'G');
  meetAndroid.registerFunction(setColor2Green, 'H');
  meetAndroid.registerFunction(setColor3Red, 'I');
  meetAndroid.registerFunction(setColor3Blue, 'J');
  meetAndroid.registerFunction(setColor3Green, 'K');
  meetAndroid.registerFunction(setColor4Red, 'M');
  meetAndroid.registerFunction(setColor4Blue, 'N');
  meetAndroid.registerFunction(setColor4Green, 'O');
  meetAndroid.registerFunction(setSpd, 'S');
  meetAndroid.registerFunction(getPattern, 'P');
}

void loop(){
  delay(10);
  meetAndroid.receive();
  delay(10);
  getColor();
  setPattern();
}

void setSpd(byte flag, byte values)
{
  int s;
  s = meetAndroid.getInt();
  spd = map(s, 1, 255, 1, 100);
  meetAndroid.send("Speed changed");  
}

void setColor1Red(byte flag, byte values)
{
  cc1red = meetAndroid.getInt();
  meetAndroid.send("Color1 Red set");
}

void setColor1Green(byte flag, byte values)
{
  cc1green = meetAndroid.getInt();
  meetAndroid.send("Color1 Green set");
}

void setColor1Blue(byte flag, byte values)
{
  cc1blue = meetAndroid.getInt();
  meetAndroid.send("Color1 Blue set");
}

void setColor2Red(byte flag, byte values)
{
  cc2red = meetAndroid.getInt();
  meetAndroid.send("Color2 Red set");
}

void setColor2Green(byte flag, byte values)
{
  cc2green = meetAndroid.getInt();
  meetAndroid.send("Color2 Green set");
}

void setColor2Blue(byte flag, byte values)
{
  cc2blue = meetAndroid.getInt();
  meetAndroid.send("Color2 Blue set");
}

void setColor3Red(byte flag, byte values)
{
  cc3red = meetAndroid.getInt();
  meetAndroid.send("Color3 Red set");
}

void setColor3Green(byte flag, byte values)
{
  cc3green = meetAndroid.getInt();
  meetAndroid.send("Color3 Green set");
}

void setColor3Blue(byte flag, byte values)
{
  cc3blue = meetAndroid.getInt();
  meetAndroid.send("Color3 Blue set");
}

void setColor4Red(byte flag, byte values)
{
  cc4red = meetAndroid.getInt();
  meetAndroid.send("Color4 Red set");
}

void setColor4Green(byte flag, byte values)
{
  cc4green = meetAndroid.getInt();
  meetAndroid.send("Color4 Green set");
}

void setColor4Blue(byte flag, byte values)
{
  cc4blue = meetAndroid.getInt();
  meetAndroid.send("Color4 Blue set");
}

void getColor()
{
  c1 = strip.Color(cc1red, cc1green, cc1blue);
  c2 = strip.Color(cc2red, cc2green, cc2blue);
  c3 = strip.Color(cc3red, cc3green, cc3blue);
  c4 = strip.Color(cc4red, cc4green, cc4blue);
}

void getPattern(byte flag, byte values)
{
  int p;
  p = meetAndroid.getInt();
  if(p == 0)
  {
  pattern = 0;
  meetAndroid.send("Pattern 0");
  }
  else if(p == 1)
  {
    pattern = 1;
    meetAndroid.send("Pattern 1");
  }
  else if(p == 2)
  {
    pattern = 2;
    meetAndroid.send("Pattern 2");
  }
  else if(p == 3)
  {
    pattern = 3;
    meetAndroid.send("Pattern 3");
  }
  else if(p == 4)
  {
    pattern = 4;
    meetAndroid.send("Pattern 4");
  }
  else if(p == 5)
  {
    pattern = 5;
    meetAndroid.send("Pattern 5");
  }
  else if(p == 6)
  {
    pattern = 6;
    meetAndroid.send("Pattern 6");
  }
  else if(p == 7)
  {
    pattern = 7;
    meetAndroid.send("Pattern 7");
  }
  else if(p == 8)
  {
    pattern = 8;
    meetAndroid.send("Pattern 8");
  }
}

void setPattern()
{
  
  switch(pattern)
  {
    case 0:
    pattern0();
    meetAndroid.send("Pattern 0 sent");
    break;
    
    case 1:
    pattern1();
    meetAndroid.send("Pattern 1 sent");
    break;
    
    case 2:
    pattern2();
    meetAndroid.send("Pattern 2 sent");
    break;
    
    case 3:
    pattern3();
    meetAndroid.send("Pattern 3 sent");
    break;
    
    case 4:
    pattern4();
    meetAndroid.send("Pattern 4 sent");
    break;
    
    case 5:
    pattern5();
    meetAndroid.send("Pattern 5 sent");
    break;
    
    case 6:
    pattern6();
    meetAndroid.send("Pattern 6 sent");
    break;
    
    case 7:
    pattern7();
    meetAndroid.send("Pattern 7 sent");
    break;
    
    case 8:
    pattern8();
    meetAndroid.send("Pattern 8 sent");
    break;
  }
}

void pattern0()
{
  thirds(c1, c2, c3, spd);
}

void pattern1()
{
  everyOther(c1, c2, spd);
}

void pattern2()
{
  colorChase(c1, spd);
  colorChase(c2, spd);
  colorChase(c3, spd);
}

void pattern3()
{
  rainbow(20);
}

void pattern4()
{
  rainbowCycle(20);
}

void pattern5()
{
  c1 = strip.Color(cc1red, cc1green, cc1blue);
  solid(c1);
}

void pattern6()
{
  policeLights(c1,c2,c3, spd);
}

void pattern7()
{
  party();
}

void pattern8()
{
  off();
}

void party()
{
  off();
  readMSGEQ7();
  leftledsize[0] = map(left[2], 50, 1023, 0, 5); 
  leftledsize[1] = map(left[3], 65, 1023, 6, 11);
  leftcolorWipe1(c1, spd);
  leftcolorWipe2(c2, spd);
  rightledsize[0] = map(right[4], 65, 1023, 24, 20);
  rightledsize[1] = map(right[5], 0, 1023, 30, 25);
  rightcolorWipe1(c3, spd);
  rightcolorWipe2(c4, spd);
  delay(75);
  off();
}

void leftcolorWipe1(uint32_t c, uint8_t wait) {
  int i;
  for (i=0; i < leftledsize[0]; i++) {
      strip.setPixelColor(i, c);
      delay(wait);
  }
  strip.show();
}

void leftcolorWipe2(uint32_t c, uint8_t wait) {
  int i;
  for (i=6; i < leftledsize[1]; i++) {
      strip.setPixelColor(i, c);
      delay(wait);
  }
  strip.show();
}

void rightcolorWipe1(uint32_t c, uint8_t wait) {
  int i;
  for (i=24; i > rightledsize[0]; i--) {
      strip.setPixelColor(i, c);
      delay(wait);
  }
  strip.show();
}

void rightcolorWipe2(uint32_t c, uint8_t wait) {
  int i;
  for (i=30; i > rightledsize[1]; i--) {
      strip.setPixelColor(i, c);
      delay(wait);
  }
  strip.show();
}

void policeLights(uint32_t c,uint32_t d,uint32_t e, uint8_t wait) {
  int leftLimit = strip.numPixels() / 4;
  int rightLimit = strip.numPixels() - leftLimit;
  int center = strip.numPixels() / 2;
  int cLeft = center - 3;
  int cRight = center + 3;
  for(uint16_t i=0; i<cLeft; i++) {
      strip.setPixelColor(i, c);
  }
  
  for(uint16_t i=cLeft; i<cRight; i++) {
      strip.setPixelColor(i, d);
  }
  
  for(uint16_t i=cRight; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, e);
  }
  strip.show();
  delay(wait);
  for(uint16_t i=0; i<cLeft; i++) {
      strip.setPixelColor(i, c);
  }
  
  for(uint16_t i=cLeft; i<cRight; i++) {
      strip.setPixelColor(i, c);
  }
  
  for(uint16_t i=cRight; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, e);
  }
  strip.show();
  delay(wait);
  for(uint16_t i=0; i<cLeft; i++) {
      strip.setPixelColor(i, e);
  }
  
  for(uint16_t i=cLeft; i<cRight; i++) {
      strip.setPixelColor(i, e);
  }
  
  for(uint16_t i=cRight; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
  for(uint16_t i=0; i<cLeft; i++) {
      strip.setPixelColor(i, e);
  }
  
  for(uint16_t i=cLeft; i<cRight; i++) {
      strip.setPixelColor(i, d);
  }
  
  for(uint16_t i=cRight; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}

void solid(uint32_t c) 
{
  for(uint16_t i=0; i<strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, c);
  }
  strip.show();
}

/////////////////////////////////////////////////////////////////////////////////////
void everyOther(uint32_t c, uint32_t d, uint8_t wait) {
  ///////////////////////START//////////////////////
  for(int i=0; i<strip.numPixels(); i++) {
    if(i%2==0)
    {
      strip.setPixelColor(i, c);
      strip.show();   
    }
    else
    {
      strip.setPixelColor(i, d);
      strip.show(); 
    }
    delay(wait);
  }
  ///////////////////////HOLD//////////////////////
  for(int i=0; i<strip.numPixels(); i++) {
    if(i%2==0)
    {
      strip.setPixelColor(i, c); // Set new pixel 'on'   
    }
    else
    {
      strip.setPixelColor(i, d); // Set new pixel 'on' 
    }
    strip.show();
    delay(25);
  }
  ///////////////////////OFF//////////////////////
  for(int i=0; i<strip.numPixels(); i++) {
    c = strip.Color(0, 0, 0);
    d = strip.Color(0, 0, 0);
    if(i%2==0)
    {
      strip.setPixelColor(i, c); // Set new pixel 'on'
      strip.show();   
    }
    else
    {
      strip.setPixelColor(i, d); // Set new pixel 'on'
      strip.show(); 
    }
    delay(wait);
  }
}
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
void thirds(uint32_t c,uint32_t d, uint32_t e, uint8_t wait) 
{
  int i;
  int a = strip.numPixels() / 3;
  uint32_t f = strip.Color(0, 0, 0);
  //////////////ON/////////////////
  for (i=0; i < a; i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
  for (i=a; i < a*2; i++) {
      strip.setPixelColor(i, d);
      strip.show();
      delay(wait);
  }
  for (i=a+a; i < a*3; i++) {
      strip.setPixelColor(i, e);
      strip.show();
      delay(wait);
  }
  //////////////OFF/////////////////
  for (i=a; i > -1; i--) {
      strip.setPixelColor(i, f);
      strip.show();
      delay(wait);
  }
  for (i=a+1; i < a*2; i++) {
      strip.setPixelColor(i, f);
      strip.show();
      delay(wait);
  }
  for (i=a*3; i > (a*2)-1; i--) {
      strip.setPixelColor(i, f);
      strip.show();
      delay(wait);
  }
}
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
void colorChase(uint32_t c, uint8_t wait) {
  int i;
  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(wait);
  }
  strip.show(); // Refresh to turn off last pixel
}
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
void off() {
  for(int i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
  strip.show();
}
/////////////////////////////////////////////////////////////////////////////////////
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void readMSGEQ7()
{
 digitalWrite(res, HIGH);
 digitalWrite(res, LOW);
 for(band=0; band <7; band++)
 {
 digitalWrite(strobe,LOW); // strobe pin on the shield - kicks the IC up to the next band 
 delayMicroseconds(30); // 
 left[band] = analogRead(0); // store left band reading
 right[band] = analogRead(1); // ... and the right
 digitalWrite(strobe,HIGH); 
 }
}

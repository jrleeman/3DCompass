#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIXILPIN 13 // Pin on the Arduino that the NeoPixil chain is connected to
#define NUMAZ 24  // Number of pixils on the azimuth ring
#define NUMINC 16

#define AZREF 11 // Pixil Number that the y+ axis points at

int azPixel = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMAZ + NUMINC, PIXILPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Start strip and make all pixils dark
  strip.begin();
  strip.show();
  
  // Start the serial port to stream data back
  Serial.begin(115200);
  Serial.println("NESW Ring Orientation Test");
  Serial.println("");
  Serial.println("This should run through a 4 element pattern, to check ring");
  Serial.println("orientation. First all lights will turn on, then off. Ring");
  Serial.println("will then cycle through North, East, South, West. North should");
  Serial.println("be in the direction of the positive x-axis. The ring will then");
  Serial.println("turn off for two seconds and start again with the cycle");
  
  // Flash the entire ring
  allOn();
  delay(2000);
  allOff();
  delay(1000);

}

void loop() {  
  plotAzimuth(0);
  delay(1000);
  plotAzimuth(90);
  delay(1000);
  plotAzimuth(180);
  delay(1000);
  plotAzimuth(270);
  delay(1000);
  allOff();
  delay(2000);
}

void plotAzimuth(int angle){
  strip.setPixelColor(azPixel, 0,0,0);
  azPixel = angle/(360/NUMAZ);
  // Rotate so it is like pixil 0 is at +x
  azPixel += AZREF;
  if (azPixel >= NUMAZ)
    azPixel -= NUMAZ;  
  strip.setPixelColor(azPixel, 50,0,0);
  strip.show();
}

void allOn() {
  for (int i=0; i<NUMAZ; i++){
    strip.setPixelColor(i,20,20,20);
  }
  strip.show();
}

void allOff() {
  for (int i=0; i<NUMAZ; i++){
    strip.setPixelColor(i,0,0,0);
  }
  strip.show();
}



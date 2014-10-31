/*
  AZ_Orientation_Test.ino
  
  This sketch provides a way for you to ensure that the ring is mounted correctly
  and that you know the correct value to set for the AZREF variable. AZREF should
  be set to the pixel number that the +y axis points at. 
  
  Created: 10/30/14
  Author: John R. Leeman
  Modified: 10/31/14
  www.johnrleeman.com
  www.github.com/jrleeman
*/
  

#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIXELPIN 13 // Pin on the Arduino that the NeoPixil chain is connected to
#define NUMAZ 24  // Number of pixels on the azimuth ring
#define NUMINC 16 // Number of pixels on the inclination ring

#define AZREF 11 // Pixil Number that the y+ axis points at

int azPixel = 0; // Stores pixel that was turned on

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMAZ + NUMINC, PIXELPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  // Start strip and make all pixels dark
  strip.begin();
  strip.show();
  
  // Start the serial port and write description
  Serial.begin(115200);
  Serial.println("NESW Ring Orientation Test");
  Serial.println("");
  Serial.println("The AZREF definition should be setup for the pixel that is");
  Serial.println("Located in the +y direction.");
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
  
  // "North" w.r.t x-axis
  plotAzimuth(0);
  delay(1000);
  
  // "East" w.r.t x-axis
  plotAzimuth(90);
  delay(1000);
  
  // "South" w.r.t x-axis
  plotAzimuth(180);
  delay(1000);
  
  // "West" w.r.t x-axis
  plotAzimuth(270);
  delay(1000);
  
  // All off and wait
  allOff();
  delay(2000);
}

void plotAzimuth(int angle){
  /* Plot a single pixel at the angle provided, assuming
  that "North" is the +y axis as marked on the magnetometer.
  */
  
  // Turn off old pixel
  strip.setPixelColor(azPixel, 0,0,0);
  
  // Calculate new pixel number
  azPixel = angle/(360/NUMAZ);
  
  // Rotate so it is like pixel 0 is at +x and correct if 
  // we run onto the next ring
  azPixel += AZREF;
  if (azPixel >= NUMAZ){
    azPixel -= NUMAZ;  
  }
    
  // Turn on the new pixel
  strip.setPixelColor(azPixel, 50,0,0);
  strip.show();
}

void allOn() {
  // Turn on all azimuth pixels
  for (int i=0; i<NUMAZ; i++){
    strip.setPixelColor(i,20,20,20);
  }
  strip.show();
}

void allOff() {
  // Turn off all azimuth pixels
  for (int i=0; i<NUMAZ; i++){
    strip.setPixelColor(i,0,0,0);
  }
  strip.show();
}



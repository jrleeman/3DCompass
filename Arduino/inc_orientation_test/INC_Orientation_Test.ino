/*
  INC_Orientation_Test.ino
  
  This sketch provides a way for you to ensure that the inclination ring is 
  mounted correctly and that you know the correct value to set for the INCREF 
  variable. INCREF should be set to the pixel number that is just above horizontal
  in the +y direction. 
  
  Created: 10/30/14
  Author: John R. Leeman
  Modified: 10/31/14
  www.johnrleeman.com
  www.github.com/jrleeman
*/
  

#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIXILPIN 13 // Pin on the Arduino that the NeoPixil chain is connected to
#define NUMAZ 24  // Number of pixels on the azimuth ring
#define NUMINC 16 // Number of pixels on the inclination ring

#define INCREF 11 // Pixil Number that is above the +y axis direction

int incPixel = 0; // Stores pixel that was turned on

// Setup neopixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMAZ + NUMINC, PIXILPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  // Start strip and make all pixels dark
  strip.begin();
  strip.show();
  
  // Start the serial port and write description
  Serial.begin(115200);
  Serial.println("Inclination Ring Orientation Test");
  Serial.println("");
  Serial.println("The INCREF definition should be setup for the pixel that is");
  Serial.println("located just above horizontal in the +y direction.");
  Serial.println("");
  Serial.println("This should run through an 8 element pattern, to check ring");
  Serial.println("orientation. First all lights will turn on, then off. Ring");
  Serial.println("will then cycle through below/above horizontal in the +y direction,");
  Serial.println("then around vertical, then above/below horizontal in the -y direction,");
  Serial.println("and finally around vertical downwards.");
  
  // Flash the entire ring
  allOn();
  delay(2000);
  allOff();
  delay(1000);
}

void loop() {  
  // 350 Degrees
  plotInclination(350);
  delay(1000);
  
  // 10 Degrees
  plotInclination(10);
  delay(1000);
  
  // 80 Degrees
  plotInclination(80);
  delay(1000);
  
  // 100 Degrees
  plotInclination(100);
  delay(1000);
  
  // 170 Degrees
  plotInclination(170);
  delay(1000);
  
  // 190 Degrees
  plotInclination(190);
  delay(1000);
  
  // 260 Degrees
  plotInclination(260);
  delay(1000);
  
    // 280 Degrees
  plotInclination(280);
  delay(1000);
  
  // All off and wait
  allOff();
  delay(2000);
}

void plotInclination(float angle){
  // Plot a single pixel at the angle provided.
  
  // Turn off old pixel
  strip.setPixelColor(incPixel, 0,0,0);
  
  // Calculate new pixel number
  incPixel = (angle-(360/NUMINC/2)) / (360/NUMINC);
  
  // Rotate to correct for ring orientation
  incPixel = INCREF - incPixel;

  if (incPixel < 0){
    incPixel = NUMINC + incPixel;
  }
  
  incPixel += NUMAZ;

  // Turn on the new pixel
  strip.setPixelColor(incPixel, 50,0,0);
  strip.show();
}

void allOn() {
  // Turn on all inclination pixels
  for (int i=NUMAZ; i<NUMAZ+NUMINC; i++){
    strip.setPixelColor(i,20,20,20);
  }
  strip.show();
}

void allOff() {
  // Turn off all inclination pixels
  for (int i=NUMAZ; i<NUMAZ+NUMINC; i++){
    strip.setPixelColor(i,0,0,0);
  }
  strip.show();
}




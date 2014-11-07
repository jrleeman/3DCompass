/*
  Vector_Display.ino
  
  Displays the orientation of the magnetic vector on two neo-pixil rings.
  North and the inclination are marked by red, faded to blue for contrast.
  
  Created: 10/30/14
  Author: John R. Leeman
  Modified: 10/31/14
  www.johnrleeman.com
  www.github.com/jrleeman
*/
  

#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#define PIXILPIN 13 // Pin on the Arduino that the NeoPixil chain is connected to
#define NUMAZ 24  // Number of pixils on the azimuth ring
#define NUMINC 16 // Number of pixils on the inclination ring

#define INCANGLE 259 //Angle that pixil "zero" is at on inclination ring (nearest degree)
#define AZREF 5 // Pixil Number that the y+ axis points at

#define STREAMDECIMATE 25 // Number of reads to write out to the serial stream
#define DECLINATION 0.22 // Declination

float heading;
float inclination;

// Counter to update serial output more slowly
int count = 0;

// Setup neopixil and magnetometer
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMAZ + NUMINC, PIXILPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Start strip and make all pixils dark
  strip.begin();
  strip.show();
  
  // Start the serial port to stream data back
  Serial.begin(115200);
  Serial.println("3D Compass Demonstration");
  Serial.println("");
  Serial.println("X,Y,Z,Heading,Inclination");
  Serial.println("nT,nT,nT,deg,deg");
  
  // Start the magnetometer
  if(!mag.begin())
  {
    Serial.println("No Magnetic Sensor Detected...");
    while(1);
  }

}

void loop() {
  // Read the sensor
  sensors_event_t event; 
  mag.getEvent(&event);
  
  // Calculate the heading and inclination from the data
  heading = 180/M_PI * calcHeading(event.magnetic.x,event.magnetic.y,event.magnetic.z);
  inclination = 180/M_PI * calcInclination(event.magnetic.x,event.magnetic.y,event.magnetic.z);
  
  // Every #STREAMDECIMATE reads, display data
  if (count%STREAMDECIMATE == 0){
    Serial.print(event.magnetic.x); Serial.print(","); 
    Serial.print(event.magnetic.y); Serial.print(",");
    Serial.print(event.magnetic.z); Serial.print(",");
    Serial.print(heading); Serial.print(",");
    Serial.println(inclination);
    count = 0;
  }
  
  // Plot the Azimuth
  plotAzimuth(360 - heading);
  
  // Plot the Inclination
  plotInclination(inclination,360-heading);
  
  count += 1; 
}

void plotAzimuth(int angle){
  int pix;
  int red;
  int blue;
  int pixDeg;
  for(int i=0;i<NUMAZ;i++){
    pix = i + AZREF;
    if (pix >= NUMAZ){
      pix -= NUMAZ;  
    }
    
    pixDeg = (pix-AZREF)*15;
    if (pixDeg<0){
      pixDeg += 360;
    }
    // Have pixil number in pix, now do color magic
    int diff;
    diff = abs(pixDeg - angle);
    
    if (diff>180){
      diff = abs(360 - diff);
    }
    
    red = 60 - diff;
    if (red<0){
      red = 0;
    }
    
    diff = abs(pixDeg - angle - 180);
    
    if (diff>180){
      diff = abs(360 - diff);
    }
    
    blue = 170 -diff;
    if (blue<0){
      blue = 0;
    }
    //blue = 0;
    strip.setPixelColor(pix,red,0,blue/4);
  }
  strip.show();
}

void plotInclination(float angle, float heading){
  int pix;
  int red;
  int blue;
  int pixDeg;
  
  // Check if negative, and if so put at correct positive angle
  if (angle < 0){
    angle += 360;
  }
  
  // Do azimuth switching if necessary
  if (heading > 180){
    angle = 180 - angle ;
  }
  
  // Make sure we are under 360
  while (angle > 360){
    angle -= 360;
  }
  
  // Make sure we are over zero
  if (angle < 0){
    angle += 360;
  }
    
  for(int i=0;i<NUMINC;i++){
    pix = i;
    pixDeg = INCANGLE - pix*22.5;
    
    if (pixDeg < 0){
      pixDeg += 360;
    }
    
    // Have pixil number in pix, now do color magic
    int diff;
    diff = abs(pixDeg - angle);
    
    if (diff>180){
      diff = abs(360 - diff);
    }
    
    red = 60 - diff;
    if (red<0){
      red = 0;
    }
    
     diff = abs(pixDeg - angle - 180);
    
    if (diff>180){
      diff = abs(360 - diff);
    }
    
    blue = 170 -diff;
    if (blue<0){
      blue = 0;
    }
    
    strip.setPixelColor(pix+NUMAZ,red,0,blue/4);
  }
  strip.show();
}
  


float calcInclination(float x, float y, float z)
{
  /* Given x,y,z componets of a field, return the 
     inclination angle w.r.t horizontal in radians. */
  return atan2(z,sqrt(x*x + y*y));
}

float calcHeading(float x, float y, float z)
{
  /* Given x,y,z componets of a field, return the 
     heading angle w.r.t "north". This assumes that
     x is "east", y is "north", and z is "up".*/   
  float theta;
  theta = atan2(y, x);
  theta += DECLINATION;
  theta -= 0.5 * PI;
  
  if (theta < 0){
    theta += 2*PI;
  }
 
  if (theta > 2*PI){
    theta -= 2*PI;
  }
 
  return theta; 
}

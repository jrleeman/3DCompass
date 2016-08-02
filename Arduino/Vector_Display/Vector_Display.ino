/*
  Vector_Display.ino

  Displays the orientation of the magnetic vector on two neo-pixel rings.
  North and the inclination are marked by red, faded to blue for contrast.

  Created: 10/30/14
  Author: John R. Leeman
  www.johnrleeman.com
  www.github.com/jrleeman

  Modified: 7/20/16
  Author: Ryan Claussen
  wwww.github.com/rtclauss
*/


#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#define PIXELPIN 13 // Pin on the Arduino that the Neopixel chain is connected to
#define NUMAZ 24  // Number of pixels on the azimuth ring
#define NUMINC 16 // Number of pixels on the inclination ring
#define INCANGLE 259 //Angle that pixel "zero" is at on inclination ring (nearest degree)
#define AZANGLE 285 //Angle that pixel zero is at on azimuth ring (nearest degree)
#define STREAMDECIMATE 25 // Number of reads to write out to the serial stream
#define BRIGHTNESS 1 // Increase or decrease for brighter/dimmer colors

// Declination in radians, go to http://geomag.org/models/wmm-declination.html
// to find your declination, then convert it to decimal degrees, and then
// multiply that angle by 2*pi/180. West is negative, East is positive
// This is the declination for Brookings, SD in the 2015-2020 WMM.
#define DECLINATION 0.05

// Floats to store heading and inclination
float heading;
float inclination;

// Counter to update serial output more slowly
int count = 0;

// Setup neopixel and magnetometer
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMAZ + NUMINC, PIXELPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Start strip and make all pixels dark
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

  // Calculate the heading and inclination from the data and convert to degrees
  heading = 180/M_PI * calcHeading(event.magnetic.x,event.magnetic.y,event.magnetic.z);
  inclination = 180/M_PI * calcInclination(event.magnetic.x,event.magnetic.y,event.magnetic.z);

  // Every #STREAMDECIMATE reads, display data
  if (count%STREAMDECIMATE == 0){
    Serial.print(event.magnetic.x); Serial.print(",");
    Serial.print(event.magnetic.y); Serial.print(",");
    Serial.print(event.magnetic.z); Serial.print(",");
    Serial.print(heading); Serial.print(",");
    Serial.println(inclination);
    count = 0; //prevent overflow of int
  }

  // Plot the Azimuth
  plotAzimuth(360 - heading);

  // Plot the Inclination
  plotInclination(inclination,360-heading);

  count += 1;
}

void plotAzimuth(int angle){
  int red;
  int blue;
  int pixDeg;

   for(int i=0;i<NUMAZ;i++){

    // Calculate angle that pixel is at and make sure it is
    // in 0-360
    pixDeg = AZANGLE + i*15;

    if (pixDeg > 360){
      pixDeg -= 360;
    }

    // Color based on difference of given angle and pixel angle
    int diff = abs(pixDeg - angle);

    // If the difference is over 180, we'll loop back to lower values of
    // difference since this is a ring
    if (diff>180){
      diff = abs(360 - diff);
    }

    // Do red coloring, increase the value for a larger red area, decrease
    // for less red. If negative, set to zero
    red = 60 - diff;
    if (red<0){
      red = 0;
    }

    // Do difference 180 from heading for south (blue) coloring and make
    // sure it is in range
    diff = abs(pixDeg - angle - 180);

    if (diff>180){
      diff = abs(360 - diff);
    }

    // Do blue coloring, increase the value for a larger blue area, decrease
    // for less blue. If negative, set to zero
    blue = 170 -diff;
    if (blue<0){
      blue = 0;
    }

    // Set pixel color brightnesses
    red = red*BRIGHTNESS;
    blue = blue*BRIGHTNESS/5;

    // Make sure neither is over 255
    if (red > 255){
      red = 255;
    }

    if (blue > 255){
      blue = 255;
    }
    //Actually set the color on the NeoPixel ring
    strip.setPixelColor(i,red,0,blue);
  }
  //Refresh the NeoPixel displays
  strip.show();
}

void plotInclination(float angle, float heading){
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
    pixDeg = INCANGLE - i*22.5;

    if (pixDeg < 0){
      pixDeg += 360;
    }

    // Color based on difference of given angle and pixel angle
    int diff = abs(pixDeg - angle);

    // If the difference is over 180, we'll loop back to lower values of
    // difference since this is a ring
    if (diff>180){
      diff = abs(360 - diff);
    }

    // Do red coloring, increase the value for a larger red area, decrease
    // for less red. If negative, set to zero
    red = 60 - diff;
    if (red<0){
      red = 0;
    }

    // Do difference 180 from heading for south (blue) coloring and make
    // sure it is in range
    diff = abs(pixDeg - angle - 180);

    if (diff>180){
      diff = abs(360 - diff);
    }

    // Do blue coloring, increase the value for a larger blue area, decrease
    // for less blue. If negative, set to zero
    blue = 170 -diff;
    if (blue<0){
      blue = 0;
    }

    // Set pixel color brightness
    red = red*BRIGHTNESS;
    blue = blue*BRIGHTNESS/5;

    // Make sure neither is over 255
    if (red > 255){
      red = 255;
    }

    if (blue > 255){
      blue = 255;
    }
    //Actually set the color on the NeoPixel ring
    strip.setPixelColor(i+NUMAZ,red,0,blue);
  }
  //Refresh the NeoPixel displays
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
  theta -= DECLINATION;
  theta -= 0.5 * PI;

  if (theta < 0){
    theta += 2*PI;
  }

  if (theta > 2*PI){
    theta -= 2*PI;
  }

  return theta;
}

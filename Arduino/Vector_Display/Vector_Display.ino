#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#define PIXILPIN 13 // Pin on the Arduino that the NeoPixil chain is connected to
#define NUMAZ 24  // Number of pixils on the azimuth ring
#define NUMINC 16 // Number of pixils on the inclination ring

#define AZREF 5 // Pixil Number that the y+ axis points at
#define INCREF 10 // Pixil Number (ring frame) that is to the +x axis side of vertical

float heading;
float inclination;
int azPixel = 0;
int incPixel = 0;

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
  
  heading = 180/M_PI * calcHeading(event.magnetic.x,event.magnetic.y,event.magnetic.z);
  inclination = 180/M_PI * calcInclination(event.magnetic.x,event.magnetic.y,event.magnetic.z);
  
  Serial.print(event.magnetic.x); Serial.print(","); 
  Serial.print(event.magnetic.y); Serial.print(",");
  Serial.print(event.magnetic.z); Serial.print(",");
  Serial.print(heading); Serial.print(",");
  Serial.println(inclination);
  
  plotAzimuth(heading);
  delay(10);
}

void plotAzimuth(float heading){
  strip.setPixelColor(azPixel, 0,0,0);
  azPixel = int((360-heading)/(360/NUMAZ));
  // Rotate so it is like pixil 0 is at +x
  azPixel += AZREF;
  if (azPixel>23)
    axPixel -= 23  
  strip.setPixelColor(azPixel, 50,0,0);
  strip.show();
}

void plotInclination(float inclination){
  strip.setPixelColor(incPixel, 0,0,0);
  incPixel = int((360-inclination)/(360/NUMINC));
  // Rotate so it is like pixil 0 is at +x
  incPixel += INCREF;
  if (incPixel>15)
    incPixel -= 15  
  // Add offset from previous pixel ring
  incPixel += 23
  strip.setPixelColor(incPixel, 50,0,0);
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
  float declinationAngle = 0.22;
  theta = atan2(y, x);
  theta += declinationAngle;
  theta -= 0.5 * PI;
  
  if (theta < 0)
    theta += 2*PI;
 
  
  if (theta > 2*PI)
    theta -= 2*PI;
 
  return theta;
  
}

# 3D Compass

## Bill of Materials
- (1) [Arduino UNO (Red board from SparkFun)](https://www.sparkfun.com/products/12757) $19.95/ea
- (1) [NeoPixel Ring - 16 Element](http://www.adafruit.com/products/1463) $9.95/ea
- (1) [NeoPixil Ring - 24 Element](http://www.adafruit.com/products/1586) $19.95/ea
- (1) [1000uF Capacitor - 6.3V or higher](https://www.sparkfun.com/products/8982) $0.35/ea
- (1) [HMC5883L Magnetometer](http://www.adafruit.com/products/1746) $9.95/ea
- (10) [Brass Heat-Set Insert 4-40](http://www.mcmaster.com/#93365a122/=ub3kod) $11.48/pk. 100
- Hook-up wire (solid)
- 300-500 Ohm Resistor (1/8 watt)
- Nylon 4-40 Screws (1/2 - 1" length)

## Tools Required
- Hobby Knife
- Drill
- Drill Bit 7/64"
- Soldering Iron/Solder
- Flat-head screwdriver
- Hot Glue Gun/Glue

## Assembly Instructions

### 3D Printing Brackets
- Print 1 top and 1 bottom bracket. 60% infill and a raft are recommended.
- Using a soldering iron, insert the heat-set thread inserts. Eight in
bottom plate, 4 in riser posts, 4 in Arduino mounts. Two in top plate for
magnetometer mounts. [Demonstration Video](http://youtu.be/NXAhOEn8nXQ)

### Assemble Top Plate
- Using the 7/64" drill bit, drill out the mounting holes in the magnetometer
breakout bracket. The existing holes are not quite large enough for 4-40
screws.
- Attach the magnetometer with 4-40 nylon screws. Shear the excess length flush
with the bottom of the plate using the hobby knife. Be careful to not break
the superstructure on the part.
- Place the capacitor into the cut-out and secure with a drop of hot glue.
- Place the 16-element NeoPixel ring into the vertical ring holder. Line the
data-in line up with the hole in the bracket. This ensures that data-in, V+,
and GND are all accessable. Secure with a drop of hot-glue.
- Place the 24-element NeoPixel ring onto the riser posts. Line up the data-out
pad to be near the data-in line on the smaller ring. The LED should be directly
above the mounting post. Secure with hot-glue on each post.

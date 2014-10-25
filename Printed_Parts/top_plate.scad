// Resolution
$fn=50;

// Base
width = 73;
thickness = 6;
length = 73;
inside_thickness = 35;

x_offset = 7.5;
y_offset = 5.7;
hole_offset = 5;

mag_x_pos = 13.5;
mag_y_pos = 9;
mag_spacing = 13;

cutout_width = 20;
cutout_height = 45;

difference(){
cube([width,length,thickness]);

translate([10,length/2.-cutout_height/2.,0])cube([cutout_width,cutout_height,10]);
translate([width-10-cutout_width,length/2.-cutout_height/2.,0])cube([cutout_width,cutout_height,10]);

// Holes for magnetometer mount threaded inserts
translate([mag_x_pos,mag_y_pos,0])cylinder(7,3.5814/2,3.5814/2);
translate([mag_x_pos+mag_spacing,mag_y_pos,0])cylinder(7,3.5814/2,3.5814/2);

// Holes for bracket mount 4-40 through hole
translate([hole_offset,hole_offset,0])cylinder(7,1.64,1.64);
translate([hole_offset,length-hole_offset,0])cylinder(7,1.64,1.64);
translate([width-hole_offset,hole_offset,0])cylinder(7,1.64,1.64);
translate([width-hole_offset,length-hole_offset,0])cylinder(7,1.64,1.64);

// Cutout for capacitor
translate([10+cutout_width/2.,length/2.+cutout_height/2.+12,thickness])
rotate([90,0,0])
cylinder(20.,5.5,5.25);

}

// Support post sizes
post_radius = 4.5/2.;
post_height = 45/2.;

fillet_height = 0.05;
fillet_radius = 1.32;

// Neopixil Ring Sizes
largeRing_cc = 59;
smallRing_OD = 45;
smallRing_ID = 31;

// Horizontal Ring Support Posts
translate([width/2.-largeRing_cc/2.,length/2.,thickness])
cylinder(post_height,post_radius,post_radius);
translate([width/2.-largeRing_cc/2.,length/2.,thickness])
cylinder(post_height*fillet_height,post_radius*fillet_radius,post_radius);

translate([width/2.+largeRing_cc/2.,length/2.,thickness])
cylinder(post_height,post_radius,post_radius);
translate([width/2.+largeRing_cc/2.,length/2.,thickness])
cylinder(post_height*fillet_height,post_radius*fillet_radius,post_radius);

translate([width/2.,length/2.-largeRing_cc/2.,thickness])
cylinder(post_height,post_radius,post_radius);
translate([width/2.,length/2.-largeRing_cc/2.,thickness])
cylinder(post_height*fillet_height,post_radius*fillet_radius,post_radius);

translate([width/2.,length/2.+largeRing_cc/2.,thickness])
cylinder(post_height,post_radius,post_radius);
translate([width/2.,length/2.+largeRing_cc/2.,thickness])
cylinder(post_height*fillet_height,post_radius*fillet_radius,post_radius);

// Supports for vertical ring

translate([width/2.,length/2,smallRing_OD/2.+thickness])
rotate([0,270,0])

difference(){
// Support block for ring
translate([(smallRing_OD+2)/-2.,(smallRing_OD+2)/-2.,0]) cube([(smallRing_OD+2)/2.,(smallRing_OD+2),3]);

// Rectangle to cut shape to half circle
translate([0,(smallRing_OD+10)/-2.,0]) cube([(smallRing_OD+10),(smallRing_OD+10),4]);

// Recessed disc to hold ring
cylinder(2,smallRing_OD/2.,smallRing_OD/2.);

// Cutout hole in center
cylinder(4,smallRing_ID/2.,smallRing_ID/2.);

// Wire hole cutout
translate([-21*0.707,21*0.707,0])cylinder(4,1.5,1.5);
}


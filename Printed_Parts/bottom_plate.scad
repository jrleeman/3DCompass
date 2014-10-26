// Resolution
$fn=50;

// Base
width = 73;
thickness = 6;
length = 73;
inside_thickness = 35;

x_offset = 9.5;
y_offset = 3.2;
hole_offset = 5;

cutout_width = 60;
cutout_height = 40;

post_size = 5;
post_height = 20;

4_40_radius = 1.64;
4_40_depth = 6.6;

difference(){
cube([width,length,thickness]);

translate([width/2.-cutout_width/2.,length/2.-cutout_height/2. - y_offset -2,0])cube([cutout_width,cutout_height,10]);

// Holes for Arduino mount threaded inserts
translate([3*2.54+x_offset,1*2.54+y_offset,0])cylinder(7,3.5814/2,3.5814/2);
translate([14*2.54+x_offset,1*2.54+y_offset,0])cylinder(7,3.5814/2,3.5814/2);
translate([1*2.54+x_offset,21.5*2.54+y_offset,0])cylinder(7,3.5814/2,3.5814/2);
translate([20*2.54+x_offset,21*2.54+y_offset,0])cylinder(7,3.5814/2,3.5814/2);
}

//Corner posts
difference(){
union(){
translate([hole_offset,hole_offset,thickness])
cylinder(post_height,post_size/2.,post_size/2.);

translate([hole_offset-post_size/2.+4_40_radius*1.5,hole_offset-post_size/2.+4_40_radius*1.5,thickness+post_height/2])
cylinder(post_height/2,4_40_radius*1.5,post_size);
}

// Holes for bracket mount 4-40 through hole
translate([hole_offset,hole_offset,thickness+post_height-4_40_depth])
cylinder(4_40_depth+1,4_40_radius,4_40_radius);
}

difference(){
union(){
translate([hole_offset,length-hole_offset,thickness])
cylinder(post_height,post_size/2.,post_size/2.);

translate([hole_offset-post_size/2.+4_40_radius*1.5,length-hole_offset-post_size/2.+4_40_radius*1.5,thickness+post_height/2])
cylinder(post_height/2,4_40_radius*1.5,post_size);
}

translate([hole_offset,length-hole_offset,thickness+post_height-4_40_depth])
cylinder(4_40_depth+1,4_40_radius,4_40_radius);

}

difference(){
union(){
translate([width-hole_offset,length-hole_offset,thickness])
cylinder(post_height,post_size/2.,post_size/2.);

translate([width-hole_offset-post_size/2.+4_40_radius*1.5,length-hole_offset-post_size/2.+4_40_radius*1.5,thickness+post_height/2])
cylinder(post_height/2,4_40_radius*1.5,post_size);
}

translate([width-hole_offset,length-hole_offset,thickness+post_height-4_40_depth])
cylinder(4_40_depth+1,4_40_radius,4_40_radius);

}

difference(){
union(){
translate([width-hole_offset,hole_offset,thickness])
cylinder(post_height,post_size/2.,post_size/2.);

translate([width-hole_offset-post_size/2.+4_40_radius*1.5,hole_offset-post_size/2.+4_40_radius*1.5,thickness+post_height/2])
cylinder(post_height/2,4_40_radius*1.5,post_size);
}

translate([width-hole_offset,hole_offset,thickness+post_height-4_40_depth])
cylinder(4_40_depth+1,4_40_radius,4_40_radius);

}



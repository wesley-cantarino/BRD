int leg_right_pin = 7;
int leg_left_pin = 11;

int foot_right_pin = 6;
int foot_left_pin = 10;

int buzzer = 8;
//echo 2 and trig 3

#define max_angle 165
#define min_angle 15

#define max_angle_leg 140
#define min_angle_leg 40

#define nat_angle 90

#define walking_angle_foot 40
#define walking_angle_leg 40

//library
#include <Servo.h>

Servo leg_right;
Servo leg_left;

Servo foot_right;
Servo foot_left;

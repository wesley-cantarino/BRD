int leg_right_pin = 7;
int leg_left_pin = 11;

int foot_right_pin = 6;
int foot_left_pin = 10;

int buzzer = 8;


#define max_angle 165
#define min_angle 15

#define max_angle_leg 140
#define min_angle_leg 40

#define nat_angle 90


//library
#include <Servo.h>

Servo leg_right;
Servo leg_left;

Servo foot_right;
Servo foot_left;

#include "Omnius.h"

void setup ()
{
  Serial.begin(115200);
  Serial.println("Serial was start :)");

  leg_right.attach(leg_right_pin);
  leg_left.attach(leg_left_pin);

  foot_right.attach(foot_right_pin);
  foot_left.attach(foot_left_pin);

  natural_position();
}

void loop ()
{
  //walk_left(2);
  //animation_atention_for_you ();

  /***********serial test***********/
  // serial_reading();
  //
  // if(reading != "")
  // {
  //   Serial.println(serial_return("legr"));
  // }

  /***********teste basico/************/
  //test_individual_motor(true, false, true, true); //leg, foot , left, right
  test_motor();
}

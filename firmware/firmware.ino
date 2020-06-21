int leg_right_pin = 7;
int leg_left_pin = 11;

int foot_right_pin = 6;
int foot_left_pin = 10;

int buzzer = 8;

int max_angle = 165, min_angle = 15;
int max_angle_leg = 120, min_angle_leg = 60;
int nat_angle = 90;
int nat_angle_lr = 15, nat_angle_ll = 90, nat_angle_fr = 90, nat_angle_fl = 90;


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
  animation_atention_for_you ();

  /***********serial test***********/
  // serial_reading();
  //
  // if(reading != "")
  // {
  //   Serial.println(serial_return("legr"));
  // }

  /***********teste basico/************/
  //test_individual_motor(true, false, true, true); //leg, foot , left, right
  //test_motor();
}

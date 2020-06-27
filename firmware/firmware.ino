#include "user_default.h"
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
  delay(1500);
}

void loop ()
{
  //alongamento(2);

  //falta muito
  //walk_left(2);

  //esta quase
  walking(true);  //andar para frente (true)
  delay(20);
  //walking(false); //andar para frente (true)

  //walk();

  /***********serial test***********/
  // serial_reading();
  //
  // if(reading != "")
  // {
  //   Serial.println(serial_return("legr"));
  // }

  /***********teste basico/************/
  //test_individual_motor(true, true, true, true, 35); //leg, foot , left, right, time
  //test_motor();
}

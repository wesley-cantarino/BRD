/*
Trigger 3
Echol 2

the point of the frent view

leg right  7
foot right 6

leg left  11
foot left 10
*/

int leg_right_pin = 7;
int leg_left_pin = 11;

int foot_right_pin = 6;
int foot_left_pin = 10;

//library
#include <Servo.h>

Servo leg_right;
Servo leg_left;

Servo foot_right;
Servo foot_left;

void setup ()
{
  Serial.begin(115200);
  Serial.println("Serial was start :)");

  leg_right.attach(leg_right_pin);
  leg_left.attach(leg_left_pin);

  foot_right.attach(foot_right_pin);
  foot_left.attach(foot_left_pin);
}

void loop ()
{
  test_motor();
}


void test_motor()
{
  for(int pos = 10; pos < 20; pos++)
  {
    leg_right.write(pos);
    delay(20);
  }
  for(int pos = 20; pos > 10; pos--)
  {
    leg_right.write(pos);
    delay(20);
  }

  delay(200);

  for(int pos = 90; pos < 110; pos++)
  {
    foot_right.write(pos);
    delay(20);
  }
  for(int pos = 110; pos > 90; pos--)
  {
    foot_right.write(pos);
    delay(20);
  }

  delay(200);

  for(int pos = 90; pos < 110; pos++)
  {
    leg_left.write(pos);
    delay(20);
  }
  for(int pos = 110; pos > 90; pos--)
  {
    leg_left.write(pos);
    delay(20);
  }

  delay(200);

  for(int pos = 90; pos < 110; pos++)
  {
    foot_left.write(pos);
    delay(20);
  }
  for(int pos = 110; pos > 90; pos--)
  {
    foot_left.write(pos);
    delay(20);
  }

  delay(200);
}

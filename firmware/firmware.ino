//Nao consegue andar para tras
//Escrever biblioteca ultrassonico

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
  melody();
  delay(2000); //2s
}

void loop ()
{
  ///*
  //alongamento(2);

  //walking(true, 20);  //andar para frente (true)
  //delay(20);
  //walking(false); //andar para frente (true)

  melody();

  //ultrassonico();
  //*/

  /**********Acao***************/
  /*
  //A cada 5 passos dar uma alongada
  alongamento(1);
  for(int i = 0; i < 5; i++)
  {
    walking(true, 20);  //andar para frente (true)
    delay(20);
  }
  */

  /***********serial test***********/
  // serial_reading();
  //
  // if(reading != "")
  // {
  //   Serial.println(serial_return("legr"));
  // }

  /***********teste basico/************/
  ///*
  //test_individual_motor(true, false, false, true, 35); //leg, foot , left, right, time
  //test_motor();
  //test_individual_motor(false, true, true, true, 40); //leg, foot , left, rightt, time
  //*/
}

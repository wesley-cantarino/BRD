/********************************************/
/****************Basic funtion***************/
/********************************************/

void natural_position ()
{
  leg_left.write(nat_angle);
  leg_right.write(nat_angle);

  foot_left.write(nat_angle);
  foot_right.write(nat_angle);

  delay(15);
}

void bip ()
{
  tone(buzzer, 220);
  delay(200);
  tone(buzzer, 440);
  delay(200);
  tone(buzzer, 660);
  delay(200);

  noTone(buzzer);
}

/********************************************/
/*******************Serial*******************/
/********************************************/

char r;
String reading = "";

void serial_reading()
{
  bool stop = false;

  while ((Serial.available() > 0) && !stop) //enquanto tiver informacao para ler e stop == false
  {
    r = Serial.read(); //faz leitura do ultimo char
    //Serial.println(r);

    if(r == ';') // ; indica que acabou a leitura
      stop = true;
    else
      reading += r;  //preencher a string
  }

  stop = false;
}

int serial_return(String procurar)
{
  if(reading.indexOf(procurar) >= 0) //indexOf retorna o indice que começa a string procurar
  {
    String _read = reading.substring(reading.indexOf("=") + 1, reading.indexOf(";"));
    Serial.println(_read);

    return _read.toInt();
  }
  else
  {
    return -1;
  }
}

/********************************************/
/*********************test*******************/
/********************************************/


void test_motor()
{
  for(int pos = nat_angle; pos < max_angle_leg; pos++)
  {
    leg_right.write(pos);
    delay(20);
  }
  for(int pos = max_angle_leg; pos > min_angle_leg; pos--)
  {
    leg_right.write(pos);
    delay(20);
  }
  for(int pos = min_angle_leg; pos < nat_angle; pos++)
  {
    leg_right.write(pos);
    delay(20);
  }

  delay(200);

  for(int pos = nat_angle; pos < max_angle; pos++)
  {
    foot_right.write(pos);
    delay(20);
  }
  for(int pos = max_angle; pos > nat_angle; pos--)
  {
    foot_right.write(pos);
    delay(20);
  }

  delay(200);

  for(int pos = nat_angle; pos < max_angle_leg; pos++)
  {
    leg_left.write(pos);
    delay(20);
  }
  for(int pos = max_angle_leg; pos > min_angle_leg; pos--)
  {
    leg_left.write(pos);
    delay(20);
  }
  for(int pos = min_angle_leg; pos < nat_angle; pos++)
  {
    leg_left.write(pos);
    delay(20);
  }


  delay(200);

  for(int pos = nat_angle; pos < max_angle; pos++)
  {
    foot_left.write(pos);
    delay(20);
  }
  for(int pos = max_angle; pos > nat_angle; pos--)
  {
    foot_left.write(pos);
    delay(20);
  }

  delay(200);
}

void test_individual_motor (bool l, bool f, bool left, bool right, int _timer)
{
  if(l)
  {
    for(int pos = nat_angle; pos < max_angle_leg; pos++)
    {
      if(left)
        leg_left.write(pos);
      if(right)
        leg_right.write(pos);
      delay(_timer);
    }

    for(int pos = max_angle_leg; pos > min_angle_leg; pos--)
    {
      if(left)
        leg_left.write(pos);
       if(right)
        leg_right.write(pos);
      delay(_timer);
    }

    for(int pos = min_angle_leg; pos < nat_angle; pos++)
    {
      if(left)
        leg_left.write(pos);
      if(right)
        leg_right.write(pos);
      delay(_timer);
    }
  }

  if(f)
  {
    for(int pos = nat_angle; pos < max_angle; pos++)
    {
      if(left)
        foot_left.write(pos);
      if(right)
        foot_right.write(pos);
      delay(_timer);
    }

    for(int pos = max_angle; pos > min_angle; pos--)
    {
      if(left)
        foot_left.write(pos);
      if(right)
        foot_right.write(pos);
      delay(_timer);
    }

    for(int pos = min_angle; pos < nat_angle; pos++)
    {
      if(left)
        foot_left.write(pos);
      if(right)
        foot_right.write(pos);
      delay(_timer);
    }
  }
}

/********************************************/
/******************animation*****************/
/********************************************/
void walking (bool sentido)
{
  if(sentido)
  {
    //inclinar para esquerda. se equilibrar em uma perna
    for(int i = nat_angle; i < walking_angle_foot + nat_angle; i++)
    {
      foot_left.write(i);
      foot_right.write(max_angle);
      delay(15);
    }

    //girar corpitiu para frente
    for(int i = nat_angle; i < walking_angle_leg + nat_angle; i++)
    {
      leg_left.write(-i + 180);
      leg_right.write(-i + 180);
      foot_right.write(i);
      delay(15);
    }

    //se equilibrarnas duas pernas
    for(int i = walking_angle_foot + nat_angle; i > nat_angle; i--)
    {
      foot_left.write(i);
      delay(15);
    }
    foot_right.write(nat_angle);

    //now, segundo passo

    //inclinar para direita. se equilibrar em uma perna
    for(int i = nat_angle; i < walking_angle_foot + nat_angle; i++)
    {
      foot_right.write(-i + 180);
      foot_left.write(min_angle);
      delay(15);
    }

    //girar corpitiu para frente
    for(int i = nat_angle; i < walking_angle_leg + nat_angle; i++)
    {
      leg_right.write(-i + 180);
      leg_left.write(-i + 180);
      foot_left.write(i);
      delay(15);
    }

    for(int i = walking_angle_foot + nat_angle; i > nat_angle; i--)
    {
      foot_left.write(i);
      delay(15);
    }
    foot_right.write(nat_angle);

    natural_position();
  }
  else
  {

  }
}

void walk_left (int steps)
{
  for(int i = 0; i < steps; i++)
  {
    for(int pos = nat_angle; pos > min_angle; pos--)
    {
      foot_left.write(pos);
      foot_right.write(-pos + 180);
      delay(35);
    }

    for(int pos = min_angle; pos < nat_angle; pos++)
    {
      foot_left.write(pos);
      foot_right.write(-pos + 180);
      delay(35);
    }
  }
}

void alongamento (int steps)
{
  for(int i = 0; i < steps; i++)
  {
    for(int pos = nat_angle; pos < max_angle; pos++)
    {
      foot_left.write(pos);
      foot_right.write(-pos + 180);
      delay(25);
    }

    bip();

    for(int pos = max_angle; pos > min_angle; pos--)
    {
      foot_left.write(pos);
      foot_right.write(-pos + 180);
      delay(25);
    }

    for(int pos = min_angle; pos < nat_angle; pos++)
    {
      foot_left.write(pos);
      foot_right.write(-pos + 180);
      delay(25);
    }

    test_individual_motor(true, true, true, true, 35);
  }
}

/********************************************/
/******************new_here*****************/
/********************************************/

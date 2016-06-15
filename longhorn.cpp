#include "Arduino.h"
#include "Mirobot.h"

void Mirobot::draw_line(int mm)
{
  pendown();
  forward(mm);
  penup();
  back(mm);
}

void Mirobot::draw_square(int mm)
{
  pendown();
  for (int i = 0; i < 4; i++) {
    forward(mm);
    left(90);
  }
}

void Mirobot::draw_parallel_lines(int mm)
{
  for (int x = 0; x < 2; x++)
  {
    pendown();
    forward(mm);
    penup();
    left(90);
    forward(mm);
    left(90);
  }
}


void Mirobot::draw_circle()
{
  pendown();
  for (int i = 0; i < 36; i++) {
    forward(10);
    left(10);
  }
}

void Mirobot::draw_heart()
{
  forward(200);
  for (int i=0; i<18; i++)
  {
    if (i & 1 == 1)
      forward(18);
    else 
      forward(17);
    left(10);
  }
  right(90);
  for (int i=0; i<18; i++)
  {
    if (i & 1 == 1)
      forward(18);
    else 
      forward(17);
    left(10);
    
  }
  forward(200);
}


void Mirobot::draw_artwork()
{
    for (int i=0; i<4; i++)
    {
      draw_heart();
      left(180);
    }

    //draw_line(400);
    //left(60);
    //draw_line(100);
}

void Mirobot::follow_line()
{
  int diff = analogRead(LEFT_LINE_SENSOR) - analogRead(RIGHT_LINE_SENSOR);
  if (diff > 5) {
    left(5);
  }if (diff < -5) {
    right(5);
  }//else {
  forward(5);
  //}
}

void Mirobot::collision()
{
  boolean collideLeft = !digitalRead(LEFT_COLLIDE_SENSOR);
  boolean collideRight = !digitalRead(RIGHT_COLLIDE_SENSOR);
  if (_collideState == NORMAL) {
    if (collideLeft) {
      _collideState = LEFT_REVERSE;
      back_nb(50);
    } else if (collideRight) {
      _collideState = RIGHT_REVERSE;
      back_nb(50);
    } else {
      forward(1);
    }
  } else if (ready()) {
    switch (_collideState) {
      case LEFT_REVERSE :
        _collideState = LEFT_TURN;
        right_nb(90);
        break;
      case RIGHT_REVERSE :
        _collideState = RIGHT_TURN;
        left_nb(90);
        break;
      case LEFT_TURN :
      case RIGHT_TURN :
        _collideState = NORMAL;
    }
  }
}



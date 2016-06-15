#include "CrossRoads.h"
#include "Mirobot.h"


CrossRoads* prevJunct;
int prevTurn = 1;
int oneSide = 0;
int orientation = 0;
int x = 0;
int y = 0;
//0: north
//1: east
//2: south
//3: west

void rotate(int amount)
{
  orientation+=amount;
  orientation%=4;
}

void updateCoords(int move)
{
  switch (orientation)
    {
      case 0:
        y+=move;
        break;
      case 1:
        x-=move;
        break;
      case 2:
        y-=move;
        break;
      case 3:
        x+=move;
    }
}

void Mirobot::do_maze()
{
  boolean collideLeft = !digitalRead(LEFT_COLLIDE_SENSOR);
  boolean collideRight = !digitalRead(RIGHT_COLLIDE_SENSOR);

  if (collideLeft && collideRight) {
    //Dead end
    oneSide = 0;
    int dx = abs(x - prevJunct->deadX);
    int dy = abs(y - prevJunct->deadY);

    //Back up.
    back(50);
    updateCoords(-50);
    
    if (dx > 80 || dy > 80)
    {
      //Reset been state
      //TODO: push prevJunct instead.
      prevJunct = new CrossRoads();
      prevJunct->been[(orientation + 2) % 4] = true;
      prevJunct->deadX = x;
      prevJunct->deadY = y;
    }
    
    prevJunct->been[orientation] = true;
    if (!prevJunct->been[(orientation - prevTurn) % 4])
    {
      if (prevTurn < 0)
        right(-90 * prevTurn);
      else
        left(90 * prevTurn);
      rotate(-prevTurn);
      prevTurn = -prevTurn;
    } else if (!prevJunct->been[(orientation + prevTurn) % 4]) {
      if (prevTurn < 0)
        left(-90 * prevTurn);
      else
        right(90 * prevTurn);
      rotate(prevTurn);
    } else if (!prevJunct->been[(orientation + 2) % 2]) {
      left(180);
      rotate(2);
    } else {
      //If we used all three locations then we are screwed.
      while(true)
      {
        beep(20);
      }
    }
  }else if (collideLeft || collideRight) {
    //Back up and try again.
    oneSide++;
    if (oneSide >= 5)
    {
      back(50);
      left(90);
      rotate(-1);
      if (collideLeft) {
        back(20);
        updateCoords(-20);
      } else {
        forward(20);
        updateCoords(20);
      }
      right(90);
      rotate(1);
    }
  }else {
    oneSide = 0;
    forward(1);
    updateCoords(1);
  }
}


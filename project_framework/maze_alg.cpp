#include "CrossRoads.h"
#include "Mirobot.h"


CrossRoads* prevJunct;
int prevTurn = 1;
int oneSide = 0;
int orientation = 0;
long x = 0;
long y = 0;
//0: north
//1: east
//2: south
//3: west

int reorientate(int amount)
{
  
  int val = (orientation+amount) & 3;
}

void rotate(int amount)
{
  orientation = reorientate(amount);
  
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

  if (collideLeft || collideRight) {
    //Dead end
    oneSide = 0;
    long dx = abs(x - prevJunct->deadX);
    long dy = abs(y - prevJunct->deadY);

    //Back up.
    back(50);
    updateCoords(-50);

    
    
    if (dx > 120 || dy > 120)
    {
      beep(200);
      //Reset been state
      //TODO: push prevJunct instead.
      prevJunct = new CrossRoads();
      prevJunct->been[reorientate(2)] = true;
      prevJunct->inOrient = reorientate(2);
      prevJunct->deadX = x;
      prevJunct->deadY = y;
    }
    
    prevJunct->been[orientation] = true;
    if (!prevJunct->been[reorientate(-prevTurn)])
    {
      if (prevTurn < 0)
        right(-90 * prevTurn);
      else
        left(90 * prevTurn);
      rotate(-prevTurn);
      prevTurn = -prevTurn;
    } else if (!prevJunct->been[reorientate(prevTurn)]) {
      if (prevTurn < 0)
        left(-90 * prevTurn);
      else
        right(90 * prevTurn);
      rotate(prevTurn);
    } else if (!prevJunct->been[reorientate(2)]) {
      left(180);
      rotate(2);
    } else {
      //If we used all three locations then we are screwed.
      int move = prevJunct->inOrient - orientation;
      right(90 * move);
      rotate(move);
      beep3(1000);
    }
  }else if (collideLeft || collideRight) {
    //NOTE only call this case when we are retracing.
    //Back up and try again.
    oneSide++;
    if (oneSide >= 50)
    {
      updateCoords(-45);
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
  beep(20);
}


#include "CrossRoads.h"
#include "Mirobot.h"

bool panic = false;
int index = 0;
CrossRoads* prevJunct;
int prevTurn = 1;
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
  return val;
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

  if (panic)
  {
    forward(50);
    back(50);
  }

  if (collideLeft || collideRight) {
    //Dead end
    long dx = abs(x - prevJunct->deadX);
    long dy = abs(y - prevJunct->deadY);

    //Back up.
    back(50);
    updateCoords(-50);
    
    if (dx > 150 || dy > 150)
    {
      //Reset been state
      //TODO: push prevJunct instead.
      prevJunct = new CrossRoads();
      prevJunct->inOrient = reorientate(2);
      prevJunct->deadX = x;
      prevJunct->deadY = y;
    }
    
    prevJunct->walls++;
    switch (prevJunct->walls)
    {
    case 1: //Hit once
      if (prevTurn < 0)
        right(-88 * prevTurn);
      else
        left(88 * prevTurn);
      rotate(-prevTurn);
      prevTurn = -prevTurn;
      break;
    case 2: //Turn other way.
      left(180);
      rotate(2);
      break;
      
    case 3: //Dead-end
      int move = prevJunct->inOrient - orientation;
      if (move == 0)
      {
        panic = true;
        return;
      }
      right(88 * move);
      rotate(move);
    }
  }else {
    forward(10);
    updateCoords(10);
  }
}


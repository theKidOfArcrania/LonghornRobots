#include "CrossRoads.h"
#include "Mirobot.h"

bool panic = false;
char freqs[8] = {(char)440, (char)360, (char)570, (char)806, (char)1100, (char)889, (char)452, (char)1146};
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
    tone(SPEAKER_PIN, freqs[index++], 200);
    delay(200);
    if (index >= 8)
      index = 0;
    return;
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
      if (move == 0)
      {
        panic = true;
        return;
      }
      right(90 * move);
      rotate(move);
    }
  }else {
    forward(10);
    updateCoords(10);
  }
}


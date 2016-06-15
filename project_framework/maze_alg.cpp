#include "Mirobot.h"

bool been[4];
int orientation = 0;
int deadX = -1;
int deadY = -1;
int x = 0;
int y = 0;
int prevTurn;
//0: north
//1: east
//2: south
//3: west

void Mirobot::do_maze()
{
  boolean collideLeft = !digitalRead(LEFT_COLLIDE_SENSOR);
  boolean collideRight = !digitalRead(RIGHT_COLLIDE_SENSOR);

  if (collideLeft && collideRight) {
    //Dead end
    int dx = abs(x - deadX);
    int dy = abs(y - deadY);
    if (dx > 80 || dy > 80)
    {
      //Reset been state
      been[0] = been[1] = been[2] = been[3] = false;
    }
    been[orientation] = true;
    
    back(50);
    switch (orientation)
    {
      case 0:
        y-=50;
        break;
      case 1:
        x+=50;
        break;
      case 2:
        y+=50;
      case 3:
        x-=50;
    }
    deadX = x;
    deadY = y;
    //TODO: turn with optimization.

    //TODO: If we used all three locations then we are screwed.
  }else if (collideLeft || collideRight) {
    //TODO: this case
  }else {
    forward(1);
    switch (orientation)
    {
      case 0:
        y++;
        break;
      case 1:
        x--;
        break;
      case 2:
        y--;
      case 3:
        x++;
    }
  }
}


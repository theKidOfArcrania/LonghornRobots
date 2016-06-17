
#include "Mirobot.h"
#include "CrossRoads.h"
void play_DeepInTheHeart();
/*
This sketch shows how you can program Mirobot directly in the Arduino environment.
*/

Mirobot mirobot;
bool calibrated = false;

void setup(){
  Serial.begin(57500);
  mirobot.setup(Serial);

}

void loop(){
   if (!calibrated) {
     mirobot.calibrateTurn(90/95.0);
   }
   calibrated = true;
   //mirobot.draw_line(200);
   mirobot.draw_square(100);
   mirobot.calibrateTurn(1.0);
   mirobot.draw_square(100);
   //mirobot.draw_parallel_lines(100);
   //mirobot.draw_circle();
   //mirobot.draw_heart();
   //mirobot.draw_artwork();
   //mirobot.follow_line();
   //mirobot.do_maze();
   //mirobot.collision();

   //delay(3000); 
}




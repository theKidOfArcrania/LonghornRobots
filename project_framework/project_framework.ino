
#include "Mirobot.h"
/*
This sketch shows how you can program Mirobot directly in the Arduino environment.
*/

Mirobot mirobot;

void setup(){
  Serial.begin(57500);
  mirobot.setup(Serial);

}

void loop(){
   //mirobot.calibrateMove(200.0/190.0);
   //mirobot.draw_line(200);
   //mirobot.draw_square(100);
   //mirobot.draw_parallel_lines(100);
   //mirobot.draw_circle();
   //mirobot.draw_heart();
   mirobot.draw_artwork();

   //mirobot.follow_line();
   //mirobot.collision();

   mirobot.beep(20); 
   //delay(3000); 
}



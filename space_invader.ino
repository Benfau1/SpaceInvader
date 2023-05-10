#include <Gamebuino-Meta.h>
#include "spriteShuttle.h"


/* Piskel data for "New Piskel" */


Image PlayerIdling(PlayerIdlingData);
//Player's coords and speed
int move_x= 32;
int move_y = 56;
int speedX = 1;

const int rightStop = 8;
const int leftStop = 5;
void setup()
{
  gb.begin();
}

void loop()
{
  while (!gb.update())
    ;
  gb.display.clear();
  
  
  if (gb.buttons.repeat(BUTTON_RIGHT, 0) && move_x < gb.display.width() - rightStop )
  {
    move_x++;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 0) && move_x > 0 )
  {
    move_x--;
  }
  gb.display.drawImage(move_x,move_y, PlayerIdling);
}

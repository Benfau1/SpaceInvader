#include <Gamebuino-Meta.h>
#include <avr/pgmspace.h>
#include <SPI.h>
#include "spriteShuttle.h"
#include "HeartFull.h"


/* Piskel data for "New Piskel" */

// Player sprite
Image spaceShuttle(PlayerIdlingData);
// Heart Sprite
Image heartFull0(HEART_FULL);
Image heartFull1(HEART_FULL);
Image heartFull2(HEART_FULL);

// Sounds
const uint16_t blast_sound[] PROGMEM = {0x0045, 0x7849, 0x784D, 0xA28, 0x0000};

//Player's coords and speed
int move_x= 32;
int move_y = 56;
int speedX = 1;

int counterForShooting = 30;

const int rightStop = 8;
const int leftStop = 5;

// Bullet properties
#define NUMBULLETS 10
int bullets_x[NUMBULLETS];
int bullets_y[NUMBULLETS];
const float bullets_vy = 2.5;
boolean bullets_active[NUMBULLETS];
short last_invader_shoot = -1;
int bulletN = 0;

void setup()
{
  gb.begin();
}

void loop()
{
  while (!gb.update())
    ;
  gb.display.clear();
  
  // When moving shuttle increase or decrease speed
  if (gb.buttons.repeat(BUTTON_RIGHT, 0) && move_x < gb.display.width() - rightStop )
  {
    move_x++;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 0) && move_x > 0 )
  {
    move_x--;
  }

  gb.display.setCursorY(0);
  gb.display.setCursorX(60);
  gb.display.print(counterForShooting);
  if ( gb.buttons.pressed(BUTTON_A) && counterForShooting == 30)
  {
     gb.sound.play(blast_sound, 0);
     InitializeBulltet(move_x , move_y);
     counterForShooting = 1;
  }
  if(counterForShooting != 30){
  counterForShooting++;
 }
   
  
  
  gb.display.drawImage(move_x,move_y, spaceShuttle);
  gb.display.drawImage(0,0, heartFull0);
  gb.display.drawImage(8,0, heartFull1);
  gb.display.drawImage(16,0, heartFull2);

  TrackBulletsOnMap();
}

void InitializeBulltet(int move_x , int move_y) {
        bulletN++;
        bullets_x[bulletN] = move_x+3;
        bullets_y[bulletN] = move_y;
        bullets_active[bulletN] = true;
        if(bulletN == 9){
          bulletN=0;
        }
}

void TrackBulletsOnMap(){
  for(byte thisBullet = 0; thisBullet < NUMBULLETS; thisBullet++) {
    if(bullets_active[thisBullet]){
        bullets_y[thisBullet] = bullets_y[thisBullet] - bullets_vy;
        gb.display.fillRect(bullets_x[thisBullet], bullets_y[thisBullet], 1, 3);
      }
      if (bullets_y[thisBullet] <= 0) {
        bullets_active[thisBullet] = false;
        bullets_x[thisBullet] = 0;
        bullets_y[thisBullet] = 0;
      }
  }
}



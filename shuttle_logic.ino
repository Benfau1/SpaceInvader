#include "spriteShuttle.h"
#include <Gamebuino-Meta.h>

// Player sprite
Image spaceShuttle(PlayerIdlingData);

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
int isPlayerShooting = false;
int bullets_x[NUMBULLETS];
int bullets_y[NUMBULLETS];
int bullet_width = 1;
int bullet_height = 3;
const float bullets_vy = 2.5;
bool bullets_active[NUMBULLETS];
short last_invader_shoot = -1;
int bulletN = 0;
float playerBulletPositionX;
float playerBulletPositionY;
const float playerBulletSpeed = 2.5;

void drawShuttle(){
  // When moving shuttle should change direction
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
  // Waiting 30 frames to allow shooting
  if(counterForShooting != 30){
    counterForShooting++;
  }
   
  gb.display.drawImage(move_x,move_y, spaceShuttle);
  if(isPlayerShooting){
    TrackBulletsOnMap();
  }
}

void InitializeBulltet(int move_x , int move_y) {
  isPlayerShooting = true;
  playerBulletPositionX = move_x+3;
  playerBulletPositionY = move_y;
  gb.display.fillRect(playerBulletPositionX, playerBulletPositionY, bullet_width, bullet_height);
}

void TrackBulletsOnMap(){
  playerBulletPositionY -= playerBulletSpeed;
  
  if(!checkAlienCollision(playerBulletPositionX, playerBulletPositionY,bullet_width,bullet_height) && playerBulletPositionY >= 0){
    gb.display.fillRect(playerBulletPositionX, playerBulletPositionY, bullet_width, bullet_height);
  }
  else {
    isPlayerShooting = false;
  }
}

int getPlayerLocationX(){
  return move_x;
}
int getPlayerLocationY(){
  return move_y;
}

int getPlayerSizeX(){
  return spaceShuttle.width();
}
int getPlayerSizeY(){
  return spaceShuttle.height();
}


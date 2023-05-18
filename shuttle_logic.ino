#include "spriteShuttle.h"

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
int bullets_x[NUMBULLETS];
int bullets_y[NUMBULLETS];
int bullet_width = 1;
int bullet_height = 3;
const float bullets_vy = 2.5;
bool bullets_active[NUMBULLETS];
short last_invader_shoot = -1;
int bulletN = 0;



//test rectangle alien
int rect_x=32;
int rect_y=32;
int rect_width=5;
int rect_height=2;

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
        
        //Check collision with alien
        if (gb.collide.rectRect(bullets_x[thisBullet], bullets_y[thisBullet],bullet_width , bullet_height,
                            rect_x, rect_y, rect_width, rect_height)){
                               lives_remaining--;
                               resetBullet(&bullets_active[thisBullet] , &bullets_x[thisBullet] , &bullets_y[thisBullet]);
                            }
        else{
               gb.display.fillRect(rect_x, rect_y, rect_width, rect_height);           
        }
        gb.display.fillRect(bullets_x[thisBullet], bullets_y[thisBullet], 1, 3);
      }
      if (bullets_y[thisBullet] <= 0) {
        resetBullet(&bullets_active[thisBullet] , &bullets_x[thisBullet] , &bullets_y[thisBullet]);
      }
  }
}

void resetBullet(bool *bullets_active , int *bullet_x , int *bullet_y){
        *bullets_active = false;
        *bullet_x = 0;
        *bullet_y = 0;
}


#include "HeartFull.h"
#include "HeartVoid.h"

int lives_remaining = 3;
int frameCounter = 0;

// Heart Sprite
Image heartFull0(HEART_FULL);
Image heartFull1(HEART_FULL);
Image heartFull2(HEART_FULL);

//Hearts void
Image heartVoid0(HEART_VOID);
Image heartVoid1(HEART_VOID);
Image heartVoid2(HEART_VOID);


void drawHealthLevel(){
  switch(lives_remaining){
     case 3:
      gb.display.drawImage(0,0, heartFull0);
      gb.display.drawImage(8,0, heartFull1);
      gb.display.drawImage(16,0, heartFull2);
      break;
    case 2:
      gb.display.drawImage(0,0, heartFull0);
      gb.display.drawImage(8,0, heartFull1);
      gb.display.drawImage(16,0, heartVoid2);
      break;
    case 1:
      gb.display.drawImage(0,0, heartFull0);
      gb.display.drawImage(8,0, heartVoid1);
      gb.display.drawImage(16,0, heartVoid2);
      break;
    default:
      gb.display.drawImage(0,0, heartVoid0);
      gb.display.drawImage(8,0, heartVoid1);
      gb.display.drawImage(16,0, heartVoid2);
      frameCounter++;
      if(frameCounter == 20){
        isWin = false;
        gameState = 1;
        frameCounter = 0;
      }
  }
}

int getCurrentLife(){
  return lives_remaining;
}

void setCurrentLife(int nbLifes){
   lives_remaining = nbLifes;
}

void removeLife(){
  lives_remaining--;
}

void killPlayer(){
  lives_remaining = 0;
}
   


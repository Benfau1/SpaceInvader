#include "alien_image.h"

#pragma region aliensParams
const int GRILLE_TAILLE_X = 8;
const int GRILLE_TAILLE_Y = 4;
const int ALIEN_TAILLE_X = 6;
const int ALIEN_TAILLE_Y = 7;
int aliens[GRILLE_TAILLE_X][GRILLE_TAILLE_Y];
float alienPositionsX[GRILLE_TAILLE_X][GRILLE_TAILLE_Y];
float alienPositionsY[GRILLE_TAILLE_X][GRILLE_TAILLE_Y];
float alienSpeedX = 1;
float alienSpeedY = 0;
int shootCurrentTimer = 0;
const int SHOOT_DELAY = 60;
int alienBulletPositionX;
int alienBulletPositionY;
const int alienBulletSizeX = 1;
const int alienBulletSizeY = 3;
bool isShooting;
int alienBulletSpeed = 1;
Image alienImg(ALIEN_IMAGE);
#pragma endregion

void initAliens(){
  for (int ligne = 0; ligne < GRILLE_TAILLE_Y; ligne += 1) {
    for (int colonne = 0; colonne < GRILLE_TAILLE_X; colonne += 1) {
      aliens[colonne][ligne] = 1;
      alienPositionsX[colonne][ligne] = colonne * (ALIEN_TAILLE_X + 2);
      alienPositionsY[colonne][ligne] = (ligne+1) * ALIEN_TAILLE_Y;
    }
  }
}

void drawAliens(){
  for (int ligne = 0; ligne < GRILLE_TAILLE_Y; ligne += 1) {
    for (int colonne = 0; colonne < GRILLE_TAILLE_X; colonne += 1) {
      if (aliens[colonne][ligne] == 0) {
        continue;
      }

      alienPositionsX[colonne][ligne] += alienSpeedX;
      alienPositionsY[colonne][ligne] += alienSpeedY;
      gb.display.drawImage(alienPositionsX[colonne][ligne], alienPositionsY[colonne][ligne], alienImg);
    }
  }

  if(alienPositionsX[GRILLE_TAILLE_X-1][GRILLE_TAILLE_Y-1] + ALIEN_TAILLE_X >= gb.display.width()){
    alienSpeedY = 0.2;
    alienSpeedX = -alienSpeedX;
  }
  else if(alienPositionsX[0][GRILLE_TAILLE_Y-1] <= 0){
    alienSpeedY = 0.2;
    alienSpeedX = abs(alienSpeedX);
  }
  else{
    alienSpeedY = 0;
  }

  if(shootCurrentTimer < SHOOT_DELAY){
    shootCurrentTimer++;
  }
  else{
    shootCurrentTimer = 0;
    isShooting = false;
    alienShoot();
  }

  if(isShooting){

    alienBulletPositionY += alienBulletSpeed;
    gb.display.fillRect(alienBulletPositionX, alienBulletPositionY, alienBulletSizeX, alienBulletSizeY);

    int playerPos_X = getPlayerLocationX();
    int playerPos_Y = getPlayerLocationY();
    int playerSize_X = getPlayerSizeX();
    int playerSize_Y = getPlayerSizeY();
    
    if(gb.collide.rectRect(alienBulletPositionX, alienBulletPositionY,alienBulletSizeX,alienBulletSizeY,
      playerPos_X, playerPos_Y, playerSize_X, playerSize_Y)){
        isShooting = false;
        removeLife();
    } 
  }
}

void alienShoot(){
  isShooting = true;
  alienBulletPositionX = alienPositionsX[rand()%(GRILLE_TAILLE_X-1)][GRILLE_TAILLE_Y-1];
  alienBulletPositionY = alienPositionsY[rand()%(GRILLE_TAILLE_X-1)][GRILLE_TAILLE_Y-1] + ALIEN_TAILLE_Y;

  gb.display.fillRect(alienBulletPositionX, alienBulletPositionY, alienBulletSizeX, alienBulletSizeY);
}
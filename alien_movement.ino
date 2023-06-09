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
bool isAlienShooting;
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
        alienPositionsX[colonne][ligne] += alienSpeedX;
        alienPositionsY[colonne][ligne] += alienSpeedY;
        continue;
      }

      alienPositionsX[colonne][ligne] += alienSpeedX;
      alienPositionsY[colonne][ligne] += alienSpeedY;
      gb.display.drawImage(alienPositionsX[colonne][ligne], alienPositionsY[colonne][ligne], alienImg);

      if(gb.collide.rectRect(alienPositionsX[colonne][ligne], alienPositionsY[colonne][ligne],ALIEN_TAILLE_X,ALIEN_TAILLE_Y,
      getPlayerLocationX(), getPlayerLocationY(), getPlayerSizeX(), getPlayerSizeY())){
        killPlayer();
      }
    }
  }
  checkBorderCollision();
  checkAlienShooting();
}

void checkBorderCollision(){
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
}

void initAlienShoot(){
  isAlienShooting = true;
  int lastRowAliens[GRILLE_TAILLE_X];
  int countActiveColumns = 0;
  for (int colonne = 0; colonne < GRILLE_TAILLE_X; colonne += 1) {
    for (int ligne = GRILLE_TAILLE_Y-1; ligne >= 0 ; ligne--) {
      if (aliens[colonne][ligne] == 1) {
        lastRowAliens[colonne] = ligne;
        countActiveColumns++;
        break;
      }
    }
  }

  int rdmColumn = rand()%(GRILLE_TAILLE_X-1);
  bool rowFound = false;

  for (int ligne = GRILLE_TAILLE_Y-1; ligne >= 0 ; ligne--) {
    if (aliens[rdmColumn][ligne] == 1) {
      rowFound = true;
    }
  }

  if(rowFound){
    alienBulletPositionX = alienPositionsX[rdmColumn][lastRowAliens[rdmColumn]];
    alienBulletPositionY = alienPositionsY[rdmColumn][lastRowAliens[rdmColumn]] + ALIEN_TAILLE_Y;
    
    gb.display.fillRect(alienBulletPositionX, alienBulletPositionY, alienBulletSizeX, alienBulletSizeY);
  }
  else{
    initAlienShoot();
  }
}

void checkAlienShooting(){
  if(shootCurrentTimer < SHOOT_DELAY){
    shootCurrentTimer++;
  }
  else{
    shootCurrentTimer = 0;
    isAlienShooting = false;
    initAlienShoot();
  }

  if(isAlienShooting){

    alienBulletPositionY += alienBulletSpeed;
    gb.display.fillRect(alienBulletPositionX, alienBulletPositionY, alienBulletSizeX, alienBulletSizeY);

    int playerPos_X = getPlayerLocationX();
    int playerPos_Y = getPlayerLocationY();
    int playerSize_X = getPlayerSizeX();
    int playerSize_Y = getPlayerSizeY();
    
    if(gb.collide.rectRect(alienBulletPositionX, alienBulletPositionY,alienBulletSizeX,alienBulletSizeY,
      playerPos_X, playerPos_Y, playerSize_X, playerSize_Y)){
        isAlienShooting = false;
        removeLife();
    } 
  }
}

bool checkAlienCollision(int bulletXPos,int bulletYPos,int bulletW,int bulletH){
  for (int ligne = 0; ligne < GRILLE_TAILLE_Y; ligne += 1) {
    for (int colonne = 0; colonne < GRILLE_TAILLE_X; colonne += 1) {
      if (aliens[colonne][ligne] == 0) {
        continue;
      }

      if (gb.collide.rectRect(bulletXPos,bulletYPos,bulletW,bulletH,
      alienPositionsX[colonne][ligne],alienPositionsY[colonne][ligne],ALIEN_TAILLE_X,ALIEN_TAILLE_Y)){
        countScore(ligne);
        aliens[colonne][ligne] = 0;
        return true;
      }
    }
  }
  return false;
}

bool isGameFinished(){
  for (int colonne = 0; colonne < GRILLE_TAILLE_X; colonne += 1) {
    for (int ligne = GRILLE_TAILLE_Y-1; ligne >= 0 ; ligne--) {
      if (aliens[colonne][ligne] == 1) {
        return false;
      }
    }
  }
  endGame();
  return true;
}

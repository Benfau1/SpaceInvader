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
}
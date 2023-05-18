#include <Gamebuino-Meta.h>

#pragma region params

//Player params
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
#pragma endregion

#pragma endregion
const uint16_t ALIEN_IMAGE[] = {

    // metadata

    6,      // frame width
    6,      // frame height
    2,      // frames
    10,      // frame loop
    0xf81f, // transparent color
    0,      // 16-bits color mode

    // colormap

    // frame 1/2
    0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0xf81f,
    0x2589, 0x2589, 0xf81f, 0xf81f, 0x2589, 0x2589,
    0xf81f, 0x4783, 0x4783, 0x4783, 0x4783, 0xf81f,
    0x4783, 0xf81f, 0x4783, 0x4783, 0xf81f, 0x4783,
    0x4783, 0x4783, 0x4783, 0x4783, 0x4783, 0x4783,
    0xf81f, 0x4783, 0x4783, 0x4783, 0x4783, 0xf81f,

    // frame 2/2
    0x2589, 0xf81f, 0xf81f, 0xf81f, 0xf81f, 0x2589,
    0xf81f, 0x2589, 0xf81f, 0xf81f, 0x2589, 0xf81f,
    0xf81f, 0x4783, 0x4783, 0x4783, 0x4783, 0xf81f,
    0x4783, 0xf81f, 0x4783, 0x4783, 0xf81f, 0x4783,
    0x4783, 0x4783, 0x4783, 0x4783, 0x4783, 0x4783,
    0xf81f, 0x4783, 0xf81f, 0xf81f, 0x4783, 0xf81f

};
Image alienImg(ALIEN_IMAGE);
void setup() {
  startGame();
  gb.begin();
}

void loop() {
  while (!gb.update());
  gb.display.clear();
  renderer();
}

#pragma region spaceInvaders
void startGame() {
   for (int ligne = 0; ligne < GRILLE_TAILLE_Y; ligne += 1) {
    for (int colonne = 0; colonne < GRILLE_TAILLE_X; colonne += 1) {
      aliens[colonne][ligne] = 1;
      alienPositionsX[colonne][ligne] = colonne * (ALIEN_TAILLE_X + 2);
      alienPositionsY[colonne][ligne] = ligne * ALIEN_TAILLE_Y;
    }
  }
}

/*void checkAlienCollider(){
  for (int ligne = GRILLE_TAILLE_Y; ligne >= 0; ligne--) {
    for (int colonne = 0; colonne < GRILLE_TAILLE_X; colonne += 1) {
      int alienX = colonne * (ALIEN_TAILLE + 2) + 1;
      int alienY = ligne * (ALIEN_TAILLE + 2) + 1;

      if (aliens[ligne][colonne] == 0) {
        continue;
      }
      //Collision
      else if(){
        aliens[ligne][colonne] = 0;
        break;
      }
    }
  }
}*/

void renderer(){
  //Aliens
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
#pragma endregion
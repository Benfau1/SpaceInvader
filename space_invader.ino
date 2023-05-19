#include <Gamebuino-Meta.h>

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
  initBackground();
  initAliens();
}

void renderer(){
  drawBackground();
  drawHealthLevel();
  drawAliens();
  if(getCurrentLife() > 0){
    drawShuttle();
  }
}
#pragma endregion
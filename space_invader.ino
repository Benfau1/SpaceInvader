#include <Gamebuino-Meta.h>

#pragma region params

//Player params


#pragma endregion
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
  initAliens();
}

void renderer(){
  drawShuttle();
  drawAliens();
  drawHealthLevel();
}
#pragma endregion
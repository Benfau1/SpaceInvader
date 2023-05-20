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

void startGame() {
  initBackground();
  initAliens();
}

void renderer(){
  drawBackground();
  drawHealthLevel();
  if(!isGameFinished()){
    drawAliens();
  }
  if(getCurrentLife() > 0){
    drawShuttle();
  }
}
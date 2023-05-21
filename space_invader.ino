#include <Gamebuino-Meta.h>

bool isGameEnded;
int score;
bool isWin;

void setup() {
  initGame();
  gb.begin();
}

void initGame() {
  setCurrentLife(3);
  isGameEnded = false;
  score = 0;
  isWin = false;
  initBackground();
  initAliens();
}

void loop() {
  while (!gb.update());
  gb.display.clear();
  isGameEnded ? endGameRenderer() : renderer();
}

void renderer(){
  drawBackground();
  drawHealthLevel();
  displayScore();
  if(!isGameFinished()){
    drawAliens();
  }
  if(getCurrentLife() > 0){
    drawShuttle();
  }
}

void endGameRenderer(){
  gb.display.setCursorY(20);
  gb.display.setCursorX(0);
  isWin ? gb.display.printf("You have won") : gb.display.printf("You have lost");
  
  gb.display.setCursorY(28);
  gb.display.setCursorX(0);
  isWin ? gb.display.printf("your score is maximum : %d" , score) : gb.display.printf("your score is : %d" , score);
  
  gb.display.setCursorY(40);
  gb.display.setCursorX(0);
  gb.display.printf("Press A to replay");
  if (gb.buttons.pressed(BUTTON_A)){
    initGame();
  }
}

int getScore(){
  return score;
}

void addScore(int number){
  score += number;
}

void endGame(){
  if(getCurrentLife() > 0){
    isWin = true;
  }
  isGameEnded = true;
}
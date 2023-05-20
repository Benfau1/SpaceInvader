#include <Gamebuino-Meta.h>

int gameState = 0;
//Player won ?
bool isWin = true;
//Score counter
int score = 0;
void setup() {
  startGame();
  gb.begin();
}

void loop() {
  while (!gb.update());
  gb.display.clear();
  switch(gameState){
    case 0:
      renderer();
      break;
    default:
      gb.display.setCursorY(20);
      gb.display.setCursorX(0);
      isWin ? gb.display.printf("You have won") : gb.display.printf("You have lost");
      
      gb.display.setCursorY(28);
      gb.display.setCursorX(0);
      isWin ? gb.display.printf("your score is maximum : %d" , score) : gb.display.printf("your score is : %d" , score);
      
      gb.display.setCursorY(40);
      gb.display.setCursorX(0);
      gb.display.printf("Press A to replay");
      if ( gb.buttons.pressed(BUTTON_A)){
        //Reinitialize game
        startGame();
      }
  }
}

void startGame() {
  setCurrentLife(3);
  gameState = 0;
  score = 0;
  initBackground();
  initAliens();
}

void renderer(){
  drawBackground();
  drawHealthLevel();
  displayScore();
  drawAliens();
  if(getCurrentLife() > 0){
    drawShuttle();
  }
}

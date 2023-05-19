const int STARS_MAX_SPEED = 4;
const int STARS_MIN_SPEED = 2;
const int MAX_STARS_ON_SCREEN = 10;

int stars[MAX_STARS_ON_SCREEN];
int starsPositionX[MAX_STARS_ON_SCREEN];
int starsPositionY[MAX_STARS_ON_SCREEN];
int starsSpeed[MAX_STARS_ON_SCREEN];

void initBackground(){
    for (int i = 0; i < MAX_STARS_ON_SCREEN; i++)
    {
        stars[i] = 0;
        starsPositionX[i] = 0;
        starsPositionY[i] = 0;
        starsSpeed[i] = 0;
    }
}

void drawBackground(){
    for (int i = 0; i < MAX_STARS_ON_SCREEN; i++)
    {
        if(stars[i] == 0){
            addStar(i);
            continue;;
        }

        starsPositionX[i] -= starsSpeed[i];

        if(starsPositionX[i] <= 0){
            stars[i] = 0;
        }
        else{
            gb.display.fillRect(starsPositionX[i], starsPositionY[i], 1, 1);
        }
    }
}

void addStar(int index){
    stars[index] = 1;
    starsPositionX[index] = gb.display.width();
    starsPositionY[index] = rand()%(gb.display.height());
    starsSpeed[index] = (rand() % (STARS_MAX_SPEED - STARS_MIN_SPEED + 1)) + STARS_MIN_SPEED;
}
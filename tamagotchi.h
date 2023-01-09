#ifndef TAMAGOTCHI
#define TAMAGOTCHI 

typedef struct {
	int hours;
	int minutes;
	int seconds;
	int hunger;
	int happiness;
	int status;				// 0 idle, 1 eating
	int over;					// 0 not over, 1 over
	int countTo5Snack;
	int countTo5Meal;
} PET_STATS;

extern PET_STATS stats;

void drawPet(int offsetX, int offsetY);
void drawPetFlipped(int offsetX, int offsetY);
void drawWumpa(int offsetX, int offsetY);				
void drawAkuAku(int offsetX, int offsetY);
void drawUkaUka(void);
void drawInterface(void);
void printAge(PET_STATS *stats);
void gameOver(void);
void decreaseStat(PET_STATS *stats, int stat);
void animatePet(int state);
void textHighlight(int flag);
void eatingAnimation(int flag);
void increaseStat(PET_STATS *stats, int stat);
void resetGame(PET_STATS *stats);



#endif

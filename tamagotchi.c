#include "tamagotchi.h"
#include <stdio.h>
#include "stuff\CrashBandicoot.c"
#include "stuff\CrashBandicoot-Flipped.c"
#include "stuff\akuaku.c"
#include "stuff\wumpa.c"
#include "stuff/ukaukafinal.c"
#include "crashIdleTEST.c"
#include "LPC17xx.h"
#include "GLCD_Advanced/GLCD.h"
#include "timer/timer.h"
#include "RIT/RIT.h"


extern PET_STATS stats;

extern void drawPet(int offsetX, int offsetY){
	int width,height=0;
	for(height=0; height < Pet.height; height++){
		for(width=0; width < Pet.width; width++){
			if(stats.over==0){
				int index=(height*Pet.width)+width;
				LCD_SetPoint(width+offsetX,height+offsetY, Pet.pixel_data[index]);
			}
		}
	}
}
extern void drawPetFlipped(int offsetX, int offsetY){
	int width,height=0;
	for(height=0; height < PetFlipped.height; height++){
		for(width=0; width < PetFlipped.width; width++){
			if(stats.over==0){
				int index=(height*PetFlipped.width)+width;
				LCD_SetPoint(width+offsetX,height+offsetY, PetFlipped.pixel_data[index]);
			}
		}
	}
}
extern void drawWumpa(int offsetX, int offsetY){			
		int width,height=0;
		for(height=0; height < Wumpa.height; height++){
			for(width=0; width < Wumpa.width; width++){
				int index=(height*Wumpa.width)+width;
				LCD_SetPoint(width+offsetX,height+offsetY, Wumpa.pixel_data[index]);
			}
		}
	
}
extern void drawAkuAku(int offsetX, int offsetY){
		int width,height=0;
		for(height=0; height < AkuAku.height; height++){
			for(width=0; width < AkuAku.width; width++){
				int index=(height*AkuAku.width)+width;
				LCD_SetPoint(width+offsetX,height+offsetY, AkuAku.pixel_data[index]);
			}
		}
}

extern void drawInterface(){
	GUI_Text(65, 0, (uint8_t *) "Age: 00:00:00", Black, White);
	drawWumpa(16, 30);
	drawWumpa(46, 30);
	drawWumpa(76, 30);
	drawAkuAku(136, 30);
	drawAkuAku(166, 30);
	drawAkuAku(196, 30);
	GUI_Text(72,270,(uint8_t*) "Snack", Black, White);
	GUI_Text(132,270,(uint8_t*) "Meal", Black, White);
}
extern void drawUkaUka(){
	int width,height=0;
	for(height=0; height < UkaUka.height; height++){
		for(width=0; width < UkaUka.width; width++){
			int index=(height*UkaUka.width)+width;
			LCD_SetPoint(width+64,height+75, UkaUka.pixel_data[index]);
		}
	}
}
extern void printAge(PET_STATS *stats){
	char time[32];
	sprintf(time, "Age: %02d:%02d:%02d", stats->hours, stats->minutes, stats->seconds);
	GUI_Text(65, 0, (uint8_t *) time, Black, White);
}

extern void GameOver(){
	LCD_DrawRectangle(0,20,240,300, White);
	drawUkaUka();
	stats.over=1;
	disable_timer(1);
	disable_timer(0);
	LCD_DrawRectangle(72, 270,90,20, White);
	GUI_Text(85, 270, (uint8_t*) "Game Over.", Black, White);
	GUI_Text(82, 285, (uint8_t*) "Try Again?", Red, White);
	
}
extern void decreaseStat(PET_STATS *stats, int stat){
	
	if(stat==0){
		if(stats->happiness == 3){
			stats->happiness--;
			LCD_DrawRectangle(196,30,26,32,White);
		}
		else if(stats->happiness==2){
			stats->happiness--;
			LCD_DrawRectangle(166,30,26,32,White);
		}
		else if(stats->happiness==1){
			stats->happiness--;
			LCD_DrawRectangle(136,30,26,32,White);
			GameOver();
		}
	}
	else if (stat == 1){
		if(stats->hunger == 3){
		stats->hunger--;
		LCD_DrawRectangle(76,30,26,32,White);
		}
		else if(stats->hunger==2){
			stats->hunger--;
			LCD_DrawRectangle(46,30,26,32,White);
		}
		else if(stats->hunger==1){
			stats->hunger--;
			LCD_DrawRectangle(16,30,26,32,White);
			GameOver();
		}
	}
}
extern void animatePet(int idle){
	
	if(idle ==0){
		int width,height=0;
		for(height=0; height < PetIdle.height; height++){
			for(width=0; width < PetIdle.width; width++){
				if(stats.over==0){
					int index=(height*PetIdle.width)+width;
					LCD_SetPoint(width+97,height+119, PetIdle.pixel_data[index]);
				}
			}
		}
	}
	else if (idle == 1){
		int width,height=0;
		for(height=0; height < PetIdle.height; height++){
			for(width=0; width < Pet.width; width++){
				if(stats.over==0){
					int index=(height*Pet.width)+width;
					LCD_SetPoint(width+97,height+119, Pet.pixel_data[index]);
				}
			}
		}
	}
}

extern void textHighlight(int flag){
	if (flag == 0){
		GUI_Text(132, 270, (uint8_t*) "Meal", Black, White);
		GUI_Text(72, 270, (uint8_t*) "Snack", Red, White);
	}
	else if (flag == 1){
		GUI_Text(72, 270, (uint8_t*) "Snack", Black, White);
		GUI_Text(132, 270, (uint8_t*) "Meal", Red, White);
	}
}

extern void eatingAnimation(int flag){
	int i;
	if(flag == 0){
		stats.status=1;
		/*drawWumpa(20,130);
		for(i = 97; i >50; i-=2){
			if(stats.over==0){
				LCD_DrawRectangle(i+46,119,2,82, White);
				drawPet(i, 119);
			}
		}
		LCD_DrawRectangle(20,130,26,32, White);
		for(i = 51; i <97; i+=2){
			if(stats.over==0){
				drawPetFlipped(i, 119);
				LCD_DrawRectangle(i,119,2,82, White);
			}
		}
		drawPet(97,119);*/
		stats.status=0;
	}
	else if (flag == 1){
		stats.status=1;
		/*drawAkuAku(190,130);
		drawPetFlipped(97, 119);
		for(i = 99; i <140; i+=2){
			if(stats.over==0){
				LCD_DrawRectangle(i-2,119,2,82, White);
				drawPetFlipped(i, 119);
			}
		}			
		LCD_DrawRectangle(190,130,30,32, White);
		for(i = 140; i >=97; i-=2){
			if(stats.over==0){
				LCD_DrawRectangle(i+46,119,2,82, White);
				drawPet(i, 119);
			}
		}*/
		stats.status=0;
	}
}
extern void increaseStat(PET_STATS *stats, int stat){
	disable_RIT();
	if (stat == 0){
		eatingAnimation(stat);
		if(stats->hunger == 1){
			stats->hunger++;
			drawWumpa(46,30);
		}
		else if(stats->hunger == 2){
			stats->hunger++;
			drawWumpa(76,30);
		}
	}
	else if (stat == 1){
		eatingAnimation(stat);
		if(stats->happiness == 1){
			stats->happiness++;
			drawAkuAku(166,30);
		}
		else if(stats->happiness == 2){
			stats->happiness++;
			drawAkuAku(196,30);
		}
	}
	enable_RIT();
}

extern void resetGame(PET_STATS *stats){
	stats->happiness=3;
	stats->hunger=3;
	stats->countTo5Meal=0;
	stats->countTo5Snack=0;
	stats->status=0;
	stats->hours=0;
	stats->minutes=0;
	stats->seconds=0;
	stats->over=0;
	LCD_DrawRectangle(64,75, 112,170, White);
	drawPet(97, 119);
	LCD_DrawRectangle(80, 270, 90, 30, White);
	drawInterface();
	reset_timer(0);
	reset_timer(1);
	enable_timer(0);
	enable_timer(1);
}

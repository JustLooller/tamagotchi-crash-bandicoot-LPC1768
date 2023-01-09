/****************************************Copyright (c)****************************************************
**
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD_Advanced/GLCD.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "Joystick/joystick.h"
#include "tamagotchi.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

PET_STATS stats = {0, 0, 0, 3, 3, 0, 0, 0, 0};
int main(void)
{

	SystemInit(); /* System Initialization (i.e., PLL)  */
	LCD_Initialization();
	drawPet(97, 119);
	drawInterface();

	joystick_init();
	init_timer(0, 0x17D7840); // 1s
	init_timer(1, 0xBEBC20);  //.5s
	init_RIT(0x1312D0);		  // 50ms
	enable_timer(0);
	enable_timer(1);
	enable_RIT();

	LPC_SC->PCON |= 0x1; /* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);

	while (1)
	{
		__ASM("wfi");
	}
}

/*********************************************************************************************************
	  END FILE
*********************************************************************************************************/

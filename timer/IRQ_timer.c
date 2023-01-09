/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD_Advanced/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../tamagotchi.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/



void TIMER0_IRQHandler (void){
	
	static int hungerFlag=1;
	static int happinessFlag=0;
  if(stats.seconds <59){
		stats.seconds++;
		printAge(&stats);
	}
	else if(stats.seconds >= 59 && stats.minutes <59){
		stats.seconds=0;
		stats.minutes++;
		printAge(&stats);
	}
	else if (stats.minutes >= 59){
		stats.seconds=0;
		stats.minutes=0;
		stats.hours++;
		printAge(&stats);
	}
	stats.countTo5Snack++;
	stats.countTo5Meal++;
	if(stats.countTo5Snack == 5){
		decreaseStat(&stats, hungerFlag);			//decrease hunger by 1 (Wumpa fruit)
		stats.countTo5Snack=0;
	}
	if(stats.countTo5Meal == 5){
		decreaseStat(&stats, happinessFlag);	//decrease happiness by 1 (Aku Aku mask)
		stats.countTo5Meal=0;
	}
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	static int idle=0;			/* il primo frame è mostrato a schermo */
	animatePet(idle);
	if (idle == 0){
		idle++;
	}
	else idle--;
	
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

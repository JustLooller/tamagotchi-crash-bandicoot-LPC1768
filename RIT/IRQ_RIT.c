/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../tamagotchi.h"


/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void textHighlight(int flag);

void RIT_IRQHandler (void)
{					
	static int right=0;			// Pin 28
	static int left=0;			// Pin 27
	static int select=0;		// Pin 25
	static int last_pressed=0;		//1 left, 2 right
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		select++;
		switch(select){
			case 1:
				if(stats.over == 1){
					last_pressed=0;
					resetGame(&stats);
				}
				if(last_pressed==1 && stats.over==0){
					disable_RIT();
					increaseStat(&stats, 0);
					enable_RIT();
					stats.countTo5Snack=0;
				}
				else if(last_pressed==2 && stats.over==0){
					increaseStat(&stats, 1);
					stats.countTo5Meal=0;
				}
				reset_RIT();
			default:
				break;
		}
	}
	else{
		select=0;
	}
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){				// Left pressed
		left++;
		switch(left){
			case 1:
				last_pressed=1;
				textHighlight(0);
				reset_RIT();
				break;
			default:
				break;
		}
	}
	else{
		left=0;
	}
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){				// Right pressed
		right++;
		switch(right){
			case 1:
				last_pressed=2;
				textHighlight(1);
				reset_RIT();
				break;
			default:
				break;
		}
	}
	else{
		right=0;
	}
	reset_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

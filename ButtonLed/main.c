#include "TM4C123.h"                    // Device header

#define GPIOF_CLK 1<<5
#define UNLOCK_GPIOF 1<<0
#define BIT1 1<<1
#define BIT4 1<<4     

int main(void)
{	
	
   SYSCTL->RCGCGPIO |= GPIOF_CLK;   
   GPIOF->LOCK = 0x4C4F434B;

	 GPIOF->CR |= UNLOCK_GPIOF;						  // Activate internal pull up and pull down resistor for GPIOF
	 
   GPIOF->DIR |= BIT1 |~(BIT4);           //set PF1 as an output and PF4 as an input pin
	 GPIOF->PUR |= BIT4;        						// Enable Pull Up resistor PF4
   GPIOF->DEN |= BIT1|BIT4 ;         		  // Enable PF1 and PF4 as a digital GPIO pins 

    while(1)
    {   
			if(GPIOF->DATA & BIT4){
				GPIOF->DATA &= ~(BIT1);
			}
			else{
				GPIOF->DATA |= BIT1;
			}		
    }
}
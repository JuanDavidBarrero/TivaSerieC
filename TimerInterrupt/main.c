#include "TM4C123.h"   // Device header file for Tiva Series Microcontroller

#define GPIOF_CLK (1<<5)
#define BIT2 (1<<2)   
#define BIT1 (1<<1)
#define BIT3 (1<<3)

#define TIMER1CLK (1<<1)


int main(void)
{
	
	 int i;	
   SYSCTL->RCGCGPIO |= GPIOF_CLK; 
   GPIOF->DIR       |= BIT2 | BIT1 |BIT3; 
   GPIOF->DEN       |= BIT2 | BIT1 |BIT3;  
	
   SYSCTL->RCGCTIMER |= TIMER1CLK; 		 									/*enable clock Timer1 subtimer A in run mode */
	
	SYSCTL->RCGCTIMER |= (1<<1);  												/*enable clock Timer1 subtimer A in run mode */
	TIMER1->CTL = 0; 																			/* disable timer1 output */
	TIMER1->CFG = 0x4; 																		/*select 16-bit configuration option */
	TIMER1->TAMR = 0x2; 																	/*select periodic down counter mode of timer1 */
	TIMER1->TAPR = 250-1; 																/* TimerA prescaler value */
	TIMER1->TAILR = 64000-1 ;														  /* TimerA counter starting count down value  */
	TIMER1->ICR = 0x1;         													  /* TimerA timeout flag bit clears*/
	TIMER1->IMR |=(1<<0);														      /*enables TimerA time-out  interrupt mask */
	TIMER1->CTL |= 0x01;        												 /* Enable TimerA module */
	NVIC->ISER[0] |= (1<<21); 														/*enable IRQ21 */
	
	SYSCTL->RCGCTIMER |= (1<<2);  
	TIMER2->CTL = 0; 
	TIMER2->CFG = 0x4; 
	TIMER2->TAMR = 0x02; 
	TIMER2->TAPR = 250; 
	TIMER2->TAILR = 32000 ; 
	TIMER2->ICR = 0x1;          
	TIMER2->IMR |=(1<<0); 
	TIMER2->CTL |= 0x01;        
	NVIC->ISER[0] |= (1<<23); 			

	
	
	while(1)
	{
		GPIOF->DATA  ^= BIT3;
		for(i = 0; i<900000; i++){}
	}
}

TIMER1A_Handler()
{
		if(TIMER1->MIS & 1<<0)
			GPIOF->DATA  ^= BIT2; 								 /* toggle Blue LED*/
		TIMER1->ICR = 1<<0;          					/* Timer1A timeout flag bit clears*/
		
		

}

TIMER2A_Handler()
{
	if(TIMER2->MIS & 1<<0)
			GPIOF->DATA  ^= BIT1; 
		TIMER2->ICR = 1<<0;          
}

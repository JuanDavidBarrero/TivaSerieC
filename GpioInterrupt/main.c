#include "TM4C123.h"                    // Device header

#define GPIOFCLK 1<<5
#define BTN0 1<<4
#define BTN1 1<<0
#define GRENLED 1<<3
#define REDLED 1<<1

void delay(void);

int main(void)
{
    
	  SYSCTL->RCGCGPIO |= GPIOFCLK;   
    
    GPIOF->LOCK = 0x4C4F434B;   /* unlock commit register */
    GPIOF->CR = 0x01;           /* make PORTF0 configurable */
    GPIOF->LOCK = 0;            /* lock commit register */

	
    GPIOF->DIR &= ~(BTN0)|~(BTN1);  
    GPIOF->DIR |= GRENLED|REDLED;           
    GPIOF->DEN |= (REDLED)|(GRENLED)|(BTN0)|(BTN1);             
    GPIOF->PUR |= (BTN0)|(BTN1);           


 
    
    /* configure PORTF4, 0 for falling edge trigger interrupt */
	
		__disable_irq();
    GPIOF->IS  &= ~(BTN0)|~(BTN1);        /* make bit 4, 0 edge sensitive */
    GPIOF->IBE &= ~(BTN0)|~(BTN1);        /* trigger is controlled by IEV */
    GPIOF->IEV &= ~(BTN0)|~(BTN1);        /* falling edge trigger */
    GPIOF->ICR |= ~(BTN0)|~(BTN1);        /* clear any prior interrupt */
    GPIOF->IM  |= ~(BTN0)|~(BTN1);        /* unmask interrupt */
    
    /* enable interrupt in NVIC and set priority to 3 */
    NVIC->IP[30] = 3 << 5;     						/* set interrupt priority to 3 */
    NVIC->ISER[0] |= 0x40000000;  				/* enable IRQ30 (D30 of ISER[0]) */
		__enable_irq();

  while(1)
    {
			GPIOF->DATA |= REDLED;
			delay();
			GPIOF->DATA &= ~(REDLED);
			delay();
    } 
    
  
}

void delay(void){
	int i;
	for(i=0; i<1500000; i++){}
}


void GPIOF_Handler(void)
{	
	volatile int readback;
	
		if (GPIOF->MIS & BTN0) 								/* check if interrupt causes by PF4/SW1*/
     {   
      GPIOF->DATA |= GRENLED;
      GPIOF->ICR |= BTN0;							  /* clear the interrupt flag */
     } 
   else if (GPIOF->MIS & BTN1) 					/* check if interrupt causes by PF0/SW2 */
    {   
     GPIOF->DATA &= ~(GRENLED);
     GPIOF->ICR |= BTN1;							  /* clear the interrupt flag */
    }
		else
		{
		GPIOF->ICR = GPIOF->MIS;
		readback = GPIOF->ICR;      		   	/* Come back to whiel thread*/
		}
		
}
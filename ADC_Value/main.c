#include "TM4C123.h"                    // Device header

#define GPIOD_CLK 1<<3
#define GPIOF_CLK 1<<5
#define ADC0_CLK	1<<0


#define BIT2 			1<<2
#define SS3_BIT 	1<<3
#define START_SS3 1<<3
#define CH5				5	


int main(void)
{
     unsigned int adc_value;
	
    
    SYSCTL->RCGCGPIO |= GPIOD_CLK | GPIOF_CLK ;   	/* Enable Clock to GPIOD and GPIOF */
    SYSCTL->RCGCADC |= ADC0_CLK;    							/* AD0 clock enable*/
    
	
		GPIOF->DIR       |= BIT2; 										
		GPIOF->DEN       |= BIT2;  									
   
    GPIOD->AFSEL |=   BIT2;       								/* enable alternate function */
    GPIOD->DEN   &= 	~(BIT2);      							/* disable digital function */
    GPIOD->AMSEL |=   BIT2;       								/* enable analog function */
		GPIOD->DIR   &=   ~(BIT2);     
   
    /* initialize sample sequencer3 */
    ADC0->ACTSS  &= ~(SS3_BIT);        						/* disable SS3 during configuration */
    ADC0->EMUX   &= ~(0xF<<12);    		 						/* software trigger conversion */
    ADC0->SSMUX3 |=  CH5;        			 						/* get input from channel 0 */
    ADC0->SSCTL3 |= (1<<1)|(1<<2);       		  		/* take one sample at a time, set flag at 1st sample */
    ADC0->ACTSS  |= (SS3_BIT);         						/* enable ADC0 sequencer 3 */
    /* End of sample sequencer3 */
	
	  	 
    while(1)
    {
       ADC0->PSSI |= START_SS3;      		   				/* Enable SS3 conversion or start sampling data from AN0 */
       while((ADC0->RIS & (1<<3)) == 0) ;  		 	/* Wait untill sample conversion completed*/
       adc_value = ADC0->SSFIFO3;					 				/* read adc coversion result from SS3 FIFO*/
       ADC0->ISC = (1<<3);        						   	/* clear coversion clear flag bit*/
			
			if(adc_value >= 2048)
					GPIOF->DATA  |= BIT2; 
			else if(adc_value < 1024)
				GPIOF->DATA  &= ~(BIT2);
			
			 
    }
}
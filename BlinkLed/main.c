#include "TM4C123.h"


#define GPIOFCLK 1<<5
#define BIT1 1<<1
#define BIT2 1<<2
#define BIT3 1<<3

void delay(void);

int main() {

	SYSCTL->RCGCGPIO |= GPIOFCLK;
	GPIOF->DIR |= BIT1 | BIT2 | BIT3;
	GPIOF->DEN |= BIT1 | BIT2 | BIT3;
	
	
	
while(1) {
	GPIOF->DATA |= BIT1;
	delay();
	GPIOF->DATA &= ~(BIT1);
	delay();
	
	GPIOF->DATA |= BIT2;
	delay();
	GPIOF->DATA &= ~(BIT2);
	delay();
	
	GPIOF->DATA |= BIT3;
	delay();
	GPIOF->DATA &= ~(BIT3);
	delay();
}


}


void delay(void){
	int i;
	for(i=0; i<1000000; i++){}
}


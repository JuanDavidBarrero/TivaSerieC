#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/tm4c123gh6pm.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"

int status;


int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);



    while (true)
    {

        status = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1);

        if (status == GPIO_PIN_1)
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,  GPIO_PIN_4);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,  GPIO_PIN_1);
                    }
        else
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 , 0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 , 0);

        }
    }
}

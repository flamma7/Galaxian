#include "msp.h"
#include "Drivers/Headers/blink.h"

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    blinkRate(LED1, RED, 1000);
//    blinkPushLED1(BUTTON_S1);
    blinkLED
    while(1)
    {
        ;
    }

}

#include "msp.h"
#include "Drivers/Headers/blink.h"

/**
 * main.c
 *
 * Author: luke
 */

#include "Unit_Test/Headers/blink_test.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    while(1)
    {
        ;
    }

}

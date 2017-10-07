#include "msp.h"
#include "Drivers/Headers/blink.h"

/**
 * main.c
 *
 * Author: luke
 */

//#include "Unit_Test/Headers/blink_test.h"
#include "Unit_Test/Headers/uart_test.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	__enable_interrupt();
	Blink_Tester();
//	Uart_Tester();

    while(1)
    {
        ;
    }

}

// that the powerful play goes on and that you may contribute a verse, what will
// your verse be

// most men live lives of quiet desperation
// dare to strike out and find new grounds

// TODO moving Corgi butt after win

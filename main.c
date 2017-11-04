#include "msp.h"
#include "Drivers/Headers/blink.h"

/**
 * main.c
 *
 * Author: luke
 */

#include "Drivers/Headers/uart.h"
#include "Unit_Test/Headers/blink_test.h"
#include "Unit_Test/Headers/buzzer_test.h"
#include "Unit_Test/Headers/uart_test.h"
#include "Unit_Test/Headers/fifo_test.h"
#include "Unit_Test/Headers/joystick_test.h"


void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	__enable_interrupt();
	config_uart();
//	Blink_Tester();
//	Uart_Tester();
//	Test_Buzzer();
//	Test_Fifo();
	Joystick_Tester();

    while(1)
    {
        ;
    }

}

// that the powerful play goes on and you may contribute a verse
// What will your verse be

// most men live lives of quiet desperation
// dare to strike out and find new grounds

// TODO moving Corgi butt after win

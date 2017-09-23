/*
 * uart_test.c
 *
 *  Created on: Sep 22, 2017
 *      Author: luke
 */

#include "Headers/uart_test.h"
#include "../Drivers/Headers/uart.h"

void Uart_Tester()
{
    config_uart();
    test_simple_transmit();
//    transmit_str("Sip that tea");
}

void test_simple_transmit()
{
    while(1)
    {
        transmit_char('A');
    }
}

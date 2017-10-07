/*
 * uart_test.c
 *
 *  Created on: Sep 22, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/uart_test.h"
#include "../Drivers/Headers/uart.h"
#include "../Drivers/Headers/timerA.h"
#include <stdint.h>

void Uart_Tester()
{
//    config_uart();
//    test_simple_transmit();
//    transmit_str("Sip that tea");
//    transmit_num32((uint32_t)0x34f26734);
//    transmit_num32((uint32_t)0x12345678);
    read_debounce();
}

uint8_t global_debounce = 0;

uint8_t uart_debounce_callback()
{
    global_debounce = 0;
    return 0;
}

/* Reads the high to low transitions of the debounces */
void read_debounce()
{
    TIMER_A timer = setTimerA(ONE_S, &uart_debounce_callback);
    P5DIR &= ~BIT1;
//    P5IE |= BIT1;
//    P5IFG &= ~BIT1;
//    P5IES |= BIT1;                  // LOW TO HIGH flag intrpt
    P5REN |= BIT1;                  // enables pullup/pulldown
    P5OUT |= BIT1;                  // PULL UP
    while(1)
    {
        global_debounce = 1;
        startTimerA(timer);

        while(global_debounce);

        if(P5IN & BIT1)
        {
            transmit_char('H');
        }
        else
            transmit_char('L');
    }
}

void test_simple_transmit()
{
    while(1)
    {
        transmit_char('A');
    }
}

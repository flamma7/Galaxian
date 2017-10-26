/*
 * buzzer.c
 *
 *  Created on: Oct 25, 2017
 *      Author: luke
 */

#include "Headers/buzzer.h"
#include "Headers/uart.h"
#include "msp.h"
#include <stdint.h>

//void config_buzzer(BUZZER_LEVEL lvl)
//{
//    // buzz for 30ms therefore low be 1/3
//    // med will be 2/3
//    // high will be 3/3
//}

// p2.7

/* Starts the buzzer */
void start_buzz()
{
    transmit_str("Buzzing");
    P2DIR |= BIT7;

    uint64_t i;
    while(1)
    {
        P2OUT |= BIT7;
        for(i=0; i < 500; i++);
        P2OUT &= ~BIT7;
        for(i=0; i < 500; i++);
    }


    /* Check if a timer's been set up
     * If no: get a timerA
     * Turn on buzzer
     * turn on the timer A with time of one_ms
     */

}

//uint8_t buzzer_callback()
//{
//    // check if count == BUZZER_TIME
//    // count = 0
//    //  if true turn off the buzzer and return zero
//
//    // otherwise
//    // otherwise toggle the buzzer with mod3 == buzzer_level
//    // add one to the count
//    // return 1
//}

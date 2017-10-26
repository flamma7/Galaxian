/*
 * buzzer.c
 *
 *  Created on: Oct 25, 2017
 *      Author: luke
 */

#include "Headers/timerA.h"
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
    uint8_t timer = setTimerA(ONE_MS, &buzzer_callback);
    transmit_str("Buzzing");
    P2DIR |= BIT7;
    startTimerA(timer);


    /* Check if a timer's been set up
     * If no: get a timerA
     * Turn on buzzer
     * turn on the timer A with time of one_ms
     */

}

uint8_t buzzer_callback()
{

    P2OUT ^= BIT7;
    return 1;

    // check if count == BUZZER_TIME
    // count = 0
    //  if true turn off the buzzer and return zero

    // otherwise
    // otherwise toggle the buzzer with mod3 == buzzer_level
    // add one to the count
    // return 1
}

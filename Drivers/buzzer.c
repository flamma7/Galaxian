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

void config_buzzer(BUZZER_SEL sel)
{
    switch(sel)
    {
    case BUZZER_ALARM:
        transmit_str("Buzzer Alarm selected.");
        buzzer_timer = setTimerA(TEN_MS, &buzzer_callback);
        buzzer_count = ALARM_TIME_COUNT;
        break;
    default: // BUZZER_BEEP
        transmit_str("Buzzer Beep selected.");
        buzzer_timer = setTimerA(ONE_MS, &buzzer_callback);
        buzzer_count = BEEP_TIME_COUNT;
        break;
    }
}

// p2.7

/* Starts the buzzer */
void buzz()
{
    if(buzzer_count == 0)
    {
        transmit_str("buzzer not configured.");
        return;
    }
    transmit_str("Buzzing");
    P2DIR |= BIT7;
    P2OUT |= BIT7;
    startTimerA((TIMER_A)buzzer_timer);
}

uint8_t buzzer_callback()
{
    if(--buzzer_count == 0)
    {
        P2OUT &= ~BIT7;
        return 0;
    }
    P2OUT ^= BIT7;
    return 1;
}

/*
 * blink.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 *      MSP's LED Driver File
 *      See Header File for function descriptions
 */


#include "msp.h"
#include "Headers/blink.h"
#include "Headers/button.h"
#include "Headers/timerA.h"

void blinkRateLED1(TIMER_A_TIME time)
{
    configLED(LED1);
    P1OUT |= BIT0;              // led on
    blinkRateTimerA = setTimerA(time, &toggleRateLED1);
    startTimerA( (TIMER_A) blinkRateTimerA);
}

void blinkPushLED1(BUTTON but)
{
    configLED(LED1);
    P1OUT |= BIT0;              // led on
    configButton(but, &toggleLED1);
}


void configLED(LED led)
{
    switch(led)
    {
    case LED1:
        P1DIR |= BIT0;          // set as output
        P1OUT &= ~BIT0;         // set 1.0 low
        break;
    case LED2:
        P2DIR |= BIT0;
        P2DIR |= BIT1;
        P2DIR |= BIT2;
        P2OUT &= ~BIT0;         // set 2.0 low
        P2OUT &= ~BIT1;         // set 2.1 low
        P2OUT &= ~BIT2;         // set 2.2 low
        break;
    case LED1_LED2:
        P1DIR |= BIT0;
        P1OUT &= ~BIT0;
        P2DIR |= BIT0;
        P2DIR |= BIT1;
        P2DIR |= BIT2;
        P2OUT &= ~BIT0;
        P2OUT &= ~BIT1;
        P2OUT &= ~BIT2;
        break;
    default: // bad input
        break;
    }
}

uint8_t toggleRateLED1()
{
    P1OUT ^= BIT0;
    return 1;
}

void toggleLED1()
{
    P1OUT ^= BIT0;
}

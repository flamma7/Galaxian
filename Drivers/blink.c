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
    _configLED(LED1);
    setTimerA(time, &toggleRateLED1);
}

void blinkPushLED1(BUTTON but)
{
    _configLED(LED1);
    P1OUT |= BIT0;              // led on
    configButton(but, &toggleLED1);
}


static void _configLED(LED led)
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

void toggleRateLED1()
{
    P1OUT ^= BIT0;
    startTimerA(_blinkRateTimerA);
}

void toggleLED1()
{
    P1OUT ^= BIT0;
}

//#define multiply(x,y)   (x)*(y)
//
//
//inline double multiply(double num1, double num2)
//{
//    return num1 * num2;
//}__attribute__((always_inline))
//
//struct myStuct{
//    char one;
//    uint32_t two;
//    uint16_t three;
//}__attribute__((aligned(8)));
//__attribute__((packed));
// align bytes in struct for speed

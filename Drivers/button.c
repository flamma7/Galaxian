/*
 * button.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/button.h"
#include "Headers/timerA.h"
#include <stdio.h> // NULL

TIMER_A buttonTimer;
BUTTON buttonIntrpt;

BUTTON_CONFIG configButton(BUTTON but, void(*handler)(void))
{
    if(handler == NULL)
        return BUTTON_CONFIG_ERR_BAD_INPUT;

    switch(but)
    {
    case LPAD_S1:
        if(buttons_in_use & LPAD_S1)
            return BUTTON_CONFIG_ERR_IN_USE;
        else
            buttons_in_use |= LPAD_S1;
        P1DIR &= ~BIT1;
        P1IE |= BIT1;
        P1IFG &= ~BIT1;
        P1IES |= BIT1;                  // LOW TO HIGH flag intrpt
        button_s1_handler = handler;
        P1REN |= BIT1;
        P1OUT |= BIT1;                  // PULL UP
        NVIC_EnableIRQ(PORT1_IRQn);

        break;
    case LPAD_S2:
        if(buttons_in_use & LPAD_S2)
            return BUTTON_CONFIG_ERR_IN_USE;
        else
            buttons_in_use |= LPAD_S2;
        P1DIR &= ~BIT4;
        P1IE |= BIT4;
        P1IFG &= ~BIT4;
        P1IES |= BIT4;                  // LOW TO HIGH flag intrpt
        button_s2_handler = handler;
        P1REN |= BIT4;
        P1OUT |= BIT4;                  // PULL UP
        NVIC_EnableIRQ(PORT1_IRQn);
        break;
    case BOOSTER_S1:
        if(buttons_in_use & BOOSTER_S1)
            return BUTTON_CONFIG_ERR_IN_USE;
        else
            buttons_in_use |= BOOSTER_S1;
        P5DIR &= ~BIT1;
        P5IE |= BIT1;
        P5IFG &= ~BIT1;
        P5IES |= BIT1;                  // LOW TO HIGH flag intrpt
        booster_s1_handler = handler;
        P5REN |= BIT1;
        P5OUT |= BIT1;                  // PULL UP
        NVIC_EnableIRQ(PORT5_IRQn);
        // p5.1
        break;
    case BOOSTER_S2:
        if(buttons_in_use & BOOSTER_S2)
            return BUTTON_CONFIG_ERR_IN_USE;
        else
            buttons_in_use |= BOOSTER_S2;
        P3DIR &= ~BIT5;
        P3IE |= BIT5;
        P3IFG &= ~BIT5;
        P3IES |= BIT5;                  // LOW TO HIGH flag intrpt
        booster_s2_handler = handler;
        P3REN |= BIT5;
        P3OUT |= BIT5;                  // PULL UP
        NVIC_EnableIRQ(PORT3_IRQn);
        // p3.5
        break;
    case JOYSTICK_S1:
        if(buttons_in_use & JOYSTICK_S1)
            return BUTTON_CONFIG_ERR_IN_USE;
        else
            buttons_in_use |= JOYSTICK_S1;
        P4DIR &= ~BIT1;
        P4IE |= BIT1;
        P4IFG &= ~BIT1;
        P4IES |= BIT1;                  // LOW TO HIGH flag intrpt
        joystick_s1_handler = handler;
        P4REN |= BIT1;
        P4OUT |= BIT1;                  // PULL UP
        NVIC_EnableIRQ(PORT4_IRQn);
        break;
        // p4.1
    default:
        return BUTTON_CONFIG_ERR_BAD_INPUT;
    }
    buttonTimer = setTimerA(ONE_MS, &_debounceHandler);

    return BUTTON_CONFIG_NO_ERROR;
}

// simply reenables the intrpt
uint8_t _debounceHandler(void)
{
    buttonTimerInUse = 0;
    switch(buttonIntrpt)
    {
        case LPAD_S1:
            P1IE |= BIT1;
            break;
        case LPAD_S2:
            P1IE |= BIT4;
           break;
        case BOOSTER_S1:
            P5IE |= BIT1;
            break;
        case BOOSTER_S2:
            P3IE |= BIT5;
            break;
        case JOYSTICK_S1:
            P4IE |= BIT1;
            break;
        default:
            break;
    }
    return 0;
}

void Port1Handler(void)
{
    if (buttonTimerInUse)               // ignore the input if another input is already being tracked
    {
        P1IFG &= ~BIT1;
        P1IFG &= ~BIT4;
        return;
    }

    if(P1IFG & BIT1)
    {
        P1IE &= ~BIT1;
        P1IFG &= ~BIT1;
        buttonIntrpt = LPAD_S1;
        startTimerA(buttonTimer);
        (*button_s1_handler)();
    }
    else if(P1IFG & BIT4)
    {
        P1IE &= ~BIT4;
        P1IFG &= ~BIT4;
        buttonIntrpt = LPAD_S2;
        startTimerA(buttonTimer);
        (*button_s2_handler)();
    }
}

void Port3Handler(void)
{
    if (buttonTimerInUse)               // ignore the input if another input is already being tracked
    {
        P3IFG &= ~BIT5;
        return;
    }

    if(P3IFG & BIT5)
    {
        P3IE &= ~BIT5;
        P3IFG &= ~BIT5;
        buttonIntrpt = BOOSTER_S2;
        startTimerA(buttonTimer);
        (*booster_s2_handler)();
    }
}

void Port4Handler(void)
{
    if (buttonTimerInUse)               // ignore the input if another input is already being tracked
    {
        P4IFG &= ~BIT1;
        return;
    }

    if(P4IFG & BIT1)
    {
        P4IE &= ~BIT1;
        P4IFG &= ~BIT1;
        buttonIntrpt = JOYSTICK_S1;
        startTimerA(buttonTimer);
        (*joystick_s1_handler)();
    }
}

void Port5Handler(void)
{
    if (buttonTimerInUse)               // ignore the input if another input is already being tracked
    {
        P5IFG &= ~BIT1;
        return;
    }

    if(P5IFG & BIT1)
    {
        P5IE &= ~BIT1;
        P5IFG &= ~BIT1;
        buttonIntrpt = BOOSTER_S1;
        startTimerA(buttonTimer);
        (*booster_s1_handler)();
    }
}

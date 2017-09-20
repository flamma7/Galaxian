/*
 * button.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/button.h"
#include <stdio.h> // NULL

void initButtons()
{
    buttons_in_use = 0;
    button_s1_handler = NULL;
    button_s2_handler = NULL;
}

BUTTON_CONFIG configButton(BUTTON but, void(*handler)(void))
{
    switch(but)
    {
    case BUTTON_S1:
        if(buttons_in_use & 1)
            return BUTTON_CONFIG_ERR_IN_USE;
        else
            buttons_in_use |= 1;
        P1DIR &= ~BIT1;
        P1IE |= BIT1;
        P1IFG &= ~BIT1;
        P1IES |= BIT1;                  // LOW TO HIGH flag intrpt
        button_s1_handler = handler;
        P1REN |= BIT1;
        P1OUT |= BIT1;                  // PULL UP
        NVIC_EnableIRQ(PORT1_IRQn);

        break;
    case BUTTON_S2:
        if(buttons_in_use & 1)
            return BUTTON_CONFIG_ERR_IN_USE;
        else
            buttons_in_use |= 2;
        P1DIR &= ~BIT4;
        P1IE |= BIT4;
        P1IFG &= ~BIT4;
        P1IES |= BIT4;                  // LOW TO HIGH flag intrpt
        button_s2_handler = handler;
        P1REN |= BIT4;
        P1OUT |= BIT4;                  // PULL UP
        NVIC_EnableIRQ(PORT1_IRQn);

        break;
    default:
        return BUTTON_CONFIG_ERR_BAD_INPUT;
    }
    __enable_interrupt();
    return BUTTON_CONFIG_NO_ERROR;
}

void Port1Handler(void)
{
    (*button_s1_handler)();
    P1IFG &= ~BIT1;
}

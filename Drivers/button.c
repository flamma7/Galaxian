/*
 * button.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/button.h"
#include <stdio.h> // NULL

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
        P5IES &= ~BIT1;                  // LOW TO HIGH flag intrpt
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
        // p3.5
        break;
    case JOYSTICK_S1:
        if(buttons_in_use & JOYSTICK_S1)
            return BUTTON_CONFIG_ERR_IN_USE;
        else
            buttons_in_use |= JOYSTICK_S1;
        // p4.1
        break;
    default:
        return BUTTON_CONFIG_ERR_BAD_INPUT;
    }
    return BUTTON_CONFIG_NO_ERROR;
}

void Port1Handler(void)
{
    if(P1IFG & BIT1)
    {
        P1IFG &= ~BIT1;
        (*button_s1_handler)();
    }
    else if (P1IFG & BIT4)
    {
        P1IFG &= ~BIT4;
        (*button_s1_handler)();
    }
}

void Port3Handler(void)
{

}

void Port5Handler(void)
{
    P5IFG &= ~BIT1;
    (*booster_s1_handler)();
}

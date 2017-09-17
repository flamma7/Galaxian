/*
 * timerA.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/timerA.h"


/* Returns an open timerA */
TIMER_A setTimerA(const TIMER_A_TIME time, const void(*handler)(void))
{
    if(!(_timerAs_in_use & TIMERA_0))
    {
        _configTimerA0(time);
        _timerA0_handler = handler;
        _timerAs_in_use |= TIMERA_0;            // set timer status in use
        return TIMERA_0;
    }
    else if(!(_timerAs_in_use & TIMERA_1))
    {
        _configTimerA1(time);
        _timerA1_handler = handler;
        _timerAs_in_use |= TIMERA_1;            // set timer status in use
        return TIMERA_1;
    }
    else if(!(_timerAs_in_use & TIMERA_2))
    {
        _configTimerA2(time);
        _timerA2_handler = handler;
        _timerAs_in_use |= TIMERA_2;            // set timer status in use
        return TIMERA_2;
    }
    else if (!(_timerAs_in_use & TIMERA_3))
    {
        _configTimerA3(time);
        _timerA3_handler = handler;
        _timerAs_in_use |= TIMERA_3;            // set timer status in use
        return TIMERA_3;
    }
    else
    {
        return TIMERA_ERROR;
    }
}


static void _configTimerA0(const TIMER_A_TIME time)
{
    switch(time)
    {
    case ONE_S:
           TA0CTL |= TACLR;
           TA0CTL &= ~TAIFG;
           TA0CTL |= TASSEL_1;
           TA0CTL &= ~ID_0;
           TA0CTL |= MC_1;
           TA0CCTL0 &= ~CAP;

           TA0EX0 &= ~TAIDEX_0;
            |= 0xFFFF;
        break;
    default:
        break;
    }
}

TIMER_A_START startTimerA(TIMER_A timerA)
{
    switch(timerA)
    {
    case TIMERA_0:
        if (!(timerAs_in_use & TIMERA_0))       // check if not configured
            return TIMER_A_START_ERR_NOT_CONFIGURED;
        TA0CCR0 |= timerA0_counter;
        break;
    case TIMERA_1:
        if (!(timerAs_in_use & TIMERA_1))
            return TIMER_A_START_ERR_NOT_CONFIGURED;
        TA1CCR0 |= timerA1_counter;
        break;
    case TIMERA_2:
        if (!(timerAs_in_use & TIMERA_2))
            return TIMER_A_START_ERR_NOT_CONFIGURED;
        TA2CCR0 |= timerA2_counter;
        break;
    case TIMERA_3:
        if (!(timerAs_in_use & TIMERA_3))
            return TIMER_A_START_ERR_NOT_CONFIGURED;
            TA3CCR0 |= timerA3_counter;
    default:
        return TIMER_A_START_ERR_NOT_CONFIGURED;
    }
    return TIMER_A_START_NO_ERROR;
}

void TimerA0Handler(void)
{
    (*_timerA0_handler)();
}

/*
 * timerA.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/timerA.h"


/* Returns an open timerA */
TIMER_A setTimerA(const TIMER_A_TIME time, void(*handler)(void))
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
           TA0CTL |= TAIE;
//           TA0CCTL0 &= ~CAP;
           TA0EX0 &= ~TAIDEX_0;
           _timerA0_counter = 0x7FFF;
           TA0CCTL0 = TIMER_A_CCTLN_CCIE;
           NVIC_EnableIRQ(TA0_0_IRQn);
        break;
    default:
        break;
    }
}

static void _configTimerA1(const TIMER_A_TIME time)
{
    ;
}

static void _configTimerA2(const TIMER_A_TIME time)
{
    ;
}

static void _configTimerA3(const TIMER_A_TIME time)
{
    ;
}

TIMER_A_START startTimerA(TIMER_A timerA)
{
    switch(timerA)
    {
    case TIMERA_0:
        if (!(_timerAs_in_use & TIMERA_0))       // check if not configured
            return TIMER_A_START_ERR_NOT_CONFIGURED;
        TA0CCR0 |= _timerA0_counter;
        break;
    case TIMERA_1:
        if (!(_timerAs_in_use & TIMERA_1))
            return TIMER_A_START_ERR_NOT_CONFIGURED;
        TA1CCR0 |= _timerA1_counter;
        break;
    case TIMERA_2:
        if (!(_timerAs_in_use & TIMERA_2))
            return TIMER_A_START_ERR_NOT_CONFIGURED;
        TA2CCR0 |= _timerA2_counter;
        break;
    case TIMERA_3:
        if (!(_timerAs_in_use & TIMERA_3))
            return TIMER_A_START_ERR_NOT_CONFIGURED;
            TA3CCR0 |= _timerA3_counter;
    default:
        return TIMER_A_START_ERR_NOT_CONFIGURED;
    }
    return TIMER_A_START_NO_ERROR;
}

void TimerA0Handler(void)
{
    TA0CTL &= ~TAIFG;
    TA0CCTL0 &= ~CCIFG;
    TA0R = 0x0;
    (*_timerA0_handler)();
}

void TimerA1Handler(void)
{
    TA1CTL &= ~TAIFG;
    TA1CCTL0 &= ~CCIFG;
    TA1R = 0x0;
    (*_timerA1_handler)();
}

void TimerA2Handler(void)
{
    TA2CTL &= ~TAIFG;
    TA2CCTL0 &= ~CCIFG;
    TA2R = 0x0;
    (*_timerA2_handler)();
}

void TimerA3Handler(void)
{
    TA3CTL &= ~TAIFG;
    TA3CCTL0 &= ~CCIFG;
    TA3R = 0x0;
    (*_timerA3_handler)();
}

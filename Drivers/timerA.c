/*
 * timerA.c
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/timerA.h"


/* Returns an open timerA */
TIMER_A setTimerA(const TIMER_A_TIME time, uint8_t(*handler)(void))
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
   TA0CTL |= TACLR;
   TA0CTL &= ~TAIFG;
   TA0CTL &= ~ID_0;
   TA0EX0 &= ~TAIDEX_0;
   TA0CCTL0 = TIMER_A_CCTLN_CCIE;
   NVIC_EnableIRQ(TA0_0_IRQn);

    // Select clock and count
    switch(time)
    {
    case ONE_MS:
       TA0CTL |= TASSEL_2;
       _timerA0_counter = 3000;
        break;
    case TEN_MS:
       TA0CTL |= TASSEL_2;
       _timerA0_counter = 30000;
        break;
    case ONE_S:
       TA0CTL |= TASSEL_1;
       _timerA0_counter = 0x7FFF;
        break;
    case HALF_S:
       TA0CTL |= TASSEL_1;
       _timerA0_counter = 0x3FFF;
    default:
        break;
    }
}

static void _configTimerA1(const TIMER_A_TIME time)
{
   TA1CTL |= TACLR;
   TA1CTL &= ~TAIFG;
   TA1CTL &= ~ID_0;
   TA1EX0 &= ~TAIDEX_0;
   TA1CCTL0 = TIMER_A_CCTLN_CCIE;
   NVIC_EnableIRQ(TA1_0_IRQn);

    // Select clock and count
    switch(time)
    {
    case ONE_MS:
       TA1CTL |= TASSEL_2;
       _timerA1_counter = 3000;
        break;
    case TEN_MS:
       TA1CTL |= TASSEL_2;
       _timerA1_counter = 30000;
        break;
    case ONE_S:
       TA1CTL |= TASSEL_1;
       _timerA1_counter = 0x7FFF;
        break;
    case HALF_S:
       TA1CTL |= TASSEL_1;
       _timerA1_counter = 0x3FFF;
    default:
        break;
    }
}

static void _configTimerA2(const TIMER_A_TIME time)
{
   TA2CTL |= TACLR;
   TA2CTL &= ~TAIFG;
   TA2CTL &= ~ID_0;
   TA2EX0 &= ~TAIDEX_0;
   TA2CCTL0 = TIMER_A_CCTLN_CCIE;
   NVIC_EnableIRQ(TA2_0_IRQn);

    // Select clock and count
    switch(time)
    {
    case ONE_MS:
       TA2CTL |= TASSEL_2;
       _timerA2_counter = 3000;
        break;
    case TEN_MS:
       TA2CTL |= TASSEL_2;
       _timerA2_counter = 30000;
        break;
    case ONE_S:
       TA2CTL |= TASSEL_1;
       _timerA2_counter = 0x7FFF;
        break;
    case HALF_S:
       TA2CTL |= TASSEL_1;
       _timerA2_counter = 0x3FFF;
    default:
        break;
    }
}

static void _configTimerA3(const TIMER_A_TIME time)
{
   TA3CTL |= TACLR;
   TA3CTL &= ~TAIFG;
   TA3CTL &= ~ID_0;
   TA3EX0 &= ~TAIDEX_0;
   TA3CCTL0 = TIMER_A_CCTLN_CCIE;
   NVIC_EnableIRQ(TA3_0_IRQn);

    // Select clock and count
    switch(time)
    {
    case ONE_MS:
       TA3CTL |= TASSEL_2;
       _timerA3_counter = 3000;
        break;
    case TEN_MS:
       TA3CTL |= TASSEL_2;
       _timerA3_counter = 30000;
        break;
    case ONE_S:
       TA3CTL |= TASSEL_1;
       _timerA3_counter = 0x7FFF;
        break;
    case HALF_S:
       TA3CTL |= TASSEL_1;
       _timerA3_counter = 0x3FFF;
    default:
        break;
    }
}

TIMER_A_START startTimerA(TIMER_A timerA)
{
    switch(timerA)
    {
    case TIMERA_0:
        if (!(_timerAs_in_use & TIMERA_0))       // check if not configured
            return TIMER_A_START_ERR_NOT_CONFIGURED;
        TA0CTL |= MC_1;
        TA0CTL |= TAIE;
        TA0R = 0;
        TA0CCR0 |= _timerA0_counter;
        break;
    case TIMERA_1:
        if (!(_timerAs_in_use & TIMERA_1))
            return TIMER_A_START_ERR_NOT_CONFIGURED;
        TA1CTL |= MC_1;
        TA1CTL |= TAIE;
        TA1R = 0;
        TA1CCR0 |= _timerA1_counter;
        break;
    case TIMERA_2:
        if (!(_timerAs_in_use & TIMERA_2))
            return TIMER_A_START_ERR_NOT_CONFIGURED;
        TA2CTL |= MC_1;
        TA2CTL |= TAIE;
        TA2R = 0;
        TA2CCR0 |= _timerA2_counter;
        break;
    case TIMERA_3:
        if (!(_timerAs_in_use & TIMERA_3))
            return TIMER_A_START_ERR_NOT_CONFIGURED;
        TA3CTL |= MC_1;
        TA3CTL |= TAIE;
        TA3R = 0;
        TA3CCR0 |= _timerA3_counter;
    default:
        return TIMER_A_START_ERR_NOT_CONFIGURED;
    }
    return TIMER_A_START_NO_ERROR;
}

void TimerA0Handler(void)
{
    TA0CTL &= ~TAIE;            // avoid double intrpt triggers
    TA0CTL &= ~TAIFG;
    TA0CCTL0 &= ~CCIFG;
    TA0CTL &= ~MC_3;            // stop counting to avoid double triggers

    if((*_timerA0_handler)())
        TA0CTL |= MC_1;
}


void TimerA1Handler(void)
{
    TA1CTL &= ~TAIE;            // avoid double intrpt triggers
    TA1CTL &= ~TAIFG;
    TA1CCTL0 &= ~CCIFG;
    TA1CTL &= ~MC_3;            // stop counting to avoid double triggers

    if((*_timerA1_handler)())
        TA1CTL |= MC_1;
}

void TimerA2Handler(void)
{
    TA2CTL &= ~TAIE;            // avoid double intrpt triggers
    TA2CTL &= ~TAIFG;
    TA2CCTL0 &= ~CCIFG;
    TA2CTL &= ~MC_3;            // stop counting to avoid double triggers

    if((*_timerA2_handler)())
        TA2CTL |= MC_1;
}

void TimerA3Handler(void)
{
    TA3CTL &= ~TAIE;            // avoid double intrpt triggers
    TA3CTL &= ~TAIFG;
    TA3CCTL0 &= ~CCIFG;
    TA3CTL &= ~MC_3;            // stop counting to avoid double triggers

    if((*_timerA3_handler)())
        TA3CTL |= MC_1;
}

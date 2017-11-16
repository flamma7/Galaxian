/*
 * joystick.c
 *
 *  Created on: Nov 4, 2017
 *      Author: luke
 */

#include "msp.h"
#include "Headers/joystick.h"
#include "Headers/fifo.h"
#include "Headers/uart.h"
#include "Headers/timerA.h"

#define ONE_ADC

#ifdef MULT_ADC
void init_joystick() // single channel; single conversion
{
// configure pins pg 501
    // J1.2 horizontal = MSP p6.0 -> secondary A15 (out of 23)
    // J3.26 Vertical == MSP p4.4 -> 4th A9
    // p6.0 primary mode
    P6SEL0 |= BIT0;
    transmit_str("Initializing multiple ADC's");
    P6SEL1 &= ~BIT0;
    // p4.4 tertiary mode
    P4SEL0 |= BIT4;
    P4SEL1 |= BIT4;

    // Set up for 8 bit'll do
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;         // reset
    // SHI bit to trigger first conversion
    ADC14->CTL0 |= ADC14_CTL0_MSC;          // requires rising edge of SHI signal each time
    ADC14->CTL0 |= ADC14_CTL0_SHT0__32;     // 32 clock cycles?
    ADC14->CTL0 |= ADC14_CTL0_SHT1__32;

    ADC14->CTL0 |= ADC14_CTL0_CONSEQ_2;     // repeat single-channel conversion
    ADC14->CTL0 |= ADC14_CTL0_SSEL__ACLK;   // aclk clock
    ADC14->CTL0 |= ADC14_CTL0_DIV__8;       // clock divider by 8
    ADC14->CTL0 |= ADC14_CTL0_SHP;
//     TODO SHS and SHP bits?
//    ADC14->CTL0 |= ADC14_CTL0_PDIV__4;     // predivide clock by 64
    ADC14->CTL1 |= ADC14_CTL1_RES__8BIT;    // 8 bit resolution

    // Thresholds? x2 types? they're fine where they are
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_9;       // INPUT A9 FOR MEM0

    // ADC14CSTARTADDX?

    ADC14->IER0 |= ADC14_IER0_IE0;          // Enable intrpt request for ADC14IFG0
    // read ADC14->IFGR0 to tell if intrpt is pending in ADC14MEM0
    // write to ADC14CLRIFGR0 to clear ADC14IG0

    ADC14->CTL0 |= ADC14_CTL0_ON;
    ADC14->CTL0 |= ADC14_CTL0_ENC;         // READY
    ADC14->CTL0 |= ADC14_CTL0_SC;
    NVIC_EnableIRQ(ADC14_IRQn);

    /* Create and initialize the circular buffer */
    y_buffer = init_fifo(JOYSTICK_BUFFER_SIZE);
    x_buffer = init_fifo(JOYSTICK_BUFFER_SIZE);
}
#endif

#ifdef ONE_ADC
void init_joystick() // single channel; single conversion
{
// configure pins pg 501
    // J1.2 horizontal = MSP p6.0 -> secondary A15 (out of 23)
    // J3.26 Vertical == MSP p4.4 -> 4th A9
    // p6.0 primary mode
    P6SEL0 |= BIT0;
    transmit_str("Initializing One ADC");
    P6SEL1 &= ~BIT0;
    // p4.4 tertiary mode
    P4SEL0 |= BIT4;
    P4SEL1 |= BIT4;

    // Set up for 8 bit'll do
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;         // reset
    // SHI bit to trigger first conversion
    ADC14->CTL0 |= ADC14_CTL0_MSC;          // requires rising edge of SHI signal each time
    ADC14->CTL0 |= ADC14_CTL0_SHT0_0;     // 32 clock cycles?
    ADC14->CTL0 |= ADC14_CTL0_SHT1__32;

    ADC14->CTL0 |= ADC14_CTL0_CONSEQ_2;     // repeat single-channel conversion
    ADC14->CTL0 |= ADC14_CTL0_SSEL__ACLK;   // aclk clock
    ADC14->CTL0 |= ADC14_CTL0_DIV__8;       // clock divider by 8
    ADC14->CTL0 |= ADC14_CTL0_SHP;
    //ADC14->CTL0 |= ADC14_CTL0_PDIV__32;     // predivide clock by 1
    ADC14->CTL1 |= ADC14_CTL1_RES__8BIT;    // 8 bit resolution

    // Thresholds? x2 types? they're fine where they are
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_15;       // INPUT A9 FOR MEM0

    //ADC14->IER0 |= ADC14_IER0_IE0;          // Enable intrpt request for ADC14IFG0

    ADC14->CTL0 |= ADC14_CTL0_ON;
    ADC14->CTL0 |= ADC14_CTL0_ENC;         // READY
    ADC14->CTL0 |= ADC14_CTL0_SC;
    //NVIC_EnableIRQ(ADC14_IRQn);

    /* initialize the circular buffer */
    x_buffer = init_fifo(JOYSTICK_BUFFER_SIZE);

    /* Create a timer to read the data in the circular buffer */
    joystick_timer = (uint8_t) setTimerA(TEN_MS, &_store_adc_buffer);
    if(joystick_timer == TIMERA_ERROR)
      {
	transmit_str("Joystick TimerA error. Possibly none open?");
	while(1);
      }
    startTimerA(joystick_timer);
}
#endif

JOYSTICK_ERR get_joy_dir(JOYSTICK_DIR* dir)
{
  JOYSTICK_DATA_TYPE data;
  if(get_joystick(&data) == JOYSTICK_NO_DATA)
    {
      return JOYSTICK_NO_DATA;
    }
  switch(data)
    {
    case data < JOYSTICK_RIGHT_THRESH:
      *dir = DIR_RIGHT;
      break;
    case data > JOYSTICK_LEFT_THRESH:
      *dir = DIR_LEFT;
      break;
    default:
      *dir = DIR_NO_MOVEMENT;
    }
  return JOYSTICK_NO_ERR;
}

JOYSTICK_ERR get_joystick(JOYSTICK_DATA_TYPE* x)
{
  uint8_t empty = 1;
  uint16_t data = get_fifo(x_buffer, &empty);
  if(empty == 1)
    {
      transmit_str("joystick x buffer empty");
      return JOYSTICK_NO_DATA;
    }
  *x = data;
  return 
}


void stop_joystick()
{
    // poll busy bit until reset then clear ADC14ENC
    // ADC14->CTL0 & ADC14BUSY
}

void restart_joystick()
{
    // set ADC14ENC
}

/* Reads the adc and stores the value in the circular buffer 
 *    Not a user function */
void _store_adc_buffer()
{
  add_fifo(x_buffer, ADC14->MEM[0]);
}

/* void ADC14_Handler(void) */
/* { */
/*     // flag is cleared automatically */
/*     uint8_t val = ADC14->MEM[0]; */
/*     transmit_num8(val); */
/* //    add_fifo(y_buffer, val); */
/*     ; */
/* } */

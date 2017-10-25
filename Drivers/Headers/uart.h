/*
 * uart.h
 *
 *  Created on: Sep 15, 2017
 *      Author: luke
 *
 *      USAGE:
 *          1) Call config_uart() to initialize UART
 *          2) Call a transmit_* function to write on UART
 */

#ifndef DRIVERS_HEADERS_UART_H_
#define DRIVERS_HEADERS_UART_H_

#include <stdint.h>
// a better procedure is to make a buffer with intrpts that publish the letters

// TODO Change these names to uart_send_str and uart_send_char and uart_send_uint32

/* Configures the eUSCI_A module to UART mode */
void config_uart();
/* Transmits a single char over UART */
void transmit_char(const char a);
/* Transmits a string over UART, reads until NULL terminator, adds a newline */
void transmit_str(const char * str);
/* Convert an unsigned number to string and transmit, cast for smaller numbers */
void transmit_num32(uint32_t num);


/* Helper functions for setup and conversions */
static void _config_baud_9600();
/* Helper function converts 32bit number to string with decimal chars */
static void _uitoa32(uint32_t num, char * str);


// read functions

#endif /* DRIVERS_HEADERS_UART_H_ */

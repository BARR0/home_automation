/*
 * uart.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef UART_H_
#define UART_H_

// Initialize necessary registers
// A1: UART TX
// A2: UART RX
void uartInit(void);

// Send one character
void uartPutCh(char output);
// Send a string
void uartPutString(char *output);

// Is there a RX character available
int uartIsCharAvailable(void);
// Return the pressed character
char uartGetCh(void);
// Return a buffer to the next line
char *uartGetLine(void);

// DEBUG: Simpler way of printing a string and an integer
void uartPrintInt(char *output, int value);

#endif /* UART_H_ */

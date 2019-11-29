/*
 * uart.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef UART_H_
#define UART_H_

void uartInit(void);

void uartPutCh(char output);
void uartPutString(char *output);

int uartIsCharAvailable(void);
char uartGetCh(void);
char *uartGetLine(void);
void uartPrintInt(char *output, int value);

#endif /* UART_H_ */

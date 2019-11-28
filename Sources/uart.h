/*
 * uart.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef UART_H_
#define UART_H_

void uartInit(void);
void uartPutCh(char input);
void uartPutString(char *input);
int uartIsCharAvailable(void);
char uartGetCh(void);
char *uartGetLine(void);

#endif /* UART_H_ */

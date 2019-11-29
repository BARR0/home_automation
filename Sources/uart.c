/*
 * uart.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include "derivative.h"
#include "common.h"

#define OSR0 13
#define SBR0 13
#define UART0RXPIN 1
#define UART0TXPIN 2

void uartInit(void)
{
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;  // Enable clock to UART0
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1); // Select FLL as the clock for UART0
    UART0->C2 = 0;                       // Disable UART0
    UART0->BDH = 0;
    UART0->BDL = UART0_BDL_SBR(SBR0);                // Set SBR to 13
    UART0->C4 = OSR0;                                // Set OSR to 13
    UART0->C1 = 0;                                   // 8 bit, no parity, 1 stop bit
    UART0->C2 = UART0_C2_TE_MASK | UART0_C2_RE_MASK; // Transmit/Receive Enable
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;              // Enable CLock for PORTA
    PORTA->PCR[UART0TXPIN] = PORT_PCR_MUX(2);        // Configure PORTA2 as function UART0_TX
    PORTA->PCR[UART0RXPIN] = PORT_PCR_MUX(2);        // Configure PORTA1 as function UART0_RX
}

void uartPutCh(char output)
{
    while (!(UART0->S1 & UART0_S1_TDRE_MASK))
        ;
    UART0->D = output;
}

void uartPutString(char *output)
{
    for (; *output != '\0'; output++)
    {
        uartPutCh(*output);
    }
    if (*(output - 1) == '\n')
    {
        uartPutCh('\r');
    }
}

int uartIsCharAvailable(void)
{
    return UART0->S1 & UART0_S1_RDRF_MASK;
}

char uartGetCh(void)
{
    while (!uartIsCharAvailable())
        ;
    return UART0->D;
}

#define MAX_BUFF 1000

volatile char buff[MAX_BUFF];

volatile char *uartGetLine(void)
{
    volatile char *current = buff;
    char next;
    int i = 0;
    for (next = uartGetCh(); next != '\r'; next = uartGetCh())
    {
        if (next != 127)
        {
            i++;
            uartPutCh(next);
            *current = next;
            current++;
        }
        else if(i > 0)
        {
            i--;
            uartPutCh(next);
            current--;
        }
        
    }
    *current = '\n';
    current++;
    *current = '\0';
    return buff;
}

void uartPrintInt(char *output, int value)
{
    char buff[1000];
    sprintf(buff, "%s%d\n", output, value);
    uartPutString(buff);
}

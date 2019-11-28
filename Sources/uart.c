/*
 * uart.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

void uartInit(void)
{
    // TODO
}

void uartPutCh(char output)
{
    // TODO
}

void uartPutString(char *output)
{
    for (; *output != '\0'; output++)
    {
        uartPutCh(*output);
    }
}

int uartIsCharAvailable(void)
{
    // TODO
    return -1;
}

char uartGetCh(void)
{
    while (!uartIsCharAvailable());
    // TODO
    return '\0';
}

#define MAX_BUFF 1000

char buff[MAX_BUFF];

char *uartGetLine(void)
{
    char *current = buff;
    char next;
    for (next = uartGetCh(); next != '\n'; next = uartGetCh())
    {
        *current = next;
        current++;
    }
    *current = '\n';
    current++;
    *current = '\0';
    return buff;
}

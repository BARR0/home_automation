/*
 * status.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include <stdio.h>

#include "adaptive.h"
#include "config.h"
#include "thermostat.h"
#include "status.h"
#include "timed.h"
#include "timer.h"
#include "uart.h"

#define MAX_BUFF 1000

void printStatus(enum status component);

void statusPrint(void)
{
    char buff[MAX_BUFF];
    uartPutString("Status:\n");

    // Apparently this feature is not supported
    // time_t time = timerGetRTC();
    // char date[MAX_BUFF];
    // ctime_s(date, MAX_BUFF, &time);

    sprintf(buff, "The current Date/Time is: %d\n", timerGetRTC());
    uartPutString(buff);

    sprintf(buff, "The current Temperature is: %d\n", thermostatTemperature());
    uartPutString(buff);

    sprintf(buff, "The minimum Temperature threshold is: %d\n", thermostatGetMinTemp());
    uartPutString(buff);

    sprintf(buff, "The maximum Temperature threshold is: %d\n", thermostatGetMaxTemp());
    uartPutString(buff);

    uartPutString("Fan status: ");
    printStatus(thermostatStatus());
    uartPutString("\n");

    sprintf(buff, "Current Light intensity in percentage: %d\n", adaptiveLightingPercentage());
    uartPutString(buff);

    sprintf(buff, "The minimum Light threshold is: %d\n", adaptiveLightingGetMinLight());
    uartPutString(buff);

    uartPutString("Adaptive LED status: ");
    printStatus(adaptiveLightingStatus());
    uartPutString("\n");

    uartPutString("Timed LED status: ");
    printStatus(timedLightingStatus());
    uartPutString("\n");

    sprintf(buff, "The Alarm ON time is: %d\n", timedLightingGetAlarmOn());
    uartPutString(buff);

    sprintf(buff, "The Alarm OFF time is: %d\n", timedLightingGetAlarmOff());
    uartPutString(buff);

    uartPutCh('\n');

    uartPutString("Controls:\n");

    sprintf(buff, "To toggle the fan: '%c'\n", THERMOSTAT_KEY);
    uartPutString(buff);

    sprintf(buff, "To toggle the adaptive LED: '%c'\n", ADAPTIVE_LIGHTING_KEY);
    uartPutString(buff);

    sprintf(buff, "To toggle the timed LED: '%c'\n", TIMED_LIGHTING_KEY);
    uartPutString(buff);

    sprintf(buff, "To enter config mode: '%c'\n", CONFIG_KEY);
    uartPutString(buff);

    uartPutCh('\n');
}

void printStatus(enum status component)
{
    switch (component)
    {
    case Off:
        uartPutString("OFF");
        break;
    case On:
        uartPutString("ON");
        break;
    case Auto:
        uartPutString("AUTO");
        break;
    }
}

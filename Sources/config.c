/*
 * config.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include <stdlib.h>
#include "adaptive.h"
#include "config.h"
#include "thermostat.h"
#include "timed.h"
#include "timer.h"
#include "uart.h"

void configUpdate(void)
{
    char *buff;

    uartPutString("Configuration Mode\n");

    int time = -1;
    while (time < 0)
    {
        uartPutString("RTC Date/Time [Positive Number]: ");
        buff = uartGetLine();
        uartPutString("\n");
        time = atoi(buff);
    }

    uartPutString("Minimal Temperature Threshold: ");
    buff = uartGetLine();
    uartPutString("\n");
    int min_temp_th = atoi(buff);
    int max_temp_th = min_temp_th - 1;
    while (max_temp_th < min_temp_th)
    {
        uartPutString("Maximum Temperature Threshold: ");
        buff = uartGetLine();
        uartPutString("\n");
        max_temp_th = atoi(buff);
    }

    int min_light_th = -1;
    while (min_light_th < 0 || min_light_th > 100)
    {
        uartPutString("Minimum Light Threshold [Percentage: 0 - 100]: ");
        buff = uartGetLine();
        uartPutString("\n");
        min_light_th = atoi(buff);
    }

    int alarm_on = -1;
    while (alarm_on < 0)
    {
        uartPutString("Alarm ON time [Positive Number]: ");
        buff = uartGetLine();
        uartPutString("\n");
        alarm_on = atoi(buff);
    }
    int alarm_off = -1;
    while (alarm_off < 0)
    {
        uartPutString("Alarm OFF time [Positive Number]: ");
        buff = uartGetLine();
        uartPutString("\n");
        alarm_off = atoi(buff);
    }

    uartPutString("Configuration Finished\n\n");

    thermostatConfig(min_temp_th, max_temp_th);
    adaptiveLightingConfig(min_light_th);
    timerSetRTC(time);
    timedLightingConfig(alarm_on, alarm_off);
}

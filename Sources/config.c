/*
 * config.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include <stdio.h>
#include "adaptive.h"
#include "config.h"
#include "thermostat.h"
#include "timer.h"
#include "uart.h"

void configUpdate(void)
{
    char *buff;

    uartPutString("Configuration Mode\n");

    uartPutString("RTC Date/Time: ");
    buff = uartGetLine();
    uartPutString("\n");
    int time = atoi(buff);
    timerSetRTC(time);

    uartPutString("Minimal Temperature Threshold: ");
    buff = uartGetLine();
    uartPutString("\n");
    int min_temp_th = atoi(buff);
    uartPutString("Maximum Temperature Threshold: ");
    buff = uartGetLine();
    uartPutString("\n");
    int max_temp_th = atoi(buff);
    thermostatConfig(min_temp_th, max_temp_th);

    uartPutString("Minimum Light Threshold: ");
    buff = uartGetLine();
    uartPutString("\n");
    int min_light_th = atoi(buff);
    adaptiveLightingConfig(min_light_th);

    uartPutString("Alarm ON time: ");
    buff = uartGetLine();
    uartPutString("\n");
    int alarm_on = atoi(buff);
    uartPutString("Alarm OFF time: ");
    buff = uartGetLine();
    uartPutString("\n");
    int alarm_off = atoi(buff);
    timedLightingConfig(alarm_on, alarm_off);

    uartPutString("Configuration Finished\n\n");
}

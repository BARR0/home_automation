/*
 * timed.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include "timed.h"

// TODO
#define DEFAULT_ON -1
#define DEFAULT_OFF -1

volatile enum status timedStatus = Off;
volatile int on = DEFAULT_ON;
volatile int off = DEFAULT_OFF;

void timedLightingInit(void)
{
    // TODO
}

void timedLightingOff(void)
{
    // TODO
    timedStatus = Off;
}

void timedLightingOn(void)
{
    // TODO
    timedStatus = On;
}

void timedLightingAuto(void)
{
    // TODO
    timedStatus = Auto;
}

void timedLightingConfig(int alarm_on, int alarm_off)
{
    on = alarm_on;
    off = alarm_off;
    if (timedStatus == Auto)
    {
        timedLightingAuto();
    }
}

int timedLightingGetAlarmOn(void)
{
    return on;
}

int timedLightingGetAlarmOff(void)
{
    return off;
}

enum status timedLightingStatus(void)
{
    return timedStatus;
}

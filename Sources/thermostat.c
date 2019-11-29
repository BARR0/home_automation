/*
 * thermostat.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include "thermostat.h"
#include "derivative.h"
#include "common.h"

// TODO
#define DEFAULT_MAX -1
#define DEFAULT_MIN -1

volatile enum status thermoStatus = Off;
volatile int min_th = DEFAULT_MIN;
volatile int max_th = DEFAULT_MAX;

void thermostatInit(void)
{
    // TODO
}

void thermostatOff(void)
{
    // TODO
    thermoStatus = Off;
}

void thermostatOn(void)
{
    // TODO
    thermoStatus = On;
}

void thermostatAuto(void)
{
    // TODO
    thermoStatus = Auto;
}

void thermostatConfig(int min_temp_th, int max_temp_th)
{
    min_th = min_temp_th;
    max_th = max_temp_th;
    if (thermoStatus == Auto)
    {
        thermostatAuto();
    }
}

int thermostatGetMinTemp(void)
{
    return min_th;
}

int thermostatGetMaxTemp(void)
{
    return max_th;
}

enum status thermostatStatus(void)
{
    return thermoStatus;
}

int thermostatTemperature(void)
{
    // TODO
    return -1;
}

/*
 * adaptive.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include "adaptive.h"

// TODO
#define DEFAULT_LIGHT -1

volatile enum status adaptiveStatus = Off;
volatile int light_th = DEFAULT_LIGHT;

void adaptiveLightingInit(void)
{
    // TODO
}

void adaptiveLightingOff(void)
{
    // TODO
    adaptiveStatus = Off;
}

void adaptiveLightingOn(void)
{
    // TODO
    adaptiveStatus = On;
}

void adaptiveLightingAuto(void)
{
    // TODO
    adaptiveStatus = Auto;
}

void adaptiveLightingConfig(int min_light_th)
{
    light_th = min_light_th;
    if (adaptiveStatus == Auto)
    {
        adaptiveLightingAuto();
    }
}

int adaptiveLightingGetMinLight(void)
{
    return light_th;
}

enum status adaptiveLightingStatus(void)
{
    return adaptiveStatus;
}

int adaptiveLightingPercentage(void)
{
    // TODO
    return -1;
}

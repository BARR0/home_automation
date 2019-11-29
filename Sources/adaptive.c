/*
 * adaptive.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include "adaptive.h"
#include "derivative.h"
#include "timed.h"
#include "common.h"

#define DEFAULT_LIGHT 50
#define ADC0_MAX 4100

volatile enum status adaptiveStatus = Off;
volatile int light_th = DEFAULT_LIGHT;

void adaptiveLightingInit(void)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; /* clock to PORTB */
    PORTB->PCR[1] = PORT_PCR_MUX(0);    /* PTE20 analog input */

    // Enable PTC2
    PORTE->PCR[23] = PORT_PCR_MUX(3);
    // Timer sets MCGIRCLK
    TPM2->SC = 0;                         // Disable timer
    TPM2->CONTROLS[1].CnSC = 0x20 | 0x09; // Edge-aligned pulse high
    TPM2->MOD = TPM2_B_MOD;               // Modulo register 60Hz
    TPM2->CONTROLS[1].CnV = 0;            // Set up channel to 50%
    TPM2->SC = TPM_SC_CMOD(1);            // Enable TPM2
}

void adaptiveLightingOff(void)
{
    TPM2->CONTROLS[1].CnV = 0;
    adaptiveStatus = Off;
}

void adaptiveLightingOn(void)
{
    TPM2->CONTROLS[1].CnV = TPM2_B_MOD;
    adaptiveStatus = On;
}

void adaptiveLightingAuto(void)
{
    adaptiveStatus = Auto;
}

void adaptiveLightingWork(void)
{
    int percentage;
    switch (adaptiveLightingStatus())
    {
    case Off:
        break;
    case On:
        break;
    case Auto:
        percentage = adaptiveLightingPercentage();
        if (percentage < light_th)
        {
            TPM2->CONTROLS[1].CnV = TPM2_B_MOD;
        }
        else
        {
            TPM2->CONTROLS[1].CnV = TPM2_B_MOD - percentage;
        }
        break;
    }
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
    ADC0->SC1[0] = 9; /* start conversion on channel 0 */
    while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
        ;                    /* wait for conversion complete */
    int result = ADC0->R[0]; /* read conversion result and clear COCO flag */
    return 100 - ((TPM2_B_MOD * result) / ADC0_MAX);
}

/*
 * timed.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include "timed.h"
#include "derivative.h"
#include "common.h"
#include "timer.h"
#include "uart.h"

#define DEFAULT_ON -1
#define DEFAULT_OFF -1

volatile enum status timedStatus = Off;
volatile int on = DEFAULT_ON;
volatile int off = DEFAULT_OFF;
volatile int alarm = 0;

void timedLightingInit(void)
{
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; /* clock to PORTE */
    PORTE->PCR[20] = PORT_PCR_MUX(0);   /* PTE20 analog input */
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;  /* clock to ADC0 */
    ADC0->SC2 &= ~ADC_SC2_ADTRG_MASK;   /* software trigger */
    /* clock div by 4, long sample time, single ended 12 bit, bus clock */
    ADC0->CFG1 = ADC_CFG1_ADIV(2) | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(1) | ADC_CFG1_ADICLK(0);

    // Enable PTC2
    PORTE->PCR[22] = PORT_PCR_MUX(3);
    SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK; // Enable clock to TPM0
    // Timer sets MCGIRCLK
    TPM2->SC = 0;                         // Disable timer
    TPM2->CONTROLS[0].CnSC = 0x20 | 0x09; // Edge-aligned pulse high
    TPM2->MOD = TPM2_B_MOD;               // Modulo register 60Hz
    TPM2->CONTROLS[0].CnV = 0;            // Set up channel to 50%
    TPM2->SC = TPM_SC_CMOD(1);            // Enable TPM2
}

void timedLightingOff(void)
{
    RTC->IER &= ~RTC_IER_TAIE_MASK;
    TPM2->CONTROLS[0].CnV = 0;
    timedStatus = Off;
}

void timedLightingOn(void)
{
    timedStatus = On;
}

void timedLightingAuto(void)
{
    int time = timerGetRTC();
    NVIC->ICPR = 0;
    RTC->SR &= ~RTC_SR_TCE_MASK;
    RTC->CR |= RTC_CR_SWR_MASK;
    RTC->CR &= ~RTC_CR_SWR_MASK;
    RTC->TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);
    RTC->TSR = time;
    RTC->TAR = on;
    RTC->SR |= RTC_SR_TCE_MASK;
    RTC->IER |= RTC_IER_TAIE_MASK;
    NVIC->ISER |= 1 << 20;
    RTC->SR &= ~RTC_SR_TAF_MASK;
    TPM2->CONTROLS[0].CnV = 0;
    timedStatus = Auto;
}

void timedLightingWork(void)
{
    switch (timedLightingStatus())
    {
    case Off:
        TPM2->CONTROLS[0].CnV = 0;
        break;
    case On:
        ADC0->SC1[0] = 0; /* start conversion on channel 0 */
        while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
            ;                    /* wait for conversion complete */
        int result = ADC0->R[0]; /* read conversion result and clear COCO flag */
        TPM2->CONTROLS[0].CnV = (TPM2_B_MOD * result) / ADC0_MAX;
        break;
    case Auto:
        if (alarm == 0)
        {
            TPM2->CONTROLS[0].CnV = 0;
        }
        else if (alarm == 1)
        {
            TPM2->CONTROLS[0].CnV = TPM2_B_MOD;
        }
        break;
    }
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

void RTC_Alarm_IRQHandler()
{
    if (!(RTC->SR & RTC_SR_TAF_MASK))
    {
        return;
    }
    if (alarm == 0)
    {
        RTC->TAR = off;
        alarm = 1;
    }
    else if (alarm == 1)
    {
        on += 60 * 60 * 24;
        off += 60 * 60 * 24;
        RTC->TAR = on;
        alarm = 0;
    }
}

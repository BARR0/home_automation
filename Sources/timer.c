/*
 * timer.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include "derivative.h"
#include "common.h"
#include "timer.h"

void timerInit(void)
{
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;                                        //Enable clock for TPM0
    SIM->SOPT2 = (SIM->SOPT2 & ~SIM_SOPT2_TPMSRC_MASK) | SIM_SOPT2_TPMSRC(3); //Select Clock source of TPM0 to be MCGIRCLK
    TPM0->SC = 0;                                                             //Set MCGIR clock divider to be 1 (no prescaler)
    TPM0->SC &= ~TPM_SC_CMOD(1);                                              //Stop timer TPM0

    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
    MCG->C1 |= MCG_C1_IRCLKEN_MASK;
    MCG->C2 &= ~(MCG_C2_IRCS_MASK);
    PORTC->PCR[1] |= PORT_PCR_MUX(0x1);
    SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);
    SIM->SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100);
    PORTC->PCR[3] |= PORT_PCR_MUX(0x5);
    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
    RTC->CR |= RTC_CR_SWR_MASK;
    RTC->CR &= ~RTC_CR_SWR_MASK;
    if (RTC->SR & RTC_SR_TIF_MASK)
    {
        RTC->TSR = 0x00000000;
    }
    RTC->TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);
    RTC->SR |= RTC_SR_TCE_MASK;
}

int timerGetRTC()
{
    return RTC->TSR;
}

void timerSetRTC(int time)
{
    RTC->CR = RTC_CR_SWR_MASK;
    RTC->CR &= ~RTC_CR_SWR_MASK;
    if (RTC->SR & RTC_SR_TIF_MASK)
    {
        RTC->TSR = 0x00000000;
    }
    RTC->TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);
    RTC->TSR = time;
    RTC->SR |= RTC_SR_TCE_MASK;
}

void timerSleep(int delay)
{
    TPM0->SC &= ~TPM_SC_CMOD(1);        //Stop TPM0
    TPM0->CNT = 0;                      //Set TPM0 counter to 0
    TPM0->SC |= TPM_SC_TOF_MASK;        //Clear TPM0 Timer Overflow Flag
    TPM0->SC |= TPM_SC_CMOD(1);         //Start TPM0
    TPM0->MOD = (32768 * delay) / 1000; //Set TPM0 Modulo to overflow every 1000ms
    while ((TPM0->SC & TPM_SC_TOF_MASK) == 0)
        ;                        //Loop until Timer Overflow Mask is set
    TPM0->SC |= TPM_SC_TOF_MASK; //Clear Timer Overflow Mask
    TPM0->SC |= TPM_SC_TOF_MASK; //Clear Timer Overflow Mask
    TPM0->SC &= ~TPM_SC_CMOD(1); //Stop timer TPM0
}

void timerStart1Sec(void)
{
    TPM0->SC &= ~TPM_SC_CMOD(1); //Stop TPM0
    TPM0->CNT = 0;               //Set TPM0 counter to 0
    TPM0->SC |= TPM_SC_TOF_MASK; //Clear TPM0 Timer Overflow Flag
    TPM0->SC |= TPM_SC_CMOD(1);  //Start TPM0
    TPM0->MOD = 32768;           //Set TPM0 Modulo to overflow every 1000ms
}

int timerIsSecDone(void)
{
    return !((TPM0->SC & TPM_SC_TOF_MASK) == 0);
}

void timerStop1Sec(void)
{
    TPM0->SC |= TPM_SC_TOF_MASK; //Clear Timer Overflow Mask
    TPM0->SC |= TPM_SC_TOF_MASK; //Clear Timer Overflow Mask
    TPM0->SC &= ~TPM_SC_CMOD(1); //Stop timer TPM0
}

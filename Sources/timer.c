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
    MCG->C2 |= 1;                                                             //Set MCGIRCLK to 4MHz in the MCG module
    MCG->C1 |= MCG_C1_IRCLKEN_MASK;                                           //Enable MCGIRCLK in the MCG module
    TPM0->SC |= 0x02;                                                         //Set TPM0 prescaler to be of 1MHz
    TPM0->SC &= ~TPM_SC_CMOD(1);                                              //Stop timer TPM0

    SIM->SOPT2 |= SIM_SOPT2_CLKOUTSEL(4);
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
    PORTC->PCR[3] |= PORT_PCR_MUX(5);

    SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
    SIM->SOPT1 &= ~SIM_SOPT1_OSC32KSEL_MASK;
    SIM->SOPT1 |= SIM_SOPT1_OSC32KSEL(0);
    // RTC->LR |= RTC_LR_SRL_MASK | RTC_LR_CRL_MASK;
    RTC->CR |= RTC_CR_SWR_MASK;
    RTC->CR &= ~RTC_CR_SWR_MASK;
    // RTC->TAR = 0xFFFFFFFF;
    RTC->CR |= RTC_CR_OSCE_MASK;
    timerSleep1Second();
    RTC->SR &= ~RTC_SR_TCE_MASK;
    RTC->SR &= ~RTC_SR_TIF_MASK;
    RTC->SR &= ~RTC_SR_TOF_MASK;
    RTC->TSR = 0xFF;
    RTC->SR |= RTC_SR_TCE_MASK;

    // RTC->SR |= RTC_SR_TIF_MASK;
    // RTC->SR |= RTC_SR_TOF_MASK;
    // RTC->TSR = 0xFF;
    // RTC->SR |= RTC_SR_TCE_MASK;
}

int timerGetRTC()
{
    // TODO
    return RTC->TSR;
}

void timerSetRTC(int time)
{
    RTC->SR &= ~RTC_SR_TCE_MASK;
    RTC->SR &= ~RTC_SR_TIF_MASK;
    RTC->SR &= ~RTC_SR_TOF_MASK;
    RTC->TSR = time;
    RTC->SR |= RTC_SR_TCE_MASK;
}

void timerSleep1Second(void)
{
    TPM0->SC &= ~TPM_SC_CMOD(1); //Stop TPM0
    TPM0->CNT = 0;               //Set TPM0 counter to 0
    TPM0->SC |= TPM_SC_TOF_MASK; //Clear TPM0 Timer Overflow Flag
    TPM0->SC |= TPM_SC_CMOD(1);  //Start TPM0
    TPM0->MOD = 1000;            //Set TPM0 Modulo to overflow every 1ms
    int i;
    for (i = 0; i < 1000; i++)
    {
        while ((TPM0->SC & TPM_SC_TOF_MASK) == 0)
            ;                        //Loop until Timer Overflow Mask is set
        TPM0->SC |= TPM_SC_TOF_MASK; //Clear Timer Overflow Mask
    }
    TPM0->SC |= TPM_SC_TOF_MASK; //Clear Timer Overflow Mask
    TPM0->SC &= ~TPM_SC_CMOD(1); //Stop timer TPM0
}

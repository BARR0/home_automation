/*
 * thermostat.c
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#include "thermostat.h"
#include "derivative.h"
#include "common.h"
#include "uart.h"
#include "timer.h"

// TODO
#define DEFAULT_MAX 30
#define DEFAULT_MIN 20

volatile enum status thermoStatus = Off;
volatile int min_th = DEFAULT_MIN;
volatile int max_th = DEFAULT_MAX;
volatile int fan_on = 0;
volatile int rtc_time = -1;
volatile int current_temp = 0;

void thermostatInit(void)
{
    // TODO
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; /* clock to PORTB */
    PORTB->PCR[2] = PORT_PCR_MUX(0);    /* PTE20 analog input */

    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    PORTA->PCR[5] = 0x100; /* make PTA3 pin as GPIO */
    PTA->PDDR |= 0x7F;     /* make PTD6-0 as output pins */
    GPIOA_PDOR &= ~(1 << 5);

    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
    NVIC->ICPR = 0;
    // configure PTD4 for interrupt
    PORTD->PCR[4] |= 0x00100;  /* make it GPIO  */
    PORTD->PCR[4] |= 0x00003;  /* enable pull-up */
    PTD->PDDR &= ~0x0010;      /* make pin input */
    PORTD->PCR[4] &= ~0xF0000; /* clear interrupt selection */
    PORTD->PCR[4] |= 0x90000;  /* enable both edge interrupt */
    NVIC->ISER |= 1 << 31;     /* enable INT30 (bit 30 of ISER[0]) */

    rtc_time = timerGetRTC();
    thermostatTemperature();
}

void thermostatOff(void)
{
    // TODO
    GPIOA_PDOR &= ~(1 << 5);
    thermoStatus = Off;
}

void thermostatOn(void)
{
    // TODO
    GPIOA_PDOR |= (1 << 5);
    thermoStatus = On;
}

void thermostatAuto(void)
{
    // TODO
    fan_on = 0;
    GPIOA_PDOR &= ~(1 << 5);
    thermoStatus = Auto;
}

void thermostatWork(void)
{
    switch (thermostatStatus())
    {
    case Off:
        break;
    case On:
        break;
    case Auto:
        if (fan_on == 0 && current_temp >= max_th)
        {
            fan_on = 1;
        }
        else if (fan_on == 1 && current_temp <= min_th)
        {
            fan_on = 0;
        }
        if (fan_on == 1)
        {
            GPIOA_PDOR |= (1 << 5);
        }
        else if (fan_on == 0)
        {
            GPIOA_PDOR &= ~(1 << 5);
        }
        break;
    }
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
    ADC0->SC1[0] = 12; /* start conversion on channel 0 */
    while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
        ;                    /* wait for conversion complete */
    int result = ADC0->R[0]; /* read conversion result and clear COCO flag */
    float voltage = ((float)result) / 1250.0;
    // return result;
    current_temp = (voltage - 0.0057) / 0.0096;
    return current_temp;
}

void PORTD_IRQHandler()
{
    if (rtc_time != timerGetRTC())
    {
        switch (thermostatStatus())
        {
        case Off:
            thermostatOn();
            break;
        case On:
            thermostatAuto();
            break;
        case Auto:
            thermostatOff();
            break;
        }
        rtc_time = timerGetRTC();
    }
    PORTD->ISFR = 0x0010; /* clear interrupt flag */
}

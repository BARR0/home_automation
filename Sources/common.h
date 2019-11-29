/*
 * common.h
 *
 *  Created on: Oct 15, 2019
 *      Author: lmaedanu
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "MKL25Z4.h"

volatile SIM_MemMapPtr SIM;
volatile MCG_MemMapPtr MCG;
volatile UART0_MemMapPtr UART0;
volatile PORT_MemMapPtr PORTA;
volatile PORT_MemMapPtr PORTB;
volatile PORT_MemMapPtr PORTC;
volatile PORT_MemMapPtr PORTD;
volatile PORT_MemMapPtr PORTE;
volatile GPIO_MemMapPtr PTA;
volatile GPIO_MemMapPtr PTB;
volatile GPIO_MemMapPtr PTC;
volatile GPIO_MemMapPtr PTD;
volatile NVIC_MemMapPtr NVIC;
volatile TPM_MemMapPtr TPM0;
volatile TPM_MemMapPtr TPM1;
volatile TPM_MemMapPtr TPM2;
volatile I2C_MemMapPtr I2C1;
volatile RTC_MemMapPtr RTC;
volatile ADC_MemMapPtr ADC0;

extern void common_init(void);

#endif /* COMMON_H_ */

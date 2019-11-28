/*
 * thermostat.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef THERMOSTAT_H_
#define THERMOSTAT_H_

#include "status.h"

#define THERMOSTAT_KEY 't'

void thermostatInit(void);

void thermostatOff(void);
void thermostatOn(void);
void thermostatAuto(void);

void thermostatConfig(int min_temp_th, int max_temp_th);
int thermostatGetMinTemp(void);
int thermostatGetMaxTemp(void);

enum status thermostatStatus(void);

#endif /* THERMOSTAT_H_ */

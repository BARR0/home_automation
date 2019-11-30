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

// Initialize the necessary registers:
// B2: Analog input (LM35)
// A5: Digital output (Fan)
// D4: Digital Input(Button)
void thermostatInit(void);

// Control Functions
void thermostatOff(void);
void thermostatOn(void);
void thermostatAuto(void);

// Main loop control function
void thermostatWork(void);

// Set the configuration values
void thermostatConfig(int min_temp_th, int max_temp_th);
// Return the Minimal Temperature Threshold
int thermostatGetMinTemp(void);
// Return the Maximum Termperature Threshold
int thermostatGetMaxTemp(void);

// Return the current status of the system
enum status thermostatStatus(void);

// Return the current temperature read from the LM35
int thermostatTemperature(void);

#endif /* THERMOSTAT_H_ */

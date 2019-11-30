/*
 * timed.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef TIMED_H_
#define TIMED_H_

#include "status.h"

#define TIMED_LIGHTING_KEY 'l'

// Initialize necessary registers:
// E20: Analog input (Potentiometer)
// E22: PWM output
void timedLightingInit(void);

// Control Functions
void timedLightingOff(void);
void timedLightingOn(void);
void timedLightingAuto(void);

// Main loop control function
void timedLightingWork(void);

// Set the configuration values
void timedLightingConfig(int alarm_on, int alarm_off);
// Get the Alarm ON time
int timedLightingGetAlarmOn(void);
// Get the Alarm OFF time
int timedLightingGetAlarmOff(void);

// Returns current status of the light
enum status timedLightingStatus(void);

#endif /* TIMED_H_ */

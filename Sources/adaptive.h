/*
 * adaptive.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef ADAPTIVE_H_
#define ADAPTIVE_H_

#include "status.h"

#define ADAPTIVE_LIGHTING_KEY 'a'

// Initialize the registers for Adaptive Lighting
// B1: Analog Input (Photoresistor)
// E23: PWM output (small LED)
void adaptiveLightingInit(void);

// Control Functions
void adaptiveLightingOff(void);
void adaptiveLightingOn(void);
void adaptiveLightingAuto(void);

// Main loop control function
void adaptiveLightingWork(void);

// Set the minimal threshold to turn light to the maximum
void adaptiveLightingConfig(int min_light_th);
// Return the current value of the threshold
int adaptiveLightingGetMinLight(void);

// Current status of the adaptive light
enum status adaptiveLightingStatus(void);

// Current light percentage read by Photoresistor
int adaptiveLightingPercentage(void);

#endif /* ADAPTIVE_H_ */

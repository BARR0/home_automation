/*
 * timed.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef TIMED_H_
#define TIMED_H_

#define TIMED_LIGHTING_KEY 'l'

void timedLightingInit(void);
void timedLightingOff(void);
void timedLightingOn(void);
void timedLightingAuto(void);
void timedLightingConfig(int alarm_on, int alarm_off);

#endif /* TIMED_H_ */

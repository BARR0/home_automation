/*
 * timed.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef TIMED_H_
#define TIMED_H_

void timeLightingInit(void);
void timeLightingOff(void);
void timeLightingOn(void);
void timeLightingAuto(void);
void timeLightingConfig(int alarm_on, int alarm_off);

#endif /* TIMED_H_ */

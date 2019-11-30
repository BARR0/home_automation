/*
 * timer.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef TIMER_H_
#define TIMER_H_

void timerInit(void);

int timerGetRTC();
void timerSetRTC(int time);

void timerSleep(int delay);

void timerStart1Sec(void);
int timerIsSecDone(void);
void timerStop1Sec(void);

#endif /* TIMER_H_ */

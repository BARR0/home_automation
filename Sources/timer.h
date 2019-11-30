/*
 * timer.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef TIMER_H_
#define TIMER_H_

// Initialize the necessary registers:
// C1: Clock OUT
// C3: Clock IN
void timerInit(void);

// Return current RTC time
int timerGetRTC();
// Set the current RTC
void timerSetRTC(int time);

// Sleep for this many milliseconds
void timerSleep(int delay);

// Control a 1 sec delay
void timerStart1Sec(void);
int timerIsSecDone(void);
void timerStop1Sec(void);

#endif /* TIMER_H_ */

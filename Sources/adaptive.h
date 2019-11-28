/*
 * adaptive.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef ADAPTIVE_H_
#define ADAPTIVE_H_

void adaptiveLightingInit(void);
void adaptiveLightingOff(void);
void adaptiveLightingOn(void);
void adaptiveLightingAuto(void);
void adaptiveLightingConfig(int min_light_th);

#endif /* ADAPTIVE_H_ */
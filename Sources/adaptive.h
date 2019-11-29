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

void adaptiveLightingInit(void);

void adaptiveLightingOff(void);
void adaptiveLightingOn(void);
void adaptiveLightingAuto(void);

void adaptiveLightingWork(void);

void adaptiveLightingConfig(int min_light_th);
int adaptiveLightingGetMinLight(void);

enum status adaptiveLightingStatus(void);

int adaptiveLightingPercentage(void);

#endif /* ADAPTIVE_H_ */

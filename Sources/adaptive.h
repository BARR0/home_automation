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
void adaptiveLightingConfig(int min_light_th);

enum status adaptiveLightingStatus(void);

#endif /* ADAPTIVE_H_ */

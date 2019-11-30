/*
 * config.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define CONFIG_KEY 'c'

// Prompt through UART to set all the control values:
//     RTC
//     Minimal Temperature Threshold
//     Maximum Temperature Threshold
//     Minimum Light Threshold
//     Alarm ON time
//     Alarm OFF time
void configUpdate(void);

#endif /* CONFIG_H_ */

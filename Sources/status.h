/*
 * status.h
 *
 *  Created on: Nov 27, 2019
 *      Author: andre
 */

#ifndef STATUS_H_
#define STATUS_H_

enum status
{
    Off,
    On,
    Auto
};


// Prints the Status of the following:
//     Date and time
//     Current Temperature
//     Min Temperature Threshold
//     Max Temperature Threshold
//     Fan status (ON/OFF)
//     Current Light intensity in percentage
//     Min Light Threshold
//     ADAPTIVE_LED status: ON/OFF/percentage
//     TIMED_LED status: ON/OFF/percentage
//     ALARM_ON time
//     ALARM_OFF time
void statusPrint(void);

#endif /* STATUS_H_ */

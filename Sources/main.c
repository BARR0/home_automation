/*
 * main implementation
 *
 */

#include "thermostat.h"
#include "adaptive.h"
#include "timed.h"
#include "timer.h"
#include "config.h"
#include "status.h"
#include "uart.h"

int main(void)
{
	thermostatInit();
	adaptiveLightingInit();
	timedLightingInit();
	timerInit();

	for (;;)
	{
		statusPrint();
		if (uartIsCharAvailable())
		{
			switch (uartGetCh())
			{
			case THERMOSTAT_KEY:
				switch (thermostatStatus())
				{
				case Off:
					thermostatOn();
					break;
				case On:
					thermostatAuto();
					break;
				case Auto:
					thermostatOff();
					break;
				}
				break;
			case ADAPTIVE_LIGHTING_KEY:
				switch (adaptiveLightingStatus())
				{
				case Off:
					adaptiveLightingOn();
					break;
				case On:
					adaptiveLightingAuto();
					break;
				case Auto:
					adaptiveLightingOff();
					break;
				}
				break;
			case TIMED_LIGHTING_KEY:
				switch (timedLightingStatus())
				{
				case Off:
					timedLightingOn();
					break;
				case On:
					timedLightingAuto();
					break;
				case Auto:
					timedLightingOff();
					break;
				}
				break;
			case CONFIG_KEY:
				configUpdate();
				break;
			}
		}
		timerSleep1Second();
	}

	return 0;
}

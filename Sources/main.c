/*
 * main implementation: use this 'C' sample to create your own application
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
				break;
			case ADAPTIVE_LIGHTING_KEY:
				break;
			case TIMED_LIGHTING_KEY:
				break;
			case CONFIG_KEY:
				break;
			}
		}
		timerSleep1Second();
	}

	return 0;
}

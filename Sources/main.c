/*
 * main implementation
 *
 */

#include "thermostat.h"
#include "adaptive.h"
#include "timed.h"
#include "timer.h"
#include "config.h"
#include "common.h"
#include "status.h"
#include "uart.h"

int main(void)
{
    common_init();
    timerInit();
    uartInit();
    timedLightingInit();
    adaptiveLightingInit();
    thermostatInit();

    for (;;)
    {
        statusPrint();
        timerStart1Sec();
        while (!timerIsSecDone())
        {
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
            timedLightingWork();
            adaptiveLightingWork();
            thermostatWork();
        }
        timerStop1Sec();
    }

    return 0;
}

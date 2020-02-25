#include "FreeRTOS.h"
#include <task.h>
#include <timers.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Communication/Console.h"
#include "../../BSP/LEDs/LEDs.h"

/*
CASE: Create timer that will steer LED dimming, and other timer that will change dimming every 1 s. Both timers are autoreload and has id.
*/

/*
Peripherial used: leds 
*/

typedef enum TimerType_e{
    eDimmingTimer = 0,
    eSteeringTimer
}TimerType_t;

#define dPWM_MaxDuty  (10)

#if (dTestSoftwareTimersId == 1)

/* Step1: create timers handles */
TimerHandle_t dimmingTimer;
TimerHandle_t steerTimer;

/* Step2: create timer callback function*/
void timerCallback(TimerHandle_t timer);

/*Step3: initialize function*/
void softwareTimerExampleWithIdInit(void)
{
    consoleSend((unsigned char*)"ID software timer example! ");

    /* Create timers */
    dimmingTimer = xTimerCreate("tim1", pdMS_TO_TICKS(100), pdTRUE, (void*)eDimmingTimer, timerCallback);
    steerTimer = xTimerCreate("tim2", pdMS_TO_TICKS(2000), pdTRUE, (void*)eSteeringTimer, timerCallback);

    /* Start timers */
    xTimerStart(dimmingTimer, 10);
    xTimerStart(steerTimer, 10);
}

void timerCallback(TimerHandle_t timer)
{
    static uint16_t pwmDuty = 2;
    static uint16_t dutyCount = 0;
    
    /*Distinguish, by id, if it is Ldimming or steering timer */
    TimerType_t timerType = (TimerType_t)pvTimerGetTimerID(timer);

    if (timerType == eDimmingTimer)
    {
        /* If dimmer timer was called just compare duty and steer leds */
        dutyCount++;
        if (dutyCount == pwmDuty)
        {
            LedOff(eLed3);
        }
        else if (dutyCount == dPWM_MaxDuty)
        {
            LedOn(eLed3);
            dutyCount = 0;
        }
    }

    if (timerType == eSteeringTimer)
    {
        /* IF steering timer was called increase pwm duty to increase light intensity */
        pwmDuty++;
        if (pwmDuty >= dPWM_MaxDuty)
        {
            pwmDuty = 0;
        }
    }
}

#endif
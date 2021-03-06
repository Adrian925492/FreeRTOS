#include "FreeRTOS.h"
#include <task.h>
#include <timers.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Communication/Console.h"
#include "../../BSP/LEDs/LEDs.h"

/*
CASE: Create timer that will toggle LED every 500 ms. Timer is type autoreload, with no ID usage.
*/


/*
Peripherial used: leds 
*/

#if (dTestSimpleTimers == 1)

/* Step1: create timer handle */
TimerHandle_t timer;

/* Step2: create timer callback function*/
void timerLedCallback(TimerHandle_t timer);

/*Step3: initialize function*/
void softwareTimerExampleInit(void)
{
    vTaskSuspendAll();
    consoleSend((unsigned char*)"Simple software timer example! ");
    xTaskResumeAll();

    /* Create timer */
    timer = xTimerCreate("tim1", pdMS_TO_TICKS(500), pdTRUE, 0, timerLedCallback);

    /* Start timer */
    xTimerStart(timer, 10);
}

void timerLedCallback(TimerHandle_t timer)
{
    taskENTER_CRITICAL();
    LedToggle(eLed2);
    taskEXIT_CRITICAL();        //Pre emption avoided by entering interrupt service routine in critical section
}
#endif
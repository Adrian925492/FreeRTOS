#include "FreeRTOS.h"
#include <task.h>
#include <event_groups.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Communication/Console.h"
#include "../../BSP/LEDs/LEDs.h"
#include "../../BSP/Button/Button.h"

#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim10;

/*
CASE: We have task for button check and timer with interrupt. Event group collects two events: timer interrupt
        and button press. After both occured, the third task has to toggle the LED. When button pressed, it starts the timer.
        Effect should be toggling led with some delay time after pressing button.
*/

/*
Peripherial used: leds, timer, button, console
*/


#if (dTestEventGroups == 1)

/* Define which bits in group are responsible for what */
#define buttonEvent ((1<<0))
#define timerEvent  ((1<<1))

/* step1: create event group handle */
EventGroupHandle_t eventGroup;

/* Step2: create timer callback function*/
void timerCallback(TimerHandle_t timer);

/* step 3: create tasks handles */
void vButtonCheckTask(void* pvParameters);
void vLedChangeStateTask(void* pvParameters);

/* Step 4: event group example init */
void eventGroupsExampleTest(void)
{   
    vTaskSuspendAll();
    consoleSend((unsigned char*)"Simple event group example! ");
    xTaskResumeAll();

    /* Prepare LED */
    LedOff(eLed5);

    /* Prepare event group */
    eventGroup = xEventGroupCreate();

    /* Create led task */
    xTaskCreate(vLedChangeStateTask, "BS_T1", 64, NULL, 3, NULL);

    /* Create button state task */
    xTaskCreate(vButtonCheckTask, "BS_T2", 64, NULL, 2, NULL);
}

void vLedChangeStateTask(void* pvParameters)
{
    for (;;)
    {
        xEventGroupWaitBits(eventGroup, timerEvent | buttonEvent, pdTRUE, pdTRUE, portMAX_DELAY);
        LedToggle(eLed5);
        
    }
}

void vButtonCheckTask(void* pvParameters)
{
    for (;;)
    {
        if(button_IsPressed())
        {
            while(button_IsPressed());   //Prevent lot of pressing events
            xEventGroupSetBits(eventGroup, buttonEvent); //Set button event bits in event group
            HAL_TIM_Base_Start_IT(&htim10);     //Start timer
        }
    }
}

void timer10Callback(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xEventGroupSetBitsFromISR(eventGroup, timerEvent, &xHigherPriorityTaskWoken);
    HAL_TIM_Base_Stop_IT(&htim10);
}
#endif
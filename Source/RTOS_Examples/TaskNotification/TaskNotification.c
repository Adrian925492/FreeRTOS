#include "FreeRTOS.h"
#include <task.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Button/Button.h"
#include "../../BSP/LEDs/LEDs.h"

/*
CASE: Create two tasks that will synchronize by notification. One task will check button state. When pressed
it will notify other tash to toggle the led state.
*/

/*
Peripherial used: leds, buttons
*/

#if (dTestTaskNotifications == 1)

/* Step 1: create tasks */
void vLed_ChangeStateTask(void* pvParameters);
void vButton_CheckTask(void* pvParameters);

/* step 2: create task handles */
TaskHandle_t ledTask;
TaskHandle_t btnTask;

/* Step 2: Init */
void taskNotificationsInit(void)
{
    /* Initialize the Led */
    LedOff(eLed4);

    /* Create led task */
    xTaskCreate(vLed_ChangeStateTask, "LS_T1", 64, NULL, 4, &ledTask);

    /* Create button state task */
    xTaskCreate(vButton_CheckTask, "LS_T2", 64, NULL, 2, &btnTask);
}

void vLed_ChangeStateTask(void* pvParameters)
{
    for (;;)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); //Wait for notificaton. DO not care about notification value - clear it after receive notification.
        LedToggle(eLed4);
    }
}

void vButton_CheckTask(void* pvParameters)
{
    for (;;)
    {
        if(button_IsPressed())
        {
            while(button_IsPressed());   //Prevent lot of pressing events
            xTaskNotifyGive(ledTask);    // Give notification to Led task    
        }
    }
}
#endif
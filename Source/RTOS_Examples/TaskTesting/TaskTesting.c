#include "FreeRTOS.h"
#include <task.h>

#include "../RTOS_Examples.h"
#include "../../BSP/LEDs/LEDs.h"
#include "stm32f4xx_hal.h"
#include "main.h"

    /* CASE 1: Both tasks has same priority, but both can be blocked by delay function */

    /* In case of blocking delay would be used (ex. HAL_Delay()) in both tasks, as long as 
    both tasks would have the same priority, the time slicing would be used and task would be
    switched one by one. hanging priority of any of the 2 tasks would cause tkat other task will
    never be reached */

/*
Peripherial used: leds: nucleo, 2 ext. leds
*/

#if (taskExample == 1)
#define dBlinkPeriod_ms (1000)

/* Step1: Initialize task functions */
void vBlinkyTask(void *pvParaeters);
void vLedTask1(void* pvParameters);

/* Step 2: call example init function */
void TaskTestingInit(void)
{
    xTaskCreate(vBlinkyTask, "BlinkyTask", 32, (void*)dBlinkPeriod_ms, 2, NULL);
    xTaskCreate(vLedTask1, "LEDtask1", 128, NULL, 2, NULL);
}

void vBlinkyTask(void* pvParameters)
{
    for(;;)
    {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        vTaskDelay(pdMS_TO_TICKS((int)(pvParameters)));
    }
}

void vLedTask1(void* pvParameters)
{
    for(;;)
    {
        //LED effect, only 1st 2 leds
        for (uint16_t id = 0; id < (uint16_t)(2); ++id)
        {
            LedToggle(id);
            vTaskDelay(500);
        }
    }
}
#endif
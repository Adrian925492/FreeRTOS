#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "BSP/BSP.h"
#include "BSP/LEDs/LEDs.h"

#define dBlinkPeriod_ms (1000)

void vIdleTask(void *pvParameters);
void vBlinkyTask(void *pvParaeters);

void vIdleTask(void *pvParameters)
{
    for(;;)
    {
        //Idle task: do nothing
    }
}

void vBlinkyTask(void* pvParameters)
{
    for(;;)
    {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        //HAL_Delay(1000);
        vTaskDelay(pdMS_TO_TICKS((int)(pvParameters)));
    }
}

void vLedTask1(void* pvParameters)
{
    for(;;)
    {
            //LED effect
        for (uint16_t id = 0; id < (uint16_t)(dLedAmount); ++id)
        {
            LedToggle(id);
            vTaskDelay(500);
        }
    }
}

void os_init(void)
{
    Bsp_Init();
}

void os_start(void)
{
    xTaskCreate(vIdleTask, "IdleTask", 32, NULL, 0, NULL);

    /* CASE 1: Both tasks has same priority, but both can be blocked by delay function */

    /* In case of blocking delay would be used (ex. HAL_Delay()) in both tasks, as long as 
    both tasks would have the same priority, the time slicing would be used and task would be
    switched one by one. hanging priority of any of the 2 tasks would cause tkat other task will
    never be reached */
    xTaskCreate(vBlinkyTask, "BlinkyTask", 32, dBlinkPeriod_ms, 2, NULL);
    xTaskCreate(vLedTask1, "LEDtask1", 128, NULL, 2, NULL);


    vTaskStartScheduler();

    for(;;);   //Shall be never reached
}

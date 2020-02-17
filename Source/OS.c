#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "BSP/BSP.h"

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
        vTaskDelay(pdMS_TO_TICKS((int)(pvParameters)));
    }
}

void os_init(void)
{
    Bsp_Init();
}

void os_start(void)
{
    xTaskCreate(vIdleTask, "IdleTask", 32, NULL, 0, NULL);
    xTaskCreate(vBlinkyTask, "BlinkyTask", 128, dBlinkPeriod_ms, 1, NULL);
    vTaskStartScheduler();

    for(;;);   //Shall be never reached
}

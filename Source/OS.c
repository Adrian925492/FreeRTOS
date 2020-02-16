#include "stm32f4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"

void vIdleTask(void *pvParameters);


void vIdleTask(void *pvParameters)
{
    for(;;)
    {
        //Idle task: do nothing
    }
}

void os_init(void)
{

}

void os_start(void)
{
    xTaskCreate(vIdleTask, "IdleTask", 32, NULL, 0, NULL);
    vTaskStartScheduler();

    for(;;);   //Shall be never reached
}

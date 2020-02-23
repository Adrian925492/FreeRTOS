#include "FreeRTOS.h"
#include "task.h"

#include "RTOS_Examples/RTOS_Examples.h"
#include "BSP/BSP.h"

void vIdleTask(void *pvParameters);;

void vIdleTask(void *pvParameters)
{
    for(;;)
    {
        //Idle task: do nothing
    }
}

void os_init(void)
{
    Bsp_Init();
    exampleInit();
}

void os_start(void)
{
    xTaskCreate(vIdleTask, "IdleTask", 32, NULL, 0, NULL);      //Explicit creation of Idle task

    vTaskStartScheduler();

    for(;;);   //Shall be never reached
}

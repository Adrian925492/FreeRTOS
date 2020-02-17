#include "LEDs/LEDs.h"
#include <FreeRTOS.h>
#include <task.h>
#include "BSP.h"

void Bsp_Init()
{
    LedsInit();
    xTaskCreate(Bsp_Perform, "BSP_task", 128, NULL, 1, NULL);
}

void Bsp_Perform()
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
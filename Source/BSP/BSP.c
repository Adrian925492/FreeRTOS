#include "LEDs/LEDs.h"
#include "Communication/Console.h"
#include <FreeRTOS.h>
#include <task.h>
#include "BSP.h"

void Bsp_Init()
{
    LedsInit();
    Console_Init();
    Console_Perfrom();
    xTaskCreate(Bsp_Perform, "BSP_task", 128, NULL, 1, NULL);
}

void Bsp_Perform()
{
    for(;;)
    {

    }
}
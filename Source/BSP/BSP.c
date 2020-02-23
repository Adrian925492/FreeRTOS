#include "LEDs/LEDs.h"
#include "Communication/Console.h"
#include "BSP.h"

void Bsp_Init()
{
    LedsInit();
    Console_Init();
}

void Bsp_Perform()
{

}
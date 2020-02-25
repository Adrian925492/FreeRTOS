#include "LEDs/LEDs.h"
#include "Communication/Console.h"
#include "Button/Button.h"
#include "BSP.h"

void Bsp_Init()
{
    LedsInit();
    Console_Init();
    buttonInit();
}

void Bsp_Perform()
{
}
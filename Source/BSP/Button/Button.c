#include "Button.h"
#include "main.h"
#include "stm32f4xx_hal.h"

void buttonInit()
{

}

bool button_IsPressed(void)
{
    if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
    {
        return true;
    }
    return false;
}
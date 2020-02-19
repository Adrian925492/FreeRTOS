#include "stm32f4xx_hal.h"
#include "Console.h"

extern UART_HandleTypeDef huart2;

void Console_Init()
{

}

void Console_Perfrom()
{
    char data[] = "Hello world";
    HAL_UART_Transmit(&huart2, data, 11, 10);
}
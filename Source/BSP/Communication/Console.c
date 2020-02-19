#include "stm32f4xx_hal.h"
#include "Console.h"

extern UART_HandleTypeDef huart2;

void Console_Init()
{
    unsigned char data[] = "Hello world\n";
    HAL_UART_Transmit(&huart2, data, 12, 10);
}

void Console_Perfrom()
{

}
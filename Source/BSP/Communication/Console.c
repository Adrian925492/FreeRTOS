#include "stm32f4xx_hal.h"
#include "Console.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Queue example HERE */

extern UART_HandleTypeDef huart2;

QueueHandle_t consoleQueue; 

void Console_Init()
{
    unsigned char data[] = "Hello world\n\n";
    HAL_UART_Transmit(&huart2, data, 13, 10);

    consoleQueue = xQueueCreate(1, sizeof(char));
}

void Console_Perfrom()
{

}
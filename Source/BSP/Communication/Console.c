#include "stm32f4xx_hal.h"
#include "Console.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Queue example HERE */

/* CASE QUEUE:
How it works:

We have 2 tasks: sender and receiver. If receiver gets any byte from UART, it keeps it into the queue.
Sender waits for anything in the queue. As queue is empty, the sender keeps in blocked state. 
As sender has higher priority than receiver, occuring anything in queue would cause preemption of any other tasks, 
and sender will immidietly send out the sign back via uart. */

extern UART_HandleTypeDef huart2;

QueueHandle_t consoleQueue; 

void vReceiverTask(void* pvParameters);
void vSenderTask(void* pvParameters);


void Console_Init()
{
    unsigned char data[] = "Hello world\n\n";
    HAL_UART_Transmit(&huart2, data, 13, 10);

    consoleQueue = xQueueCreate(1, sizeof(char));

    xTaskCreate(vSenderTask, "consoleSenderTask", 64, NULL, 3, NULL);
    xTaskCreate(vReceiverTask, "consoleReceiverTask", 64, NULL, 2, NULL);
}

void Console_Perfrom()
{

}

void vReceiverTask(void* pvParameters)
{
    /* After receiving byte by UART it gives it into queue so the byte could be sent back by sender task */
    for(;;)
    {
        unsigned char data = 0;
        HAL_UART_Receive(&huart2, &data, 1, 0);
        if (data != 0)
        {
            xQueueSendToBack(consoleQueue, &data, 0);
        }
    }
}

void vSenderTask(void* pvParameters)
{
    for(;;)
    {
        unsigned char data = 0;
        xQueueReceive(consoleQueue, &data, portMAX_DELAY);
        HAL_UART_Transmit(&huart2, &data, 1, 0);
    }
}
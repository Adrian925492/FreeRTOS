#include "stm32f4xx_hal.h"
#include "Console.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Queue example HERE */

//#define dUseDirectQueue  /* CASE1: data are copied directly to the queue */
//#define dUsePointerQueue   /* CASE2: only pointers to buffers are queued. See case 2 for more info (below). Good for large amount of data*/
#define dUseQueueSet       /* CASE3: example of queue set usage. */

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


void Console_Perfrom()
{
}

#ifdef dUseDirectQueue
/*
CASE1: Data are directly copied into a queue
*/
void Console_Init()
{
    unsigned char data[] = "Hello world\n\n\r";
    HAL_UART_Transmit(&huart2, data, 13, 10);

    consoleQueue = xQueueCreate(1, sizeof(char));

    xTaskCreate(vSenderTask, "consoleSenderTask", 64, NULL, 3, NULL);
    xTaskCreate(vReceiverTask, "consoleReceiverTask", 64, NULL, 2, NULL);
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
#endif

#ifdef dUsePointerQueue
/*
CASE2: If we have large amount of data it is good idea to queue pointer to data buffers instead of copying the data
to queue itself. It would save RAM memory and time resources, beacouse we have no need to copy */
unsigned char dataBuffer[30];

void Console_Init()
{
    unsigned char data[] = "Hello world\n\n\r";
    HAL_UART_Transmit(&huart2, data, 13, 10);

    consoleQueue = xQueueCreate(1, sizeof(char *));

    xTaskCreate(vSenderTask, "consoleSenderTask", 64, NULL, 3, NULL);
    xTaskCreate(vReceiverTask, "consoleReceiverTask", 64, NULL, 2, NULL);
}

void vReceiverTask(void* pvParameters)
{
    /* After receiving byte by UART it gives it into queue so the byte could be sent back by sender task */
    static uint16_t i = 0;
    unsigned char *pcStringToSend;
    for(;;)
    {
        unsigned char data = 0;
        HAL_UART_Receive(&huart2, &data, 1, 0);
        
        if (data != 0)
        {
            dataBuffer[i] = data;   //Add sign to buffer
            i++;

            if (data == 0x0D)  //If enter sign
            {
                pcStringToSend = dataBuffer;
                xQueueSendToBack(consoleQueue, &pcStringToSend, 0);  //Queue pointer to data buffer
                i = 0;
            }
        }
    }
}

void vSenderTask(void* pvParameters)
{
    for(;;)
    {
        unsigned char* data = NULL;
        uint16_t nrOfBytes = 0;
        
        xQueueReceive(consoleQueue, &data, portMAX_DELAY);
        
        while(data[nrOfBytes] != 0)
        {
            nrOfBytes++;
        }
        
        HAL_UART_Transmit(&huart2, data, nrOfBytes, 10);
        
        for(uint16_t i = 0; i < nrOfBytes; i++)     //Empty buffer after sending
        {
            data[i] = 0;
        }
    }
}
#endif

#ifdef dUseQueueSet
/*
CASE3: If we have 2 or more queues that has to be serviced by task, and we do not want to use pooling each queue, we can use
queue set. The set contains defined number of queues (or semaphores) and returns handler for queue or semaphore that had received some 
data. Each receive causes sending queue handler to ueue set. */

unsigned char tickMessage[] = "tick\n";

QueueSetHandle_t set;
QueueHandle_t tickSendQueue;

void vTickTask(void* pvParameters);

void Console_Init()
{
    unsigned char data[] = "Hello world\n\n\r";
    HAL_UART_Transmit(&huart2, data, 13, 10);

    consoleQueue = xQueueCreate(1, sizeof(char));
    tickSendQueue = xQueueCreate(1, sizeof(char));

    set = xQueueCreateSet(2);

    xQueueAddToSet(consoleQueue, set);
    xQueueAddToSet(tickSendQueue, set);

    xTaskCreate(vSenderTask, "T1", 128, NULL, 3, NULL);
    xTaskCreate(vReceiverTask, "T2", 128, NULL, 2, NULL);
    xTaskCreate(vTickTask, "tick console task", 128, NULL, 2, NULL);
}

void vTickTask(void* pvParameters)
{
    unsigned char tick = 'T';
    /* Every 1 second sends pointer to string "tick" to the tick queue */
    for (;;)
    {
        xQueueSendToBack(tickSendQueue, &tick, 0);
        vTaskDelay(1000);
    }
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
    QueueHandle_t xQueueThatContainsData;
    char *pcReceivedString;

    for(;;)
    {
        xQueueThatContainsData =  (QueueHandle_t )xQueueSelectFromSet(set, portMAX_DELAY);
        xQueueReceive( xQueueThatContainsData, &pcReceivedString, 0 );

        HAL_UART_Transmit(&huart2, &pcReceivedString, 1, 0);
        HAL_UART_Transmit(&huart2, (unsigned char*)"\n\r", 2, 1);
    }
}
#endif
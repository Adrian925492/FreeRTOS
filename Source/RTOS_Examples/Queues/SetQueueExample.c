#include "FreeRTOS.h"
#include <task.h>
#include <queue.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Communication/Console.h"

/* CASE SET QUEUE:
If we have 2 or more queues that has to be serviced by task, and we do not want to use pooling each queue, we can use
queue set. The set contains defined number of queues (or semaphores) and returns handler for queue or semaphore that had received some 
data. Each receive causes sending queue handler to ueue set. */

#if (dTestQueueSet == 1)

/* Step1: create handler for queues and set*/
QueueHandle_t consoleQueue; 
QueueHandle_t tickSendQueue;
QueueSetHandle_t set;

/* Step2: create taks functions declarations*/
void vReceiverTask(void* pvParameters);
void vSenderTask(void* pvParameters);
void vTickTask(void* pvParameters);

/* Step 3: call example init function */
void setQueueExampleInit(void)
{
    consoleSend((unsigned char*)"Set queue example! ");

    /* Create sender - receiver queue */
    consoleQueue = xQueueCreate(1, sizeof(char));
    tickSendQueue = xQueueCreate(1, sizeof(char));

    /* Create tick queue */
    set = xQueueCreateSet(2);

    /* Add queues to set */
    xQueueAddToSet(consoleQueue, set);
    xQueueAddToSet(tickSendQueue, set);

    /* Create sender and receiver tasks */
    xTaskCreate(vSenderTask, "T1", 64, NULL, 3, NULL);
    xTaskCreate(vReceiverTask, "T2", 64, NULL, 2, NULL);

    /* Create tick task */
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
        consoleRead(&data, 1, 0);
        if (data != 0)
        {
            xQueueSendToBack(consoleQueue, &data, 0);
        }
    }
}

void vSenderTask(void* pvParameters)
{
    QueueHandle_t xQueueThatContainsData;
    
    for(;;)
    {
        unsigned char data = 0;
        xQueueThatContainsData =  (QueueHandle_t )xQueueSelectFromSet(set, portMAX_DELAY);
        xQueueReceive( xQueueThatContainsData, &data, 0 );
        consoleSendByte(&data);
    }
}

#endif
#include "FreeRTOS.h"
#include <task.h>
#include <queue.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Communication/Console.h"

/*
CASE: Gatekeeper test. We have 2 tasks, one periodically prints out to the console, other one also, but with the same time. The
console is protected by the gatekeeper task (3rd task) to not avoid to access the console by 2 tasks at once. Both tasks has the same priority,
but gatekeeper has higher priority. The resource (console) is accesed only by 1 task, so we have no problem with shared resource.
*/

/*
Peripherial used: console 
*/

#if (dUseGatekeeperTask == 1)

/* step 1: create gatekeeper task handler */
void vGatekeeperTask(void* pvParameters);

/* Step 2: create tasks handlers */
void vSenderTask(void* pvParameters);
void vTickTask(void* pvParameters);

/* Step3: queue handler create */
QueueHandle_t gatekeeperQueue;

/* Stap 4: gatekeeper init */
void gatekeeperTaskExampleInit(void)
{
    vTaskSuspendAll();
    consoleSend((unsigned char*)"Gatekeeper task example! ");
    xTaskResumeAll();  //Suspend and resume scheduler - to not allow to preempt writing by other task!

    /* Create gatekeeper queue */
    gatekeeperQueue = xQueueCreate(5, sizeof(unsigned char));

    /* Create gatekeeper task */
    xTaskCreate(vGatekeeperTask, "TM1", 128, NULL, 3, NULL);    //Gatekeeper has higher priority!

    /* Create tasks */
    xTaskCreate(vSenderTask, "TM1", 128, NULL, 2, NULL);
    xTaskCreate(vTickTask, "TM2", 128, NULL, 2, NULL);
}


void vTickTask(void* pvParameters)
{
    unsigned char byte = 'B';
    for (;;)
    {
        vTaskDelay(2000);       //Every 1000 ms send something
        xQueueSendToFront(gatekeeperQueue, &byte, portMAX_DELAY);
    }
}

void vSenderTask(void* pvParameters)
{  
    unsigned char byte = 'A';
    for(;;)
    {
        vTaskDelay(2010);       //Every 1000  ms send something
        xQueueSendToFront(gatekeeperQueue, &byte, portMAX_DELAY);
    }
}

void vGatekeeperTask(void* pvParameters)
{
    unsigned char byteToSend;
    for (;;)
    {
        xQueueReceive(gatekeeperQueue, &byteToSend, portMAX_DELAY);
        consoleSend((unsigned char*)" Gatekeeper tsk: received byte:  ");
        consoleSendByte(&byteToSend);
        consoleSend((unsigned char*)"\n\n");
    }
}

#endif
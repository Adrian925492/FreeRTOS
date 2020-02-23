#include "FreeRTOS.h"
#include <task.h>
#include <queue.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Communication/Console.h"

/* CASE QUEUE:
How it works:

We have 2 tasks: sender and receiver. If receiver gets any byte from UART, it keeps it into the queue.
Sender waits for anything in the queue. As queue is empty, the sender keeps in blocked state. 
As sender has higher priority than receiver, occuring anything in queue would cause preemption of any other tasks, 
and sender will immidietly send out the sign back via uart.

Data are directly copied into a queue
*/

#if (dTestSimpleQueue == 1)

/* Step1: create handler for queue */
QueueHandle_t queue; 

/* Step2: create taks functions declarations*/
void vReceiverTask(void* pvParameters);
void vSenderTask(void* pvParameters);

/* Step 3: call example init function */
void simpleQueueExampleInit(void)
{
    consoleSend((unsigned char*)"Simple queue example! ");

    /* Create queue */
    queue = xQueueCreate(1, sizeof(char));

    /* Create sender and receiver tasks */
    xTaskCreate(vSenderTask, "T1", 64, NULL, 3, NULL);
    xTaskCreate(vReceiverTask, "T2", 64, NULL, 2, NULL);
}

/* Step4: implement receive and send task */
void vReceiverTask(void* pvParameters)
{
    /* After receiving byte by UART it gives it into queue so the byte could be sent back by sender task */
    for(;;)
    {
        unsigned char data = 0;
        consoleRead(&data, 1, 0);
        if (data != 0)
        {
            xQueueSendToBack(queue, &data, 0);
        }
    }
}

void vSenderTask(void* pvParameters)
{
    for(;;)
    {
        unsigned char data = 0;
        xQueueReceive(queue, &data, portMAX_DELAY);
        consoleSendByte(&data);
    }
}



#endif


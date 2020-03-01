#include "FreeRTOS.h"
#include <task.h>
#include <queue.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Communication/Console.h"

/* CASE POINTER QUEUE:
If we have large amount of data it is good idea to queue pointer to data buffers instead of copying the data
to queue itself. It would save RAM memory and time resources, beacouse we have no need to copy.

Only pointers to buffers are queued. See case 2 for more info (below). Good for large amount of data.
*/

/*
Peripherial used: console 
*/

#if (dTestPointereQueue == 1)

/* Step1: create handler for queue and data buffer*/
QueueHandle_t queue; 
unsigned char dataBuffer[30];

/* Step2: create taks functions declarations*/
void vReceiverTask(void* pvParameters);
void vSenderTask(void* pvParameters);

/* Step 3: create functions for data buffer servicing */
static inline void clearBuffer(unsigned char* pBuffer)
{
    uint16_t byteNr = 0;
    while (pBuffer[byteNr] != 0)
    {
        pBuffer[byteNr] = 0;
        ++byteNr;
    }
}

/* Step 4: call example init function */
void pointerQueueExampleInit(void)
{
    vTaskSuspendAll();
    consoleSend((unsigned char*)"Pointer queue example! ");
    xTaskResumeAll();  //Suspend and resume scheduler - to not allow to preempt writing by other task!

    /* Create queue */
    queue = xQueueCreate(1, sizeof(char));

    /* Create sender and receiver tasks */
    xTaskCreate(vSenderTask, "T1", 64, NULL, 3, NULL);
    xTaskCreate(vReceiverTask, "T2", 64, NULL, 2, NULL);
}

/* Step5: implement receive and send task */
void vReceiverTask(void* pvParameters)
{
    /* After receiving byte by UART it gives it into queue so the byte could be sent back by sender task */
    static uint16_t buffPos = 0;
    unsigned char *pcStringToSend;
    for(;;)
    {
        unsigned char data = 0;
        consoleRead(&data, 1, 0);
        
        if (data != 0)
        {
            dataBuffer[buffPos] = data;         //Add sign to buffer
            buffPos++;

            if (data == 0x0D)                   //If enter sign
            {
                pcStringToSend = dataBuffer;
                xQueueSendToBack(queue, &pcStringToSend, 0);  //Queue pointer to data buffer
                buffPos = 0;
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
        
        xQueueReceive(queue, &data, portMAX_DELAY);
        
        // while(data[nrOfBytes] != 0)
        // {
        //     nrOfBytes++;
        // }
        
        // HAL_UART_Transmit(&huart2, data, nrOfBytes, 10);
        
        consoleSend(data);
        clearBuffer(data);

        // for(uint16_t i = 0; i < nrOfBytes; i++)     //Empty buffer after sending
        // {
        //     data[i] = 0;
        // }
    }
}
#endif
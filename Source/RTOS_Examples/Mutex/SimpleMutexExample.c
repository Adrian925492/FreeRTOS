#include "FreeRTOS.h"
#include <task.h>
#include <semphr.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Communication/Console.h"

/*
CASE: Simple mutex test. We have 2 tasks, one periodically prints out to the console, other one also, but with the same time. The
console is protected by the mutex to not avoid to access the console by 2 tasks at once. both tasks has the same priority.
*/

/*
Peripherial used: console 
*/

#if (dTestSimpleMutex == 1)

/* step 1: create mutex handler */
SemaphoreHandle_t mutex;

/* Step 2: create tasks handlers */
void vSenderTask(void* pvParameters);
void vTickTask(void* pvParameters);

/* Step 3: initfunction call */
void simpleMutexTestInit(void)
{
    consoleSend((unsigned char*)"Siple mutex example! ");

    /* Create mutex */
    mutex = xSemaphoreCreateMutex();

    /* Create tasks */
    xTaskCreate(vSenderTask, "TM1", 128, NULL, 2, NULL);
    xTaskCreate(vTickTask, "TM2", 128, NULL, 2, NULL);
}


void vTickTask(void* pvParameters)
{
    /* Every 1 second sends pointer to string "tick" to the tick queue */
    for (;;)
    {
        xSemaphoreTake(mutex, portMAX_DELAY);   //Wait for mutex
        vTaskDelay(2000);       //Every 1000 ms send something
        consoleSend((unsigned char*)"TASK1: ============================================");
        xSemaphoreGive(mutex);
    }
}

void vSenderTask(void* pvParameters)
{  
    for(;;)
    {
        xSemaphoreTake(mutex, portMAX_DELAY);
        vTaskDelay(2010);       //Every 1000  ms send something
        consoleSend((unsigned char*)"TASK2: ============================================");
        xSemaphoreGive(mutex);
    }
}



#endif
#include "FreeRTOS.h"
#include <task.h>
#include <semphr.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Button/Button.h"
#include "../../BSP/Communication/Console.h"

#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim10;

/*
CASE: Create counting semaphore that will count number of button press events and print in out by other task.
*/

/*
Peripherial used: buttons, console
*/

#if (dTestCountingSemaphore == 1)

/* STEP1: create semaphore handler */
SemaphoreHandle_t semaphore;

/* Step2: create led stitching state task*/
void vPrintStateTask(void* pvParameters);

/* Step3: create button checking state task*/
void vButtonCheckStateTask(void* pvParameters);

/* Step 4: initialize function */
void countingSemaphoreTestInit(void)
{
    consoleSend((unsigned char*)"Counting semaphore example! ");    

    /* Create binary semaphore */
    semaphore = xSemaphoreCreateCounting(10, 0);

    /* Create console task */
    xTaskCreate(vPrintStateTask, "BS_T1", 64, NULL, 3, NULL);

    /* Create button state task */
    xTaskCreate(vButtonCheckStateTask, "BS_T2", 64, NULL, 2, NULL);
}

void vPrintStateTask(void* pvParameters)
{
    for (;;)
    {
        xSemaphoreTake(semaphore, portMAX_DELAY);   //Wait for semaphore to take
        consoleSend((char*)"Counting semaphore!");
        
    }
}

void vButtonCheckStateTask(void* pvParameters)
{
    for (;;)
    {
        if(button_IsPressed())
        {
            xSemaphoreGive(semaphore);   //Give semaphore if button pressed (on release event)
        }
    }
}

#endif
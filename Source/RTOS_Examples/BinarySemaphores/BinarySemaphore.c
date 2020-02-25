#include "FreeRTOS.h"
#include <task.h>
#include <semphr.h>

#include "../RTOS_Examples.h"
#include "../../BSP/Button/Button.h"
#include "../../BSP/LEDs/LEDs.h"

#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim10;

/*
CASE: Create binary semaphore that will synchronize 2 tasks (1 case) and task with timer ISR. Synchronized task
        will change led state (on/off) after synchronization. After pressing the button (button task noticed) the led has to shine
        (if switched off) and switch off if shined. Shining the led must start the timer, that will unblock led task causing switching it
        off after timer period elapsing.
*/

/*
Peripherial used: leds, buttons, timer
*/

#if (dTestBinarySemaphore == 1)

/* STEP1: create semaphore handler */
SemaphoreHandle_t semaphore;

/* Step2: create led stitching state task*/
void vLedChangeStateTask(void* pvParameters);

/* Step3: create button checking state task*/
void vButtonCheckStateTask(void* pvParameters);

/* Step4: create timer interrupt*/


/* Step 4: initialize function */
void binarySemaphoreTestInit(void)
{

    /* Create binary semaphore */
    semaphore = xSemaphoreCreateBinary();

    /* Initialize the Led */
    LedOff(eLed4);

    /* Initialize the timer */
    //Already initialized by STM HAL

    /* Create led task */
    xTaskCreate(vLedChangeStateTask, "BS_T1", 64, NULL, 3, NULL);

    /* Create button state task */
    xTaskCreate(vButtonCheckStateTask, "BS_T2", 64, NULL, 2, NULL);
}

void vLedChangeStateTask(void* pvParameters)
{
    for (;;)
    {
        xSemaphoreTake(semaphore, portMAX_DELAY);   //Wait for semaphore to take
        LedToggle(eLed4);
        
    }
}

void vButtonCheckStateTask(void* pvParameters)
{
    for (;;)
    {
        if(button_IsPressed())
        {
            while(button_IsPressed());   //Prevent lot of pressing events
            xSemaphoreGive(semaphore);   //Give semaphore if button pressed (on release event)
            HAL_TIM_Base_Start_IT(&htim10);     //Start timer
        }
    }
}

void timer10Callback(void)
{
    xSemaphoreGiveFromISR(semaphore, pdTRUE);   //Semaphore give from ISR, force contex switching
    HAL_TIM_Base_Stop_IT(&htim10);
}

#endif
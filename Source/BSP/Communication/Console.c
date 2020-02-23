#include "stm32f4xx_hal.h"
#include "Console.h"

extern UART_HandleTypeDef huart2;

static inline uint16_t nrOfChars(unsigned char* pData);

static inline uint16_t nrOfChars(unsigned char* pData)
{
    uint16_t nrOfChars = 0;
    while(pData[nrOfChars] != 0) nrOfChars++;   //Calculate number of characters   
    return nrOfChars;
}

void consoleSend(unsigned char* pData)
{
    uint16_t length = nrOfChars(pData);
    HAL_UART_Transmit(&huart2, pData, length, 10);
    HAL_UART_Transmit(&huart2, (unsigned char*)("\r\n"), 2, 2);
}

void consoleSendByte(unsigned char* data)
{
    HAL_UART_Transmit(&huart2, data, 1, 0);
}

void consoleRead(unsigned char* pData, uint16_t length, uint16_t timeout)
{
    HAL_UART_Receive(&huart2, pData, length, timeout);
}

void Console_Init()
{
    unsigned char data[] = "Hello world\r\n\n";
    HAL_UART_Transmit(&huart2, data, 14, 10);
}



// #ifdef dUsePointerQueue
// void vReceiverTask(void* pvParameters)
// {
//     /* After receiving byte by UART it gives it into queue so the byte could be sent back by sender task */
//     static uint16_t i = 0;
//     unsigned char *pcStringToSend;
//     for(;;)
//     {
//         unsigned char data = 0;
//         HAL_UART_Receive(&huart2, &data, 1, 0);
        
//         if (data != 0)
//         {
//             dataBuffer[i] = data;   //Add sign to buffer
//             i++;

//             if (data == 0x0D)  //If enter sign
//             {
//                 pcStringToSend = dataBuffer;
//                 xQueueSendToBack(consoleQueue, &pcStringToSend, 0);  //Queue pointer to data buffer
//                 i = 0;
//             }
//         }
//     }
// }

// void vSenderTask(void* pvParameters)
// {
//     for(;;)
//     {
//         unsigned char* data = NULL;
//         uint16_t nrOfBytes = 0;
        
//         xQueueReceive(consoleQueue, &data, portMAX_DELAY);
        
//         while(data[nrOfBytes] != 0)
//         {
//             nrOfBytes++;
//         }
        
//         HAL_UART_Transmit(&huart2, data, nrOfBytes, 10);
        
//         for(uint16_t i = 0; i < nrOfBytes; i++)     //Empty buffer after sending
//         {
//             data[i] = 0;
//         }
//     }
// }
// #endif

#ifdef dUseQueueSet
/*
CASE3: 

unsigned char tickMessage[] = "tick\n";


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
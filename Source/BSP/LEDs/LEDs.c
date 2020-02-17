#include "LEDs.h"
#include "LED_Config.h"
#include "stm32f4xx_hal.h"

static const uint32_t pins[] = LED_Pin;
static const GPIO_TypeDef* ports[] = LED_Port;

void LedsInit(void)
{

  
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  for (uint16_t id = 0; id < (uint16_t)(dLedAmount); id++)
  {
    GPIO_InitStruct.Pin = pins[id];
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init((GPIO_TypeDef*)ports[id], &GPIO_InitStruct);
  }

}

void LedOn(LedId_t ledId)
{
    HAL_GPIO_WritePin((GPIO_TypeDef*)ports[ledId], pins[ledId], GPIO_PIN_SET);
}

void LedOff(LedId_t ledId)
{
    HAL_GPIO_WritePin((GPIO_TypeDef*)ports[ledId], pins[ledId], GPIO_PIN_RESET);
}

void LedToggle(LedId_t ledId)
{
    HAL_GPIO_TogglePin((GPIO_TypeDef*)ports[ledId], pins[ledId]);
}
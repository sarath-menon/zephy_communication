
#include "hal_functions.h"
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <stm32l4xx.h>

UART_HandleTypeDef huart2;

static void MX_USART2_UART_Init(void);
void Error_Handler(void);

int main() {

  MX_USART2_UART_Init();

  while (1) {
    // HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
    // HAL_Delay(250);

    uint8_t data[] = "HELLO WORLD \r\n";
    HAL_UART_Transmit(&huart2, data, sizeof(data), 10);
    HAL_Delay(25); // 250 ms delay
  }
  return 0;
}


#include "hal_functions.h"
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <stm32l4xx.h>

UART_HandleTypeDef huart2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void Error_Handler(void);

int main() {

  HAL_Init();

  // SystemClock_Config();
  MX_GPIO_Init();
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

static void MX_USART2_UART_Init(void) {

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */
}

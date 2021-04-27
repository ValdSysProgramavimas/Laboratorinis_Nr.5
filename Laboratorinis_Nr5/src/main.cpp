#include "stm32f4xx_hal.h"

UART_HandleTypeDef UART_Handler;

void UART2_Configuration(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	GPIO_InitTypeDef UART2_GPIO_Handler;

	UART2_GPIO_Handler.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	UART2_GPIO_Handler.Mode = GPIO_MODE_AF_PP;
	UART2_GPIO_Handler.Pull = GPIO_PULLUP;
	UART2_GPIO_Handler.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	UART2_GPIO_Handler.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &UART2_GPIO_Handler);

	UART_Handler.Instance = USART2;
	UART_Handler.Init.BaudRate = 115200;
	UART_Handler.Init.Mode = UART_MODE_TX_RX;
	UART_Handler.Init.WordLength = UART_WORDLENGTH_8B;
	UART_Handler.Init.StopBits = UART_STOPBITS_1;
	UART_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART_Handler);
}

void InitializeLED()
{
	__GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = GPIO_PIN_13;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
int main(void)
{
	HAL_Init();
	UART2_Configuration();
	InitializeLED();

	while(1)
	{
			uint8_t buffer[1];
			HAL_UART_Receive(&UART_Handler, buffer, sizeof(buffer), HAL_MAX_DELAY);
			if(buffer[0]=='r'){HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);}
			if(buffer[0]=='0'){HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);}
	}
}

#include "..\stm\stm32f4xx_rcc.h"
#include "..\stm\stm32f4xx_gpio.h"
#include "..\stm\stm32f4xx_usart.h"
#include "..\stm\stm32f4xx_dma.h"
#include "uart.h"

void UART1_Initializing(void)
{
	GPIO_InitTypeDef gpio_usart1_init;
	USART_InitTypeDef usart1_init;
	
		/* clocking on A (USART1) */
	RCC_AHB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
		/* clocking on USART1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	gpio_usart1_init.GPIO_Pin = GPIO_Pin_8;
	gpio_usart1_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_usart1_init.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA, &gpio_usart1_init);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	
	gpio_usart1_init.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	gpio_usart1_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_usart1_init.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &gpio_usart1_init);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	usart1_init.USART_BaudRate = 9600;
	usart1_init.USART_WordLength = USART_WordLength_8b;
  usart1_init.USART_StopBits = USART_StopBits_1;
  usart1_init.USART_Parity = USART_Parity_No;
  usart1_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart1_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &usart1_init);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //receive interruption 
	USART_ITConfig(USART1, USART_IT_TC, ENABLE); //transmit interruption
	NVIC_EnableIRQ(USART1_IRQn);
	
	USART_Cmd(USART1, ENABLE);
}

void DMA_Initializing(void)
{
	DMA_InitTypeDef dma1;
	
		/* clocking on DMA */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	/*
	dma1.DMA_PeripheralBaseAddr = (uint32t)&(USART1->DR); //адрес периферийного устройства, которое будет участвовать в обмене информацией
	dma1.DMA_MemoryBaseAddr = (uint32_t)&dataBuffer[0]; //data addr
	dma1.DMA_DIR = DMA_DIR_PeripheralDST; //destination - peripherial
	dma1.DMA_BufferSize = 16;
	dma1.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma1.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma1.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma1.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_Init(DMA1_Channel4, &dma1);
	*/
	
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
//	DMA_Cmd(DMA1_Channel4, ENABLE);
}

int UART_ReceiveData(void)
{
	
}

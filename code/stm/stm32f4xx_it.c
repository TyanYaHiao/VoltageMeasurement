/**
  ******************************************************************************
  * @file    NVIC/NVIC_IRQMask/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_adc.h"
#include "..\interfaces\spi.h"
#include "..\interfaces\adc.h"
#include "stm32f4xx_gpio.h"
   
extern	uint8_t receivedData[16];
extern uint8_t reseivedDataLenght;
extern uint8_t reseivedDataCounter;
extern uint8_t sendData[9];
extern uint8_t sendDataLenght;
extern uint8_t sendDataCounter;

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup NVIC_IRQMask
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t uwIndex = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s).    */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

	/* Interruption processing */

void	Beep(unsigned int times)
{
	while (times)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		Delay(10000000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		Delay(10000000);
		times--;
	}
}

void TIM7_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	TIM7_flag = true;
}

void USART1_IRQHandler()
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		receivedData[reseivedDataCounter] = USART_ReceiveData(USART1);
		reseivedDataCounter++;
		
		if (reseivedDataCounter == reseivedDataLenght)
		{
			USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
		}
/*		if (UART_ReceiveData())
			DMA_SendData();
		else
			UART_SendError();
		*/
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); //clear flag
	}
	
	if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)
	{
		USART_SendData(USART1, sendData[sendDataCounter]);
		sendDataCounter++;
		
		if  (sendDataCounter == sendDataLenght)
    	{
        sendDataCounter = 0;
      }
		
		USART_ClearITPendingBit(USART1, USART_IT_TC); //clear flag
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

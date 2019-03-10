#include "..\stm\stm32f4xx_gpio.h"
#include "..\stm\stm32f4xx_spi.h"
#include "..\stm\stm32f4xx_tim.h"
#include "..\stm\stm32f4xx_rcc.h"
#include "tim.h"
#include "adc.h"

void TIM_Initializing(void)
{
	TIM_TimeBaseInitTypeDef tim_init;
	RCC_ClocksTypeDef clocks_init;
	RCC_GetClocksFreq(&clocks_init);

	/* clocking on TIM6 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	tim_init.TIM_Prescaler = 40 - 1; // 40??
	tim_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_init.TIM_Period = (20000 / PRECISION); // 20000 - period lenght in 50Hz
	tim_init.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM6, &tim_init);

	TIM_Cmd(TIM6, ENABLE); // Enabling timer
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
}

void TIM7_Initializing(void)
{
	TIM_TimeBaseInitTypeDef tim_init;
	RCC_ClocksTypeDef clocks_init;
	RCC_GetClocksFreq(&clocks_init);

	/* clocking on TIM7 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	
	tim_init.TIM_Prescaler = 40 - 1; // Converting to 1MHz freq
	tim_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_init.TIM_Period = (20000 / PRECISION); // 20000 - period lenght in 50Hz
	tim_init.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM7, &tim_init);

	TIM_Cmd(TIM7, ENABLE); // Enabling timer
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);
}

void	TIM_Delay(void)
{
	while (TIM_GetFlagStatus(TIM6, TIM_FLAG_Update) != SET);

	TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	TIM_SetCounter(TIM6, 0); // Timer reset
}

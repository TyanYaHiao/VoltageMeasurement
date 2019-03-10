#include "..\stm\stm32f4xx_spi.h"
#include "..\stm\stm32f4xx_gpio.h"
#include "..\stm\stm32f4xx_tim.h"
#include "..\stm\stm32f4xx_rcc.h"
#include "..\stm\stm32f4xx.h"
#include "adc.h"
#include <math.h> 

bool TIM7_flag;
extern double result[NUM_VOLTAGE];

void ADC_MCP3914_Init()
{
	GPIO_Initializing();
	SPI_Initializing();
	BEEP_Initializing();
	RESET_Initializing();
	TIM7_Initializing(); //TIM 7 Initializing for BEEP
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); //enable tim7 interruption
	NVIC_EnableIRQ(TIM7_IRQn);
	
	/* Select RESET */
	GPIO_SetBits(GPIOC, GPIO_Pin_4);
	Delay(1000000); // Waiting for reset
}

void	Delay(unsigned long p)
{
	while(p > 0)
		p--;
}

void Calculate_Sign(int32_t *data)
{
	int phase = 0;
	
	while(phase < NUM_VOLTAGE)
	{
		if (data[phase] > 0x7FFFFF)
			data[phase] += (0xFF << 24);
		phase++;
	}
}

void Convert_Data(int32_t *data, double *data_d)
{
	int phase = 0;
	double circuit_k = 0;
	double adc_k = 0;

	/* */
	circuit_k = (1000 + 360000 + 360000 + 360000) / 1000;
	adc_k = (1.2 / (8388608 * 1 * 1.5));
	while(phase < NUM_VOLTAGE)
	{
		data_d[phase] = data[phase] * circuit_k * adc_k;
		phase++;
	}
}

void Read_Array(int32_t (*g_buffer)[NUM_VOLTAGE], int count)
{
	while (count < PRECISION)
	{	
		if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_4); // Transfer ON flag
			Read_Voltage(VOLTAGE_A, g_buffer[count]);	// Array filling
			GPIO_SetBits(GPIOA, GPIO_Pin_4); // Transfer OFF flag	
			count++;
		}
	}
	
	NVIC_DisableIRQ(TIM7_IRQn);
}

void Read_Voltage(uint16_t request, int32_t *data)
{
	int i;
	uint8_t array[9] = {0};
	uint8_t temp = 0;

	SPI_I2S_SendData(SPI1, request);	
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	SPI_I2S_ReceiveData(SPI1); 
	for (i = 1; i <= 9; i++)
	{		
		SPI_I2S_SendData(SPI1, 0x00);
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
		while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		temp = SPI_I2S_ReceiveData(SPI1);
		array[i - 1] = temp;
		if (i <= 3)
		{	
			data[0] = data[0] + temp;
			if (i != 3)
				data[0] = data[0] << 8;
		}
		else if (i <= 6)
		{
			data[1] = data[1] + temp;
			if (i != 6)
				data[1] = data[1] << 8;
		}
		else if (i<= 9)
		{
			data[2] = data[2] + temp;
			if (i != 9)
				data[2] = data[2] << 8;		
		}
	}
	temp = 0;
}

void Calculate_Value(double g_data[][NUM_VOLTAGE], double *voltage)
{
	int phase = 0;
	int i;
	double temp;
	
	while (phase < NUM_VOLTAGE)
	{
		temp = 0;
		i = 0;
		while (i < PRECISION)
		{
			temp = temp + g_data[i][phase] * g_data[i][phase];
			if(i == PRECISION - 1)
				voltage[phase] = sqrt(temp / PRECISION);
			i++;
		}
		phase++;			
	}
}

void Voltage_Measurement(double *voltage)
{
	int32_t g_buffer[PRECISION][NUM_VOLTAGE] = {0};
	double	g_data[PRECISION][NUM_VOLTAGE] = {0};
	int read_count = 0;
	int convert_count = 0;
		
	 /* Read and write phases A,B,C */
	Read_Array(g_buffer, read_count);
		
	/* Converting measurements data */
	for (convert_count = 0; convert_count < PRECISION; convert_count++)
	{
		Calculate_Sign(g_buffer[convert_count]);
		Convert_Data(g_buffer[convert_count], g_data[convert_count]); // into Volts
	}
	
	/* Final calculating between all measurements in period */
	Calculate_Value(g_data, voltage);
}
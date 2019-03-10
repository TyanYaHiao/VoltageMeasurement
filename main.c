#include <stdint.h>
#include "code\interfaces\spi.h"
#include "code\interfaces\adc.h"
#include "code\interfaces\tim.h"
#include "code\stm\stm32f4xx_gpio.h"
#include "code\stm\stm32f4xx_spi.h"
#include "code\stm\stm32f4xx_rcc.h"
#include "code\stm\stm32f4xx_adc.h"
#include "code\stm\stm32f4xx.h"
#include "code\stm\stm32f4xx_it.h"
#include "code\stm\stm32f4xx_tim.h"

double result[NUM_VOLTAGE] = {0};
uint8_t receivedData[16];
uint8_t reseivedDataLenght = 16;
uint8_t reseivedDataCounter = 0;
uint8_t sendData[9];
uint8_t sendDataLenght = 9;
uint8_t sendDataCounter = 0;


int		main()
{		
	sendData[0] = 0x11;
	sendData[1] = 0x22;
	sendData[2] = 0x33;
	sendData[3] = 0x44;
	sendData[4] = 0x55;
	sendData[5] = 0x66;
	sendData[6] = 0x77;
	sendData[7] = 0x88;
	sendData[8] = 0x99;
	
	UART1_Initializing();
	ADC_MCP3914_Init();	
	while (1)
		Voltage_Measurement(result);
}
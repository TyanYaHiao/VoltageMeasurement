#include "..\stm\stm32f4xx_gpio.h"
#include "..\stm\stm32f4xx_spi.h"
#include "..\stm\stm32f4xx_rcc.h"
#include "..\stm\stm32f4xx.h"

/* Variables declaration*/
GPIO_InitTypeDef gpio_init;
SPI_InitTypeDef spi_init;

void	BEEP_Initializing(void)
{
	GPIO_InitTypeDef gpio_beep_init;
	
	/* clocking on D (relay) */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	gpio_beep_init.GPIO_Pin = GPIO_Pin_12;
	gpio_beep_init.GPIO_Mode = GPIO_Mode_OUT;
	gpio_beep_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_beep_init.GPIO_OType = GPIO_OType_PP;
	gpio_beep_init.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &gpio_beep_init);
}

void GPIO_Initializing(void)
{
	/* clocking on A (SPI interface) */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		
	/* Initializing SCLK(5), MISO(6), MOSI(7) */
	gpio_init.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	gpio_init.GPIO_Mode = GPIO_Mode_AF;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_OType = GPIO_OType_PP;
	gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &gpio_init);
		
	
	/* Setting alternative function PINs 5,6,7 */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
		
	/* Initializing SS1(4) */
	gpio_init.GPIO_Pin = GPIO_Pin_4;
	gpio_init.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_OType = GPIO_OType_PP;
	gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio_init);
}

void RESET_Initializing(void)
{
		/* clocking on C (reset) */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
		/* Initializing RESET */
	gpio_init.GPIO_Pin = GPIO_Pin_4;
	gpio_init.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_OType = GPIO_OType_PP;
	gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &gpio_init);
}

void SPI_Initializing(void)
{
	SPI_InitTypeDef spi_init;
	
	/* clocking on SPI1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	/* SPI1 settings */
	spi_init.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
 	spi_init.SPI_Mode = SPI_Mode_Master;
	spi_init.SPI_DataSize = SPI_DataSize_8b;
	spi_init.SPI_CPOL = SPI_CPOL_Low;
	spi_init.SPI_CPHA = SPI_CPHA_1Edge;
	spi_init.SPI_NSS = SPI_NSS_Soft;
	spi_init.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	spi_init.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI1, &spi_init);
	
	/* SPI1 module enabling */
	SPI_Cmd(SPI1, ENABLE); 
}
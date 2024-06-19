/*
 * Display_EDO_W21.c
 *
 *  Created on: Jun 12, 2024
 *      Author: Utilisateur
 */

#include "Display_EPD_W21_spi.h"

extern SPI_HandleTypeDef hspi1;

void SPI_Delay(uint8_t xrate)
{
	while(xrate--);

}

//void SPI_Write(uint8_t value)
//{
//
//	unsigned char i;
//	 SPI_Delay(1);
//	for(i=0; i<8; i++)
//	{
//		EPD_W21_CLK_0;
//		SPI_Delay(1);
//		if(value & 0x80)
//			EPD_W21_MOSI_1;
//		else
//			EPD_W21_MOSI_0;
//		value = (value << 1);
//		SPI_Delay(1);
//		EPD_W21_CLK_1;
//		SPI_Delay(1);
//	}
//
//}

// SPI Hardware Implement
void SPI_Write(uint8_t value)
{

HAL_SPI_Transmit(&hspi1, &value, 1, HAL_MAX_DELAY);

}



void EPD_W21_WriteCMD(uint8_t command)
{
	EPD_W21_CS_0;
	EPD_W21_DC_0;  // D/C#   0:command  1:data
	SPI_Write(command);
	EPD_W21_CS_1;
}
//SPI write data
void EPD_W21_WriteDATA(uint8_t datas)
{
	EPD_W21_CS_0;
	EPD_W21_DC_1;  // D/C#   0:command  1:data
	SPI_Write(datas);
	EPD_W21_CS_1;
}

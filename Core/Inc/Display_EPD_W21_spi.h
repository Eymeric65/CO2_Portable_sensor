#ifndef _DISPLAY_EPD_W21_SPI_
#define _DISPLAY_EPD_W21_SPI_

#include "stm32l0xx_hal.h"
// Non hardware SPI
//#define EPD_W21_MOSI_0	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,GPIO_PIN_RESET)
//#define EPD_W21_MOSI_1	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,GPIO_PIN_SET)
//
//#define EPD_W21_CLK_0	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_RESET)
//#define EPD_W21_CLK_1	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,GPIO_PIN_SET)
// -----------------
#define EPD_W21_CS_0	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
#define EPD_W21_CS_1	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

#define EPD_W21_DC_0	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_RESET);
#define EPD_W21_DC_1	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_SET);

#define EPD_W21_RST_0	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
#define EPD_W21_RST_1	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

#define isEPD_W21_BUSY HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) // for solomen solutions

void SPI_write(uint8_t value);

void EPD_W21_WriteDATA(uint8_t datas);
void EPD_W21_WriteCMD(uint8_t command);


#endif  //#ifndef _MCU_SPI_H_

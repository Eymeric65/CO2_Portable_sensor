/*
 * CO2_probe.h
 *
 *  Created on: Jun 15, 2024
 *      Author: Utilisateur
 */

#ifndef INC_CO2_PROBE_H_
#define INC_CO2_PROBE_H_

#include "fonts.h"
#include "stdint.h"
#include "stm32l0xx_hal.h"


typedef struct
{
  uint8_t x;
  uint16_t y;
  uint8_t max_x;
  uint16_t max_y;
  uint8_t max_digit;
  uint16_t column;
  uint16_t line;
  sFONT font;
  uint16_t num;
  uint8_t num_digit;
  uint16_t area_draw;
  uint16_t absolute_address;
 } Text_Z;

uint8_t countDigits(uint16_t num);


void Set_pixel(uint8_t* Map,uint8_t x,uint16_t y, uint8_t set);

void Write_num(uint8_t* Map,uint8_t x,uint16_t y,sFONT font,uint8_t num);

Text_Z Zone_Write_nums(uint8_t x,uint16_t y,sFONT font,uint16_t num,uint8_t v_al,uint8_t h_al,uint8_t max_size);

void Write_nums(uint8_t* Map,Text_Z text);

void Display_Text(Text_Z text, uint8_t * Map,uint8_t * background);

HAL_StatusTypeDef Send_I2C_Command(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t command, uint32_t Timeout);

void SCREEN_GPIO_Deact(void);

void SCREEN_GPIO_Act(void);


#endif /* INC_CO2_PROBE_H_ */

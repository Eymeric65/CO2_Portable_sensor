/*
 * CO2_probe.c
 *
 *  Created on: Jun 16, 2024
 *      Author: Utilisateur
 */
#include "CO2_probe.h"
#include "Display_EPD_W21.h"
#include <string.h>
#include <stdlib.h>
#include <main.h>
#include "stm32l0xx_hal.h"
/* Coord going from top right do bottom left from 0,0 to EPD_HEIGHT,EDP_WIDTH
 *
 */

/*
 * Modify the bit in where the indice 0 is the left one
 */

uint8_t modify_bit(uint8_t x, uint8_t n, uint8_t value) {
    return (value) ? (x | (0x80 >> n)) : (x & ~(0x80 >> n));
}

/*
 * Get the bit in where the indice 0 is the left one
 */

uint8_t get_bit(uint8_t x,uint8_t n){
	return (x >> (7-n)) & 1;
}

void Set_pixel(uint8_t* Map,uint8_t x,uint16_t y, uint8_t set)
{
	uint16_t absolute_address;

	absolute_address = y + x*EPD_WIDTH;

	Map[absolute_address/8]= modify_bit(Map[absolute_address/8],absolute_address%8,set);

}

uint8_t countDigits(uint16_t num) {
	uint8_t count = 0;

	if(num==0)
	{
		return 1;
	}

    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}

void getDecimalDigits(uint16_t num, uint8_t * digits, uint16_t numDigits) {
	int16_t i;
    for (i = numDigits - 1; i >= 0; i--) {
        digits[i] = num % 10;
        num /= 10;
    }
}

/*
 * Draw a Number on an array from bottom left
 */
void Write_num(uint8_t* Map,uint8_t x,uint16_t y,sFONT font,uint8_t num)
{
	uint8_t round_width;

	round_width = font.Width/8 + (font.Width%8>0);

	uint16_t start_adress;

	start_adress = num*round_width*font.Height;

	uint8_t i;
	uint8_t j;

	for(i=0;i<font.Width;i++)
	{

		for(j=0;j<font.Height;j++)
		{
			Set_pixel(Map,x-i,y-font.Height+j,get_bit(font.table[start_adress+i/8+j*round_width],i%8));
			//Set_pixel(Map,x-i,y-font.Height+j,(i+j)%2);
		}

	}
}

#define LETTER_UPPER_CACHE 1

Text_Z Zone_Write_nums(uint8_t x,uint16_t y,sFONT font,uint16_t num,uint8_t v_al,uint8_t h_al,uint8_t max_size)
{

	Text_Z res;

	res.num_digit = countDigits(num);

	uint16_t max_y;

	switch(v_al){
	case 0: // up
		max_y=y-font.Height;
		break;
	case 1: // center
		max_y=y-font.Height/2;
		break;
	case 2: // down
		max_y=y;
		break;
	}

	uint8_t max_x_th;
	uint8_t max_x;
	switch(h_al){
	case 0: // left
		max_x=x+(res.num_digit)*font.Width;
		max_x_th = x;
		break;
	case 1: // center
		max_x=x+(res.num_digit*font.Width)/2;
		max_x_th=x-(max_size*font.Width)/2;
		break;
	case 2: // right
		max_x=x;
		max_x_th=x-max_size*font.Width;
		break;
	}

	res.y = max_y+font.Height;
	res.max_y=max_y-max_y%8;
	res.line=max_y%8 + font.Height;
	res.line+=  (8-res.line%8)*(res.line%8!=0);

	res.x = max_x;
	res.max_x=max_x_th;
	res.column= max_size*font.Width;

	res.font=font;

	res.num=num;

	res.max_digit=max_size;

	res.area_draw=res.column*res.line/8;

	res.absolute_address = (res.max_x*EPD_WIDTH+res.max_y)/8;

	return res;
}

/*
 * Save data inside the draw zone of a text into an array save
 */
void Save_data(uint8_t * save,Text_Z text,uint8_t * Map)
{

	uint16_t i;
	for(i=0;i<text.area_draw;i++){
		save[i]=Map[text.absolute_address+i%(text.line/8)+i/(text.line/8)*EPD_WIDTH/8];
	}
}

/*
 * Wipe the text zone
 */
void Wipe_TextZone(uint8_t * Map,Text_Z text,uint8_t * Background){
	uint16_t i;
	for(i=0;i<text.area_draw;i++){
		uint16_t address = text.absolute_address+i%(text.line/8)+i/(text.line/8)*EPD_WIDTH/8;
		Map[address]=Background[address];
	}
}

/*
 * Write the different number of the Text_Z element from bottom left
 */

void Write_nums(uint8_t* Map,Text_Z text)
{

    uint8_t digits[text.num_digit]; // Array to store digits

    getDecimalDigits(text.num, digits, text.num_digit); // Store digits in the array

	uint8_t i;
	for(i=0;i<text.num_digit;i++)
	{
		Write_num(Map,text.x-i*text.font.Width,text.y,text.font,digits[i]);
	}

}



void Display_Text(Text_Z text, uint8_t * Map,uint8_t * background)
{

	uint8_t old_datas[text.area_draw];

	//memset(old_datas,0xFF,text.area_draw);
	Save_data(old_datas,text,Map);


	Wipe_TextZone(Map,text,background);
	Write_nums(Map,text);

	uint8_t new_datas[text.area_draw];

//	uint16_t i;
//	for(i=0;i<text.area_draw;i++){
//		//new_datas[i] = 0xAA;
//		new_datas[i]=Map[text.absolute_address+i%(text.line/8)+i/(text.line/8)*EPD_WIDTH/8];
//	}

	//memset(new_datas,0x00,text.area_draw);
	Save_data(new_datas,text,Map);



	EPD_Dis_Part_Old(text.max_y,text.max_x,new_datas,old_datas,text.column,text.line);



}


HAL_StatusTypeDef Send_I2C_Command(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t command, uint32_t Timeout)
{

	uint8_t comm[] = {(command >> 8) & 0xFF,command & 0xFF};

	//return HAL_I2C_Master_Transmit(hi2c, DevAddress, (uint8_t*)&command,2, 500);
	return HAL_I2C_Master_Transmit(hi2c, DevAddress, comm,2, 500);
}

void SCREEN_GPIO_Act(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */

  /*Configure GPIO pin Output Level */
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Screen_CS_GPIO_Port, Screen_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Screen_PWR_Pin, GPIO_PIN_RESET); // Activate the screen

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D_C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Screen_Res_GPIO_Port, Screen_Res_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CO2_PWR_Pin Screen_CS_Pin */
  GPIO_InitStruct.Pin = Screen_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : Screen_PWR_Pin SD_PWR_Pin SD_CS_Pin D_C_Pin */
  GPIO_InitStruct.Pin = D_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Screen_Busy_Pin */
  GPIO_InitStruct.Pin = Screen_Busy_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Screen_Busy_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Screen_Res_Pin */
  GPIO_InitStruct.Pin = Screen_Res_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Screen_Res_GPIO_Port, &GPIO_InitStruct);

}

void SCREEN_GPIO_Deact(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  HAL_GPIO_WritePin(Screen_CS_GPIO_Port, Screen_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Screen_PWR_Pin, GPIO_PIN_SET); // Deactivate the screen

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D_C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Screen_Res_GPIO_Port, Screen_Res_Pin, GPIO_PIN_RESET);

  /* GPIO Ports Clock Enable */

  /*Configure GPIO pin Output Level */
  /*Configure GPIO pin Output Level */


  /*Configure GPIO pins : CO2_PWR_Pin Screen_CS_Pin */
  GPIO_InitStruct.Pin = Screen_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : Screen_PWR_Pin SD_PWR_Pin SD_CS_Pin D_C_Pin */
  GPIO_InitStruct.Pin = D_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Screen_Busy_Pin */
  GPIO_InitStruct.Pin = Screen_Busy_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Screen_Busy_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Screen_Res_Pin */
  GPIO_InitStruct.Pin = Screen_Res_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Screen_Res_GPIO_Port, &GPIO_InitStruct);

}

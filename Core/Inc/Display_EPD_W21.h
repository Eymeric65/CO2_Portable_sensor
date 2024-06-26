#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_

#include "stdint.h"

#define EPD_WIDTH   88
#define EPD_HEIGHT  184
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8  
//Full screen refresh display
void EPD_Init(void); 
void EPD_Init_DS(void);
void EPD_Init_180(void);	
void EPD_WhiteScreen_ALL(const unsigned char *datas);
void EPD_WhiteScreen_White(void);
void EPD_WhiteScreen_Black(void);
void EPD_DeepSleep(void);
//Partial refresh display 
void EPD_Init_Part(void);
void EPD_SetRAMValue_BaseMap(const unsigned char * datas);
void EPD_Dis_PartAll(const unsigned char * datas);
void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE);
void EPD_Dis_Part_Time(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
												const unsigned char * datas_C,const unsigned char * datas_D,const unsigned char * datas_E,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE);

void EPD_Dis_Part_Old(unsigned int x_start,unsigned int y_start,uint8_t * datas,uint8_t * oldDatas,unsigned int PART_COLUMN,unsigned int PART_LINE);
//Fast refresh display
//void EPD_Init_Fast(void);
//void EPD_WhiteScreen_ALL_Fast(const unsigned char *datas);   
//GUI display				
void EPD_Init_GUI(void);												
void EPD_Display(unsigned char *Image); 
void EPD_Dis_Part11(unsigned int x,unsigned int y,const unsigned char * new_data,unsigned int w,unsigned int l,unsigned char mode); //mode 0: first  1: other...
												 
#endif



#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"

unsigned char oldData[2024];
unsigned char oldDataP[256];
unsigned char oldDataA[256];
unsigned char oldDataB[256];
unsigned char oldDataC[256];
unsigned char oldDataD[256];
unsigned char oldDataE[256];
unsigned char partFlag=1;
void delay_xms(unsigned int xms)
{
	unsigned int i;
	while(xms--)
	{
		i=12000;
		while(i--);
	}
}
void lcd_chkstatus(void)
{
	while(isEPD_W21_BUSY==0);
                   
}

void EPD_Init_DS(void)
{
	EPD_W21_RST_0;		// Module reset
	HAL_Delay(10);//At least 10ms delay
	EPD_W21_RST_1;
	HAL_Delay(10);//At least 10ms delay
lcd_chkstatus();
EPD_W21_WriteCMD(0x06);
EPD_W21_WriteDATA (0x17);
EPD_W21_WriteDATA (0x17);
EPD_W21_WriteDATA (0x17);

EPD_W21_WriteCMD(0x04);
lcd_chkstatus();

EPD_W21_WriteCMD(0x00);
EPD_W21_WriteDATA (0x1f);

EPD_W21_WriteCMD(0x61);
EPD_W21_WriteDATA (0x58);
EPD_W21_WriteDATA (0x00);
EPD_W21_WriteDATA (0xb8);

EPD_W21_WriteCMD(0x50);
EPD_W21_WriteDATA (0x87);
}


void EPD_lut(unsigned char LUTsel)			
{
	unsigned char tempfull,temppartial;
	EPD_W21_WriteCMD(0x40);
	lcd_chkstatus();
	//tempfull = EPD_W21_ReadDATA();
	tempfull =25;
	if((128>tempfull)&&(tempfull>54))		
		tempfull = 53 ;						
	else if(tempfull>128)					
		tempfull = 1;							
	
	temppartial = tempfull+60;			
	if(temppartial>128)						
		temppartial = 127;
	
	if(LUTsel==0)							
	{
			EPD_W21_WriteCMD(0xE0);					
			EPD_W21_WriteDATA(0x02);		
			EPD_W21_WriteCMD(0xE5);			
			EPD_W21_WriteDATA(tempfull);	//define the Temperature value////			
	}

	else if(LUTsel==1)							
	{
			EPD_W21_WriteCMD(0xe0);
			EPD_W21_WriteDATA (0x02);
			EPD_W21_WriteCMD(0xe5);
			EPD_W21_WriteDATA (temppartial);
	}
}
//JD79651
void EPD_Init(void)
{	
		EPD_W21_RST_0;		// Module reset
		HAL_Delay(10);//At least 10ms delay
		EPD_W21_RST_1;
		HAL_Delay(10);//At least 10ms delay
    lcd_chkstatus();
    /******FiTi  init****************/

		EPD_W21_WriteCMD(0x4D);        			//FITIinternal code
		EPD_W21_WriteDATA (0xAA);

		EPD_W21_WriteCMD(0x87);        			//FITIinternal code
		EPD_W21_WriteDATA (0x28);

		EPD_W21_WriteCMD(0x88);        			//FITIinternal code
		EPD_W21_WriteDATA (0x80);

		EPD_W21_WriteCMD(0x90);        			//FITIinternal code
		EPD_W21_WriteDATA (0x02);

		EPD_W21_WriteCMD(0x91);        			//FITIinternal code
		EPD_W21_WriteDATA (0x8d);

		EPD_W21_WriteCMD(0xAA);        			//FITIinternal code
		EPD_W21_WriteDATA (0x0f);

		EPD_lut(0);

		EPD_W21_WriteCMD(0xE8);
		EPD_W21_WriteDATA (0xA8);		//A

		EPD_W21_WriteCMD(0x26);
		EPD_W21_WriteDATA (0x0f);		//A

		EPD_W21_WriteCMD(0x04);  // power ON
		lcd_chkstatus();

		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0x1f);		//KW-BF   KWR-AF	BWROTP 0f	BWOTP 1f

		EPD_W21_WriteCMD(0X50);
		EPD_W21_WriteDATA(0x97);

}


void EPD_Init_Part(void)
{
		EPD_W21_RST_0;		// Module reset
		delay_xms(10);//At least 10ms delay 
		EPD_W21_RST_1;
		delay_xms(10);//At least 10ms delay 
    lcd_chkstatus();

		EPD_W21_WriteCMD(0x4D);        			//FITIinternal code
		EPD_W21_WriteDATA (0xAA);

		EPD_W21_WriteCMD(0x87);        			//FITIinternal code
		EPD_W21_WriteDATA (0x28);

		EPD_W21_WriteCMD(0x88);        			//FITIinternal code
		EPD_W21_WriteDATA (0x80);

		EPD_W21_WriteCMD(0x90);        			//FITIinternal code
		EPD_W21_WriteDATA (0x02);

		EPD_W21_WriteCMD(0x91);        			//FITIinternal code
		EPD_W21_WriteDATA (0x8d);

		EPD_W21_WriteCMD(0xAA);        			//FITIinternal code
		EPD_W21_WriteDATA (0x0f);

		EPD_lut(1);

		EPD_W21_WriteCMD(0xE8);         
		EPD_W21_WriteDATA (0xA8);		//A

		EPD_W21_WriteCMD(0x26);         
		EPD_W21_WriteDATA (0x0f);		//A

		EPD_W21_WriteCMD(0x04);  
		lcd_chkstatus();

		EPD_W21_WriteCMD(0x00);			//panel setting
		EPD_W21_WriteDATA(0x1f);		//KW-BF   KWR-AF	BWROTP 0f	BWOTP 1f

		EPD_W21_WriteCMD(0X50);
		EPD_W21_WriteDATA(0xf7);
	}
	
void EPD_DeepSleep(void)
{
		EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0xf7); //WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7	

		EPD_W21_WriteCMD(0X02);  	//power off
	  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
    delay_xms(100);
	  EPD_W21_WriteCMD(0X07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);
}
//Full screen refresh update function
void EPD_Update(void)
{   
	//Refresh
	EPD_W21_WriteCMD(0x12);		//DISPLAY REFRESH 	
	delay_xms(1);	             //!!!The delay here is necessary, 200uS at least!!!     
	lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal
}


void EPD_WhiteScreen_ALL(const unsigned char *datas)
{
    unsigned int i;
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<EPD_ARRAY;i++)	  
    {	
	    EPD_W21_WriteDATA(0xFF);  //Transfer the actual displayed data
    }	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<EPD_ARRAY;i++)	     
	  {
	    EPD_W21_WriteDATA(datas[i]);  //Transfer the actual displayed data
	  }
    EPD_Update();	    


}
void EPD_WhiteScreen_White(void)
{
    unsigned int i;
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<EPD_ARRAY;i++)
    {
	    EPD_W21_WriteDATA(0x00);
    }
	  EPD_W21_WriteCMD(0x11);
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<EPD_ARRAY;i++)
	  {
	    EPD_W21_WriteDATA(0xff);  //Transfer the actual displayed data
			oldData[i]=0xFF;
	  }
	  EPD_W21_WriteCMD(0x11);
    EPD_Update();
}

//Partial refresh of background display, this function is necessary, please do not delete it!!!
void EPD_SetRAMValue_BaseMap( const unsigned char * datas)
{
  unsigned int i;	
  EPD_W21_WriteCMD(0x10);  //write old data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(0xFF);
   }
  EPD_W21_WriteCMD(0x13);  //write new data 
  for(i=0;i<EPD_ARRAY;i++)
   {               
     EPD_W21_WriteDATA(datas[i]);
		  oldData[i]=datas[i]; 
   }	 
    EPD_Update();	    
}

void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
  unsigned int i;
	x_start=x_start-x_start%8;

	  EPD_Init_Part();
	
		EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting
	
		EPD_W21_WriteCMD(0x14);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start    
		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);      //y-start  
		EPD_W21_WriteDATA(PART_LINE);	        //w
		EPD_W21_WriteDATA((PART_COLUMN)/256);	    //l-MSB
		EPD_W21_WriteDATA((PART_COLUMN)%256);	    //l-LSB	
		if(partFlag==1) 
		{
			partFlag=0;
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
				 EPD_W21_WriteDATA(0xFF); 
		}
    else
		{
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
 			  EPD_W21_WriteDATA(oldData[i]); 	 
		}
		  
		EPD_W21_WriteCMD(0x15);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start    
		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start  
		EPD_W21_WriteDATA(PART_LINE);	        //w
		EPD_W21_WriteDATA((PART_COLUMN)/256);	    //l-MSB
		EPD_W21_WriteDATA((PART_COLUMN)%256);	    //l-LSB	

		for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
	 {
		EPD_W21_WriteDATA(datas[i]);
    oldData[i]=datas[i]; 			 
	 } 
		
    		//Refresh
		EPD_W21_WriteCMD(0x16);	//DISPLAY REFRESH 
		EPD_W21_WriteDATA (x_start);   //x-start    
		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start  
		EPD_W21_WriteDATA(PART_LINE);	        //w
		EPD_W21_WriteDATA((PART_COLUMN)/256);	    //l-MSB
		EPD_W21_WriteDATA((PART_COLUMN)%256);	    //l-LSB	

		delay_xms(1);	             //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal  
	  
}

void EPD_Dis_Part_Old(unsigned int x_start,unsigned int y_start,uint8_t * datas,uint8_t * oldDatas,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
  unsigned int i;

  	  	EPD_Init_Part();

		EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting

		EPD_W21_WriteCMD(0x14);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start
		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);      //y-start
		EPD_W21_WriteDATA(PART_LINE);	        //w
		EPD_W21_WriteDATA((PART_COLUMN)/256);	    //l-MSB
		EPD_W21_WriteDATA((PART_COLUMN)%256);	    //l-LSB

		for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
		{
		EPD_W21_WriteDATA(oldDatas[i]);
		}

		EPD_W21_WriteCMD(0x15);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start
		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start
		EPD_W21_WriteDATA(PART_LINE);	        //w
		EPD_W21_WriteDATA((PART_COLUMN)/256);	    //l-MSB
		EPD_W21_WriteDATA((PART_COLUMN)%256);	    //l-LSB

		for(i=0;i<PART_COLUMN*PART_LINE/8;i++)
		{
		EPD_W21_WriteDATA(datas[i]);
		}

    		//Refresh
		EPD_W21_WriteCMD(0x16);	//DISPLAY REFRESH
		EPD_W21_WriteDATA (x_start);   //x-start
		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start
		EPD_W21_WriteDATA(PART_LINE);	        //w
		EPD_W21_WriteDATA((PART_COLUMN)/256);	    //l-MSB
		EPD_W21_WriteDATA((PART_COLUMN)%256);	    //l-LSB

		HAL_Delay(2);	             //!!!The delay here is necessary, 200uS at least!!!
		lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal

}

//Full screen partial refresh display
void EPD_Dis_PartAll(const unsigned char * datas)
{
    unsigned int i;
	  EPD_Init_Part();
	  //Write Data
		EPD_W21_WriteCMD(0x10);	       //Transfer old data
	  for(i=0;i<EPD_ARRAY;i++)	  
    {	
			 EPD_W21_WriteDATA(oldData[i]);  //Transfer the actual displayed data
    }	
		EPD_W21_WriteCMD(0x13);		     //Transfer new data
	  for(i=0;i<EPD_ARRAY;i++)	     
	  {
	    EPD_W21_WriteDATA(datas[i]);  //Transfer the actual displayed data
       oldData[i]=datas[i]; 
	  }  
			
    EPD_Update();	     

}
//Partial refresh write address and data
void EPD_Dis_Part_RAM(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
												const unsigned char * datas_C,const unsigned char * datas_D,const unsigned char * datas_E,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
  unsigned int i;
	x_start=x_start-x_start%8;

	  EPD_Init_Part();
	
		EPD_W21_WriteCMD(0x91);		//This command makes the display enter partial mode
		EPD_W21_WriteCMD(0x90);		//resolution setting
	
		EPD_W21_WriteCMD(0x14);		//resolution setting
		EPD_W21_WriteDATA (x_start);   //x-start    
		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start  
		EPD_W21_WriteDATA(PART_LINE);	        //w
		EPD_W21_WriteDATA((PART_COLUMN*num)/256);	    //l-MSB
		EPD_W21_WriteDATA((PART_COLUMN*num)%256);	    //l-LSB	
		if(partFlag==1) 
		{
			partFlag=0;
			for(i=0;i<PART_COLUMN*PART_LINE*num/8;i++)	     
				 EPD_W21_WriteDATA(0xFF); 
		}
    else
		{
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
				EPD_W21_WriteDATA(oldDataA[i]);  						 
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
				EPD_W21_WriteDATA(oldDataB[i]);  
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
				EPD_W21_WriteDATA(oldDataC[i]);  						 
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
				EPD_W21_WriteDATA(oldDataD[i]);
			for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	     
				EPD_W21_WriteDATA(oldDataE[i]);  						 			 
		} 
 

	  EPD_W21_WriteCMD(0x15);				 //writes New data to SRAM.
		EPD_W21_WriteDATA (x_start);   //x-start    
		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start  
		EPD_W21_WriteDATA(PART_LINE);	        //w
		EPD_W21_WriteDATA((PART_COLUMN*num)/256);	    //l-MSB
		EPD_W21_WriteDATA((PART_COLUMN*num)%256);	    //l-LSB	
		
		for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	
		{			
			EPD_W21_WriteDATA(datas_A[i]);  
			oldDataA[i]=datas_A[i];
		}					
		for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	
		{			
			EPD_W21_WriteDATA(datas_B[i]);  
			oldDataB[i]=datas_B[i];
		}	
		for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	
		{			
			EPD_W21_WriteDATA(datas_C[i]);  
			oldDataC[i]=datas_C[i];
		}	
		for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	
		{			
			EPD_W21_WriteDATA(datas_D[i]);  
			oldDataD[i]=datas_D[i];
		}	
		for(i=0;i<PART_COLUMN*PART_LINE/8;i++)	
		{			
			EPD_W21_WriteDATA(datas_E[i]);  
			oldDataE[i]=datas_E[i]; 
		}	
		//Refresh
		EPD_W21_WriteCMD(0x16);	//DISPLAY REFRESH 
		EPD_W21_WriteDATA (x_start);   //x-start    
		EPD_W21_WriteDATA (y_start/256);
		EPD_W21_WriteDATA (y_start%256);   //y-start  
		EPD_W21_WriteDATA(PART_LINE);	        //w
		EPD_W21_WriteDATA((PART_COLUMN*num)/256);	    //l-MSB
		EPD_W21_WriteDATA((PART_COLUMN*num)%256);	    //l-LSB	

		delay_xms(1);	             //!!!The delay here is necessary, 200uS at least!!!     
		lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal  
		
	  
}
//Clock display
void EPD_Dis_Part_Time(unsigned int x_start,unsigned int y_start,
	                      const unsigned char * datas_A,const unsigned char * datas_B,
												const unsigned char * datas_C,const unsigned char * datas_D,const unsigned char * datas_E,
                        unsigned char num,unsigned int PART_COLUMN,unsigned int PART_LINE)
{
	EPD_Dis_Part_RAM(x_start,y_start,datas_A,datas_B,datas_C,datas_D,datas_E,num,PART_COLUMN,PART_LINE);

}		

////////////////////////////////Other newly added functions////////////////////////////////////////////
//Display rotation 180 degrees initialization
void EPD_Init_180(void)
{	
		EPD_W21_RST_0;		// Module reset
		delay_xms(10);//At least 10ms delay 
		EPD_W21_RST_1;
		delay_xms(10);//At least 10ms delay 
    lcd_chkstatus();
    /******FiTi  init****************/
		EPD_W21_WriteCMD(0x4D);        			//FITIinternal code
		EPD_W21_WriteDATA (0xAA);

		EPD_W21_WriteCMD(0x87);        			//FITIinternal code
		EPD_W21_WriteDATA (0x28);

		EPD_W21_WriteCMD(0x88);        			//FITIinternal code
		EPD_W21_WriteDATA (0x80);

		EPD_W21_WriteCMD(0x90);        			//FITIinternal code
		EPD_W21_WriteDATA (0x02);

		EPD_W21_WriteCMD(0x91);        			//FITIinternal code
		EPD_W21_WriteDATA (0x8d);

		EPD_W21_WriteCMD(0xAA);        			//FITIinternal code
		EPD_W21_WriteDATA (0x0f);

		EPD_lut(0);	

		EPD_W21_WriteCMD(0xE8);         
		EPD_W21_WriteDATA (0xA8);		//A

		EPD_W21_WriteCMD(0x26);         
		EPD_W21_WriteDATA (0x0f);		//A

		EPD_W21_WriteCMD(0x04);  
		lcd_chkstatus();

		EPD_W21_WriteCMD(0x00);
		EPD_W21_WriteDATA(0x13); //180 mirror

		EPD_W21_WriteCMD(0X50);
		EPD_W21_WriteDATA(0x97);
}

void EPD_Display(unsigned char *Image)
{
    unsigned int Width, Height,i,j;
    Width = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    Height = EPD_HEIGHT;

    EPD_W21_WriteCMD(0x10);
    for (j = 0; j < Height; j++) {
        for ( i = 0; i < Width; i++) {
            EPD_W21_WriteDATA(0x00);
        }
    }

    EPD_W21_WriteCMD(0x13);
    for ( j = 0; j < Height; j++) {
        for ( i = 0; i < Width; i++) {
           EPD_W21_WriteDATA(Image[i + j * Width]);
        }
    }
    EPD_Update();	     
}









/***********************************************************
						end file
***********************************************************/


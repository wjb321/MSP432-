#ifndef __OLED_H
#define __OLED_H	

#include "ti/devices/msp432e4/driverlib/inc/hw_gpio.h"
#include "ti/devices/msp432e4/driverlib/driverlib.h"

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//----------------------------------------------------------------------------------
#define		OLED_SSD1306_SCLK						(GPIO_PIN_2)
#define		OLED_SCLK_Set()			        GPIOPinWrite(GPIO_PORTE_BASE, OLED_SSD1306_SCLK, OLED_SSD1306_SCLK)
#define		OLED_SCLK_Clr()							GPIOPinWrite(GPIO_PORTE_BASE, OLED_SSD1306_SCLK, 0)

//----------------------------------------------------------------------------------
#define		OLED_SSD1306_SDIN						(GPIO_PIN_1)
#define		OLED_SDIN_Set()							GPIOPinWrite(GPIO_PORTE_BASE, OLED_SSD1306_SDIN, OLED_SSD1306_SDIN)
#define		OLED_SDIN_Clr()			  			GPIOPinWrite(GPIO_PORTE_BASE, OLED_SSD1306_SDIN, 0)


#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED端口定义----------------  					   
		     

//OLED控制用函数
void OLED_WR_Byte(unsigned char dat,unsigned char cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t);
void OLED_Fill(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char dot);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2);
void OLED_ShowString(unsigned char x,unsigned char y, unsigned char *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowENCN(unsigned char x,unsigned char y,char *chr);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_printf(unsigned char x,unsigned char y,char* fmt,...);
#endif  
	 




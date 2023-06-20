#include <stdarg.h>
#include <stdio.h>	
#include "oled.h"
#include "oledfont.h" 
#include "ti/devices/msp432e4/driverlib/driverlib.h"

//#include "delay.h"
//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 		
unsigned int N_CN;

void IIC_Start()
{
  OLED_SCLK_Set() ;
  OLED_SDIN_Set();
  OLED_SDIN_Clr();
  OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
  OLED_SCLK_Set() ;
  //	OLED_SCLK_Clr();
  OLED_SDIN_Clr();
  OLED_SDIN_Set();
}

void IIC_Wait_Ack()
{

	//GPIOB->CRH &= 0XFFF0FFFF;	//����??PB12?a��?��-��?��??�꨺?
	//GPIOB->CRH |= 0x00080000;
//	OLED_SDA = 1;
//	delay_us(1);
	//OLED_SCL = 1;
	//delay_us(50000);
/*	while(1)
	{
		if(!OLED_SDA)				//?D??��?��??����?��?OLED ��|��eD?o?
		{
			//GPIOB->CRH &= 0XFFF0FFFF;	//����??PB12?a������?��??a��?3??�꨺?
			//GPIOB->CRH |= 0x00030000;
			return;
		}
	}
*/
  OLED_SCLK_Set();
  OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
  unsigned char i;
  unsigned char m,da;
  da=IIC_Byte;
  OLED_SCLK_Clr();
  for(i=0;i<8;i++)		
  {
    m=da;
    //	OLED_SCLK_Clr();
    m=m&0x80;
    if(m==0x80)
    {OLED_SDIN_Set();}
    else OLED_SDIN_Clr();
    da=da<<1;
    OLED_SCLK_Set();
    OLED_SCLK_Clr();
  }
}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
  IIC_Start();
  Write_IIC_Byte(0x78);            //Slave address,SA0=0
  IIC_Wait_Ack();	
  Write_IIC_Byte(0x00);			//write command
  IIC_Wait_Ack();	
  Write_IIC_Byte(IIC_Command); 
  IIC_Wait_Ack();	
  IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
  IIC_Start();
  Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
  IIC_Wait_Ack();	
  Write_IIC_Byte(0x40);			//write data
  IIC_Wait_Ack();	
  Write_IIC_Byte(IIC_Data);
  IIC_Wait_Ack();	
  IIC_Stop();
}

void OLED_WR_Byte(unsigned char dat,unsigned char cmd)
{	
  if(cmd)
  {
    Write_IIC_Data(dat);
  }
  else
  {
    Write_IIC_Command(dat);
  } 	  
} 

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
  OLED_WR_Byte(0xb0+y,OLED_CMD);
  OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
  OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
  OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
  OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
  OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
  OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
  OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
  OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
  unsigned char i,n;		    
  for(i=0;i<8;i++)  
  {  
    OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
    OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
    OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
    for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
  } //������ʾ
}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)
{      	
  unsigned char c=0,i=0;	
  c=chr-' ';//�õ�ƫ�ƺ��ֵ			
  if(x>Max_Column-1){x=0;y=y+2;}
  if(SIZE ==16)
  {
    OLED_Set_Pos(x,y);	
    for(i=0;i<8;i++)
      OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
    OLED_Set_Pos(x,y+1);
    for(i=0;i<8;i++)
      OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
  }
  else
  {	
    OLED_Set_Pos(x,y+1);
    for(i=0;i<6;i++)
      OLED_WR_Byte(F6x8[c][i],OLED_DATA);
  }
}
//m^n����
unsigned int oled_pow(unsigned char m,unsigned char n)
{
  unsigned int result=1;	 
  while(n--)result*=m;    
  return result;
}
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2)
{         	
  unsigned char t,temp;
  unsigned char enshow=0;						   
  for(t=0;t<len;t++)
  {
    temp=(num/oled_pow(10,len-t-1))%10;
    if(enshow==0&&t<(len-1))
    {
      if(temp==0)
      {
        OLED_ShowChar(x+(size2/2)*t,y,' ');
        continue;
      }
      else enshow=1; 
    }
    OLED_ShowChar(x+(size2/2)*t,y,temp+'0'); 
  }
} 
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
  unsigned char j=0;
  while (chr[j]!='\0')
  {
    OLED_ShowChar(x,y,chr[j]);
    x+=8;
    if(x>120){x=0;y+=2;}
    j++;
  }
}

//��ʾ����
void OLED_ShowENCN(unsigned char x,unsigned char y,char *chr)
{
  unsigned char i=0,wordNum=0;	

  while ( *chr != '\0')
  {
    if(x>=128)
    {
      x=0;
      y+=2;
    }
    if(*chr>128)
    {
      for(wordNum=0;wordNum<N_CN;wordNum++)
      {
        if((CN16CHAR[wordNum].Index[0]==*chr)&&(CN16CHAR[wordNum].Index[1]==*(chr+1)))
        {
          OLED_Set_Pos(x,y);

          for (i=0; i<32; i++) //дһ����
          {
            if (i == 16)	 //����16X16�õ�����Y���꣬�����ڵ���16ʱ���л�����
            {
              OLED_Set_Pos(x,y+1);	
            }
            OLED_WR_Byte(CN16CHAR[wordNum].Msk[i],OLED_DATA);
          }
        break;
        }
      }
      x += 16;
      chr += 2;
    }
    else
    {
      OLED_Set_Pos(x,y);	
      for(i=0;i<8;i++)
        OLED_WR_Byte(F8X16[(*chr-' ')*16+i],OLED_DATA);
      OLED_Set_Pos(x,y+1);
      for(i=0;i<8;i++)
        OLED_WR_Byte(F8X16[(*chr-' ')*16+i+8],OLED_DATA);
      x += 8;
      chr += 1;
    }
  }			
}

__align(8) char OLED_BUF[64]; 	//��ʾ����,���64�ֽ�
void OLED_printf(unsigned char x,unsigned char y,char* fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)OLED_BUF,fmt,ap);
	va_end(ap);
	OLED_ShowENCN(x,y,OLED_BUF);
}

//��ʼ��SSD1306					    
void OLED_Init(void)
{
  N_CN = sizeof(CN16CHAR)/sizeof(CN16CHAR[0]);	
  
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2);
	MAP_GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2,
                             GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  OLED_WR_Byte(0xAE,OLED_CMD);//--display off
  OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
  OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
  OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
  OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
  OLED_WR_Byte(0x81,OLED_CMD); // contract control
  OLED_WR_Byte(0xFF,OLED_CMD);//--128   
  OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
  OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
  OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
  OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
  OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
  OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
  OLED_WR_Byte(0x00,OLED_CMD);//
  
  OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
  OLED_WR_Byte(0x80,OLED_CMD);//
  
  OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
  OLED_WR_Byte(0x05,OLED_CMD);//
  
  OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
  OLED_WR_Byte(0xF1,OLED_CMD);//
  
  OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
  OLED_WR_Byte(0x12,OLED_CMD);//
  
  OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
  OLED_WR_Byte(0x30,OLED_CMD);//
  
  OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
  OLED_WR_Byte(0x14,OLED_CMD);//
  
  OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}  


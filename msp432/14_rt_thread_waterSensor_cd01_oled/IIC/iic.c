//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103RCT6,����ԭ��MiniSTM32������,��Ƶ72MHZ������12MHZ
//QDtech-OLEDҺ������ for STM32
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtft.com
//�Ա���վ��http://qdtech.taobao.com
//wiki������վ��http://www.lcdwiki.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//����֧��QQ:3002773612  3002778157
//��������QQȺ:324828016
//��������:2018/9/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================��Դ����================================================//
// OLEDģ��               STM32��Ƭ��
//   VCC         ��       DC 5V/3.3V      //OLED����Դ��
//   GND         ��          GND          //OLED����Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪIIC
// OLEDģ��               STM32��Ƭ��
//   SDA         ��          PB15         //OLED��IIC�����ź�
//=======================================Һ���������߽���==========================================//
// OLEDģ��               STM32��Ƭ��
//   SCL         ��          PB13         //OLED��IICʱ���ź�
//=========================================����������=========================================//
//��ģ�鲻���������ܣ����Բ���Ҫ����������
****************************************************************************************************/	
/***************************************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
****************************************************************************************************/		
#include "iic.h"

/*****************************************************************************
 * @name       :void IIC_Start(void)
 * @date       :2018-09-13 
 * @function   :start iic bus
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void IIC_Start(void)
{
	OLED_SCL_SET();
	OLED_SDA_SET();
	OLED_SDA_CLR();
	OLED_SCL_CLR();
}

/*****************************************************************************
 * @name       :void IIC_Stop(void)
 * @date       :2018-09-13 
 * @function   :stop iic bus
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void IIC_Stop(void)
{
	OLED_SCL_SET();
	OLED_SDA_CLR();
	OLED_SDA_SET();
}

/*****************************************************************************
 * @name       :void IIC_Wait_Ack(void)
 * @date       :2018-09-13 
 * @function   :wait iic ack
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void IIC_Wait_Ack(void)
{
	OLED_SCL_SET();
	OLED_SCL_CLR();
}

/*****************************************************************************
 * @name       :void Write_IIC_Byte(u8 IIC_Byte)
 * @date       :2018-09-13 
 * @function   :Write a byte of content with iic bus
 * @parameters :IIC_Byte
 * @retvalue   :None
******************************************************************************/
void Write_IIC_Byte(u8 IIC_Byte)
{
	u8 i;
	u8 m,da;
	da=IIC_Byte;
	OLED_SCL_CLR();
	for(i=0;i<8;i++)		
	{
		m=da;
		m=m&0x80;
		if(m==0x80)
		{
			OLED_SDA_SET();
		}
		else
		{
			OLED_SDA_CLR();
		}
		da=da<<1;
		OLED_SCL_SET();
		OLED_SCL_CLR();
		}
}

/*****************************************************************************
 * @name       :void Write_IIC_Command(u8 IIC_Command)
 * @date       :2018-09-13 
 * @function   :Write a byte of command to oled screen
 * @parameters :IIC_Command:command to be written
 * @retvalue   :None
******************************************************************************/
void Write_IIC_Command(u8 IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(IIC_SLAVE_ADDR);            //Slave address,SA0=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
	IIC_Stop();
}

/*****************************************************************************
 * @name       :void Write_IIC_Data(u8 IIC_Data)
 * @date       :2018-09-13 
 * @function   :Write a byte of data to oled screen
 * @parameters :IIC_Data:data to be written
 * @retvalue   :None
******************************************************************************/
void Write_IIC_Data(u8 IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(IIC_SLAVE_ADDR);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
	IIC_Stop();
}

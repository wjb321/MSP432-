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
#ifndef _IIC_H_
#define _IIC_H_
//#include "sys.h"
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include "oled.h"

//�����Գ���ʹ�õ������ģ��IIC�ӿ�����
//IIC���������Ŷ����ʱ�����Ŷ��嶼���������޸�
//�޸����Ŷ������Ҫ��Ӧ�޸�oled.c��OLED_Init_GPIO�����������ų�ʼ��

//����IIC���豸��ַ
#define IIC_SLAVE_ADDR 0x78


//--------------IIC�������Ŷ���-----------------------
#define GPIO_OLED_DAT_PORT_BASE       GPIO_PORTE_BASE//OLED��IIC�����ź�
#define GPIO_OLED_DAT_PORT_SYSCTL     SYSCTL_PERIPH_GPIOE  //OLED��IICʱ���ź�
#define GPIO_OLED_DAT_PIN             GPIO_PIN_1  //OLED��IICʱ���ź�

#define GPIO_OLED_SCLK_PORT_BASE       GPIO_PORTE_BASE  //OLED��IICʱ���ź�
#define GPIO_OLED_SCLK_PORT_SYSCTL     SYSCTL_PERIPH_GPIOE  //OLED��IICʱ���ź�
#define GPIO_OLED_SCLK_PIN             GPIO_PIN_2  //OLED��IICʱ���ź�

//--------------IIC�˿ڲ�������---------------------
#define	OLED_SDA_SET()  	  MAP_GPIOPinWrite(GPIO_OLED_DAT_PORT_BASE, GPIO_OLED_DAT_PIN, 0xFF) //GPIO_SetBits(GPIOB,OLED_SDA)
#define	OLED_SDA_CLR()  	  MAP_GPIOPinWrite(GPIO_OLED_DAT_PORT_BASE, GPIO_OLED_DAT_PIN, 0) //GPIO_ResetBits(GPIOB,OLED_SDA) 
  
#define	OLED_SCL_SET()  	  MAP_GPIOPinWrite(GPIO_OLED_SCLK_PORT_BASE, GPIO_OLED_SCLK_PIN, 0xFF)  //GPIO_SetBits(GPIOB,OLED_SCL)    
#define	OLED_SCL_CLR()  	  MAP_GPIOPinWrite(GPIO_OLED_SCLK_PORT_BASE, GPIO_OLED_SCLK_PIN, 0)  //GPIO_ResetBits(GPIOB,OLED_SCL)    

//IIC��������
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Wait_Ack(void);
void Write_IIC_Byte(u8 IIC_Byte);
void Write_IIC_Command(u8 IIC_Command);
void Write_IIC_Data(u8 IIC_Data);

#endif

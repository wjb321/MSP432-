//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RCT6,正点原子MiniSTM32开发板,主频72MHZ，晶振12MHZ
//QDtech-OLED液晶驱动 for STM32
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/9/13
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================电源接线================================================//
// OLED模块               STM32单片机
//   VCC         接       DC 5V/3.3V      //OLED屏电源正
//   GND         接          GND          //OLED屏电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为IIC
// OLED模块               STM32单片机
//   SDA         接          PB15         //OLED屏IIC数据信号
//=======================================液晶屏控制线接线==========================================//
// OLED模块               STM32单片机
//   SCL         接          PB13         //OLED屏IIC时钟信号
//=========================================触摸屏接线=========================================//
//本模块不带触摸功能，所以不需要触摸屏接线
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
//////////////////////////////////////////////////////////////////////////////////	 
//
//存储图片数据，图片大小为128*64像素
//逐行式，顺向（高位在前）
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef __BMP_H
#define __BMP_H
unsigned char BMP2[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x7F,0xE0,0x03,0x91,0x1C,0x38,0x18,0x00,0x70,0x00,0xFF,0xFC,0x00,0x07,0xFF,0xFE,
	0x66,0x60,0x04,0x5B,0x22,0x44,0x14,0x01,0x8C,0x01,0x7F,0xFA,0x00,0x04,0x00,0x02,
	0x36,0xC0,0x08,0x15,0x40,0x80,0x52,0x02,0x02,0x01,0xBF,0xF6,0x00,0x3D,0xB6,0xDA,
	0x1F,0x80,0x88,0x11,0x40,0x80,0x34,0x04,0x71,0x01,0xDF,0xEE,0x00,0x25,0xB6,0xDA,
	0x0F,0x02,0x88,0x11,0x40,0x80,0x18,0x00,0x88,0x01,0xE0,0x1E,0x00,0x25,0xB6,0xDA,
	0x06,0x0A,0x88,0x11,0x40,0x80,0x34,0x01,0x04,0x01,0xDF,0xEE,0x00,0x25,0xB6,0xDA,
	0x06,0x2A,0x88,0x11,0x40,0x80,0x52,0x00,0x20,0x01,0xBF,0xF6,0x00,0x3D,0xB6,0xDA,
	0x06,0xAA,0x84,0x51,0x22,0x44,0x14,0x00,0x70,0x01,0x7F,0xFA,0x00,0x04,0x00,0x02,
	0x06,0xAA,0x83,0x91,0x1C,0x38,0x18,0x00,0x20,0x00,0xFF,0xFC,0x00,0x07,0xFF,0xFE,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x1F,0xFC,0x00,0x3F,0xFC,0x7F,0xF0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x07,0x3F,0xFE,0x00,0x7F,0xFC,0xFF,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0F,0x30,0x06,0x00,0x60,0x00,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x1B,0x30,0x06,0x00,0x60,0x00,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x33,0x30,0x06,0x00,0x60,0x00,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x63,0x30,0x06,0x18,0x60,0x00,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xC3,0x30,0x06,0x18,0x7F,0xFC,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x83,0x30,0x06,0x00,0x7F,0xFC,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x3F,0xFE,0x00,0x00,0x0C,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x3F,0xFE,0x00,0x00,0x0C,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x30,0x06,0x00,0x00,0x0C,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x30,0x06,0x18,0x00,0x0C,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x30,0x06,0x18,0x00,0x0C,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x30,0x06,0x00,0x00,0x0C,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x30,0x06,0x00,0x60,0x0C,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x30,0x06,0x00,0x60,0x0C,0xC0,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x3F,0xFE,0x00,0x7F,0xFC,0xFF,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x1F,0xFC,0x00,0x3F,0xF8,0x7F,0xF0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xF9,0xE3,0x0F,0x00,0xF1,0xE0,0x1E,0x3C,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x01,0x0A,0x15,0x10,0x81,0x0A,0x10,0x21,0x42,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x12,0x11,0x10,0x81,0x0A,0x00,0x21,0x40,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x22,0x11,0x1F,0x81,0x0B,0xE0,0x21,0x7C,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x42,0x11,0x10,0x81,0x0A,0x10,0x21,0x42,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x82,0x11,0x10,0x99,0x0A,0x13,0x21,0x42,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x01,0xF9,0xE7,0xCF,0x18,0xF1,0xE3,0x1E,0x3C,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x41,0x1C,0x41,0x41,0x00,0x00,0x00,0x00,0x81,0x00,0x00,0x00,0x00,0x82,0x7C,0x82,
	0x63,0x22,0x61,0x41,0x00,0x00,0x00,0x00,0xF1,0x00,0x00,0x00,0x00,0xC6,0x82,0xC2,
	0x55,0x41,0x51,0x41,0x00,0x00,0x00,0x00,0x81,0x00,0x00,0x00,0x00,0xAA,0x80,0xA2,
	0x49,0x7E,0x49,0x41,0x00,0x00,0x00,0x00,0xFD,0x00,0x00,0x00,0x00,0x92,0x7C,0x92,
	0x41,0x40,0x45,0x41,0x00,0x00,0x00,0x00,0x81,0x00,0x00,0x00,0x00,0x82,0x02,0x8A,
	0x41,0x21,0x43,0x22,0x00,0x00,0x00,0x00,0xF1,0x00,0x00,0x00,0x00,0x82,0x82,0x86,
	0x41,0x1E,0x41,0x1C,0x00,0x00,0x00,0x00,0x81,0x00,0x00,0x00,0x00,0x82,0x7C,0x82,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

unsigned char BMP3[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0xF8,0x03,0xFF,0xF8,0x03,0xC0,0xF0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0F,0xFE,0x03,0xFF,0xF8,0x07,0xF3,0xFC,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x18,0x03,0x03,0x00,0x00,0x0F,0xFF,0xFE,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x30,0x01,0x83,0x00,0x00,0x1F,0xFF,0xFF,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC3,0x00,0x00,0x1F,0xFF,0xFF,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC3,0x00,0x00,0x1F,0xFF,0xFF,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC3,0x00,0x00,0x0F,0xFF,0xFE,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC3,0x00,0x00,0x0F,0xFF,0xFE,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x30,0x01,0x83,0x7F,0xC0,0x07,0xFF,0xFC,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x30,0x03,0x03,0xFF,0xF0,0x03,0xFF,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x18,0x06,0x03,0x80,0x38,0x01,0xFF,0xF0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0F,0xFC,0x03,0x00,0x18,0x00,0x7F,0xC0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x1F,0xFF,0x00,0x00,0x0C,0x00,0x3F,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x30,0x01,0x80,0x00,0x0C,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC0,0x00,0x0C,0x00,0x04,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC0,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC0,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC0,0x00,0x0C,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC0,0x00,0x0C,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC6,0x00,0x0C,0x1E,0x38,0xCC,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0x00,0xC7,0x00,0x1C,0x11,0x45,0x32,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x30,0x01,0x83,0x80,0x38,0x11,0x45,0x22,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x1F,0xFF,0x01,0xFF,0xF0,0x11,0x45,0x22,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0F,0xFE,0x00,0x7F,0xC0,0x11,0x45,0x22,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x79,0x22,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x22,0x00,0x90,0x04,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x02,0x40,0x42,0x00,0x90,0x04,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x06,0x40,0x41,0x01,0x08,0x08,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x04,0x20,0x81,0x01,0x08,0x08,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x08,0x20,0x81,0x02,0x04,0x10,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x08,0x20,0x80,0x82,0x04,0x10,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x10,0x21,0x00,0x82,0x02,0x10,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x20,0x11,0x00,0x84,0x02,0x10,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x40,0x12,0x00,0x44,0x02,0x20,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x80,0x12,0x00,0x48,0x01,0x20,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x00,0x48,0x01,0x20,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x30,0x01,0x20,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x30,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

unsigned char BMP4[] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x03,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x00,0x0C,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x00,0x0F,0xC0,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x00,0x1F,0xFE,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x00,0x3F,0xFF,0xFF,0x00,0x00,0x10,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x07,0x00,0x7F,0xFF,0xFF,0xFF,0xC0,0x10,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x06,0x00,0xFF,0xFF,0xFF,0xFF,0xE0,0x10,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x06,0x03,0xFF,0xFF,0xFF,0xFF,0xE0,0x20,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x06,0x0F,0xFF,0xFF,0xFF,0xFF,0xE0,0x60,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x06,0x3F,0xFF,0xFF,0xFF,0xFF,0xF0,0xC0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x07,0x3C,0x3F,0xFF,0xF8,0x7F,0xF1,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x07,0x3F,0xFF,0xFF,0xFF,0xFF,0xF1,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x3F,0xFF,0xFF,0xFF,0xFF,0xF3,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x20,0x00,0xFF,0x00,0x07,0xF2,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x0F,0xFF,0x7E,0xFF,0xFB,0xE7,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x9F,0x7F,0x81,0xFD,0xFC,0x0F,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0xBE,0x3F,0x9D,0xF8,0xFD,0xFF,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xDF,0x7F,0xBC,0xFD,0xFB,0xFF,0x80,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x67,0xFE,0x7E,0x7F,0xE3,0xFF,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x38,0x01,0xFF,0x80,0x0F,0xFE,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x07,0xFE,0x00,0x7F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xC7,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x0F,0x80,0x00,0x00,0x00,0x01,0x83,0x80,0x61,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x0F,0x80,0xF0,0x00,0x00,0x07,0x82,0xE3,0xE1,0xB0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x0F,0x80,0x1C,0x00,0x00,0x0C,0x6C,0x02,0x3F,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x0E,0x00,0x03,0x00,0x00,0x00,0xFE,0x00,0x3F,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x06,0x00,0xF1,0x80,0x00,0x0F,0x81,0xF7,0xC0,0x7C,0x00,0x00,0x00,
	0x00,0x00,0x00,0x03,0x80,0x18,0x80,0x00,0x03,0xFF,0x80,0xFF,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x01,0xC0,0x0C,0x40,0x00,0x02,0x18,0x81,0x8C,0x60,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xE1,0x84,0x40,0x00,0x02,0x18,0x81,0x8C,0x60,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x7F,0xC2,0x40,0x00,0x03,0xFF,0x81,0xFF,0xE0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x3F,0xE2,0x40,0x00,0x02,0x00,0x31,0x80,0x0C,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x0F,0xC0,0x00,0x00,0x03,0xFF,0xF0,0xFF,0xFC,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xC0,0x7F,0xF0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

//////////////////////////////////////////////////////////////////////////////////	 
//
//存储图片数据，图片大小为51*32像素
//逐行式，顺向（高位在前）
//
/////////////////////////////////////////////////////////////////////////////////
unsigned char BMP5[] =
{
	0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,
	0x0E,0x00,0x00,0x00,0x00,0x01,0x80,0x0E,0x00,0x20,0x00,0x00,0x01,0xC0,0x00,0x00,
	0x70,0x00,0x00,0x00,0xC0,0x00,0x00,0xE0,0x00,0x00,0x00,0xE0,0x3F,0x81,0xC0,0x00,
	0x00,0x00,0x61,0xFF,0xF0,0x80,0x00,0x00,0x00,0x03,0xC0,0xF8,0x00,0x00,0x00,0x00,
	0x07,0x00,0x1C,0x00,0x00,0x00,0x00,0x1E,0x00,0x0F,0x00,0x00,0x00,0x7C,0x1C,0x00,
	0x03,0x1F,0x80,0x00,0x7C,0x1C,0x07,0xFF,0x1F,0x80,0x00,0x7C,0x1C,0x1F,0xFF,0x9F,
	0x80,0x00,0x00,0x1C,0x7C,0x03,0xF8,0x00,0x00,0x00,0x0F,0xF0,0x00,0x7C,0x00,0x00,
	0x03,0xFF,0x00,0x00,0x0F,0xE0,0x00,0x0F,0xF2,0x00,0x00,0x07,0xFE,0x00,0x1F,0x80,
	0x00,0x00,0x00,0x7F,0x80,0x3C,0x00,0x00,0x00,0x00,0x03,0x80,0x7C,0x00,0x00,0x00,
	0x00,0x03,0xC0,0x70,0x00,0x00,0x00,0x00,0x01,0xC0,0x70,0x00,0x00,0x00,0x00,0x01,
	0xC0,0x78,0x00,0x00,0x00,0x00,0x01,0xC0,0x7C,0x00,0x00,0x00,0x00,0x03,0xC0,0x3C,
	0x00,0x00,0x00,0x00,0x07,0x80,0x3E,0x00,0x00,0x00,0x00,0x3F,0x80,0x0F,0xE1,0xC0,
	0x00,0x1F,0xFC,0x00,0x03,0xFF,0xFC,0x03,0xFF,0xF0,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
	0x00,0x00,0x00,0x00,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x01,0xFC,0x00,0x00,0x00,
};

unsigned char BMP6[] = 
{
   0xd8,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,
	 0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd8,0xd7,0xd7,0xd7,0xd7,0xd7,
	 0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd7,0xd8,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd9,0xd8,
	 0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,
	 0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,
	 0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xe7,0x52,0x99,0x6d,0xd4,0xcf,0xca,0xc8,0xca,
	 0xca,0xce,0xd4,0xee,0xed,0xe8,0xed,0xea,0xe9,0xe7,0xe7,0xe7,0xe7,0xe7,0xe7,0xe8,
	 0xe0,0xde,0xc7,0xc8,0xc8,0xc8,0xc8,0xc8,0xc8,0xc8,0xc8,0xc8,0xc8,0xc8,0xc8,0xc8,
	 0xf3,0xea,0xea,0xea,0xeb,0xec,0xea,0xea,0xea,0xea,0xea,0xea,0xea,0xea,0xea,0xea,
	 0xeb,0xea,0xea,0xeb,0xea,0xea,0xea,0xed,0xea,0xe9,0xf2,0xf8,0xf7,0xf6,0xf6,0xf9,
	 0xf9,0xf6,0xf7,0xf6,0xf6,0xf6,0xf7,0xec,0xea,0xea,0xea,0xea,0xea,0xea,0xea,0xee,
	 0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,
	 0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,
	 0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xff,0x56,0xa7,0x6d,0xf9,0xaa,0xef,0xf4,0xe6,
	 0xec,0xbd,0xee,0xd4,0xc7,0xf3,0xc3,0xde,0xe4,0xf0,0xee,0xee,0xee,0xee,0xee,0xee,
	 0xef,0xf0,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,
	 0xee,0xed,0xf6,0xf3,0xf1,0xdd,0xfa,0xf5,0xf2,0xf4,0xee,0xf2,0xf6,0xf3,0xf4,0xf5,
	 0xeb,0xf3,0xf4,0xed,0xf2,0xf3,0xfb,0xdc,0xf5,0xf0,0xfc,0xf6,0xff,0xff,0xff,0xdc,
	 0xed,0xff,0xff,0xff,0xff,0xff,0xff,0xf2,0xfc,0xf3,0xf3,0xf3,0xf4,0xf5,0xf3,0xec,
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xff,0x55,0xa6,0x6f,0xd5,0xe2,0xc8,0xf5,0xea, 
	 0xbc,0x4c,0xe2,0x73,0x3e,0xff,0x18,0x80,0xf0,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xed,0xe9,0xc0,0xe1,0xed,0xce,0xa2,0xca,0xf3,0xd6,0xf4,0xd3,0xbc,0xe2,0xda,0xd6, 
	 0xd9,0xe5,0xdb,0xbf,0xed,0xe5,0x97,0xb6,0xea,0xe7,0xff,0x9e,0x98,0xbd,0xba,0xf1, 
	 0xb4,0xc0,0xae,0x97,0xc3,0xa5,0xd6,0xff,0x6e,0xe7,0xe3,0xdc,0xde,0xc2,0xdc,0xee, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xff,0x55,0xa6,0x6f,0xd7,0xe2,0xc9,0xf5,0xea, 
	 0xbf,0x4c,0xe3,0x7a,0x47,0xff,0x1a,0x86,0xf0,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xed,0xf3,0x80,0x92,0x7d,0xbd,0xca,0xb4,0x72,0x84,0xd7,0xd1,0xbb,0x4f,0x81,0x5d, 
	 0x95,0xb5,0x75,0x9e,0xa7,0x8c,0xbc,0xbe,0x80,0xa8,0xff,0xb1,0xc8,0xc1,0xdb,0xe0, 
	 0xab,0xb7,0xd2,0x97,0xbe,0xc7,0xd1,0xff,0x92,0xa4,0x73,0x7b,0x5f,0x92,0xa4,0xf3, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xff,0x55,0xa6,0x6f,0xe5,0x9d,0xde,0xf3,0xe7,
	 0xd2,0x6a,0xea,0xa1,0x85,0xff,0x60,0xa3,0xec,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xed,0xeb,0xe1,0xed,0xea,0xe3,0xe9,0xeb,0xec,0xeb,0xeb,0xf1,0xe6,0xf0,0xf1,0xe1, 
	 0xe5,0xf1,0xe9,0xe2,0xf1,0xe5,0xec,0xe1,0xf0,0xf0,0xf9,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf3,0xe5,0xf3,0xb3,0xee,0xe6,0xe7,0xe6,0xed, 
	 0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef, 
	 0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xef, 
	 0xef,0xef,0xef,0xef,0xef,0xef,0xef,0xff,0x55,0xa6,0x6c,0xff,0x8e,0xed,0xf2,0xe3, 
	 0xff,0x6c,0xfa,0xe8,0x87,0xfc,0xa9,0xea,0xe5,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xf4,0xf8,0xf7,0xf7,0xf8,0xf7,0xf7,0xf7,0xf7,0xf6,0xf6,0xf7,0xf7,0xf7,0xf8, 
	 0xf8,0xf7,0xf8,0xf8,0xf7,0xf8,0xf7,0xf8,0xf7,0xf5,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfa,0xf7,0xf7,0xfc,0xf8,0xf8,0xf8,0xf7,0xf6, 
	 0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6, 
	 0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6, 
	 0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xf6,0xff,0x55,0xa6,0x6c,0xff,0xec,0xe8,0xf2,0xe3, 
	 0xfa,0x94,0xf6,0xd6,0xad,0xf5,0xcc,0xd2,0xe6,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xf5,0xd7,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda, 
	 0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xd9,0xd8,0xd8,0xd8,0xd8,0xd8, 
	 0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd8,0xd9,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda, 
	 0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda, 
	 0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda,0xda, 
	 0xda,0xda,0xda,0xda,0xda,0xda,0xd8,0xfa,0x56,0xa6,0x6c,0xff,0x8e,0xeb,0xf2,0xe3, 
	 0xf8,0x78,0xfa,0xc2,0xdf,0xf5,0x96,0xdd,0xe6,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xed,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xfe,0xff,0xff,0xff,0xf3,0xf4,0xf7,0x56,0xa6,0x6c,0xff,0x9f,0xf4,0xf1,0xe3, 
	 0xf7,0x98,0xf7,0xcb,0xaf,0xfa,0x84,0xee,0xe5,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xed,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xfd,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xff, 
	 0xfe,0xf0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xfb,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xfd,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xfb,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xfb,0xff,0xff,0xff,0xe2,0xe6,0xf9,0x56,0xa6,0x6c,0xff,0xc4,0xee,0xf1,0xe3, 
	 0xf9,0x85,0xf7,0xd5,0xc9,0xf9,0x84,0xc3,0xe8,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xee,0xfd,0x9e,0xe0,0xc3,0xd6,0xdd,0xf0,0xff,0xb2,0xbc,0xe6,0xaf,0xfc,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x71, 
	 0xe9,0xd5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xbb,0xa5,0xfc,0xc3,0xed,0xff,0xff,0xff,0x84,0xe4,0xde,0xf4,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xc6,0xc2,0xdb,0xdb,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xfb,0xff,0xff,0xff,0xbc,0xbf,0xfc,0x56,0xa6,0x6c,0xff,0x8b,0xf5,0xf1,0xe3, 
	 0xf9,0x91,0xf5,0xe1,0xb9,0xf6,0xb0,0xe4,0xe5,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xef,0xfa,0x81,0x79,0xd6,0x4d,0x90,0x93,0xff,0xb8,0xca,0x49,0xc9,0xfb,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x6f, 
	 0x8a,0xce,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xc4,0xbc,0x8f,0x91,0xd3,0xff,0xff,0xff,0x9d,0x8d,0x7f,0xf2,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xd0,0x6f,0xa5,0xa3,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xfb,0xff,0xff,0xff,0xf4,0xf5,0xf7,0x56,0xa6,0x6c,0xff,0xa8,0xf8,0xf1,0xe4, 
	 0xef,0x82,0xf9,0xbe,0xb5,0xf5,0xc1,0xda,0xe6,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xed,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfb,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	 0xff,0xff,0xfb,0xff,0xff,0xff,0xce,0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xff,0xff,
	 0xff,0xff,0xff,0xff,0xff,0xfb,0xff,0xff,0xff,0xdb,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xfb,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x6c,0xff,0x73,0xf8,0xf1,0xe4, 
	 0xeb,0xb9,0xf1,0xe4,0xb8,0xfb,0x76,0xf8,0xe4,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xed,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfa,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfa,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xfa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfa,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xfa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xfa,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x6c,0xff,0x98,0xf4,0xf1,0xe3, 
	 0xf2,0xf6,0xf0,0xab,0xc2,0xfa,0x75,0xed,0xe4,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xed,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xed,0xff,0xff,0xff,0xff,0xff,0xff,0xf5,0xfb,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xee,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xed,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xef,0xff,0xff,0xff,0xee,0xff,0xff,0xff,0xff,0xff,0xff,0xec,0xff,0xff,0xff,0xff, 
	 0xf1,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x6f,0xd3,0xff,0xf0,0xf1,0xe3, 
	 0xf1,0xf0,0xf1,0xa0,0xbf,0xee,0xfb,0xf2,0xe3,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xee,0xff,0x9e,0xe7,0xff,0xff,0xff,0xff,0xff,0xb8,0xb8,0xed,0x9d,0xff,0x89, 
	 0x94,0xff,0xce,0x8b,0xeb,0xd5,0xe8,0xe6,0xff,0xe0,0xf7,0xc9,0xea,0xd8,0xff,0xa8, 
	 0xbf,0xd7,0xc3,0xd7,0x86,0xb4,0xfa,0x85,0xb2,0xff,0xc8,0xff,0xe6,0xe9,0xe9,0xf6, 
	 0xcb,0xcf,0xff,0xc9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xcc,0xee,0x98,0x82,0xff, 
	 0xc1,0xe6,0xff,0xbe,0xcc,0xff,0xdd,0xf9,0xac,0xb0,0xd0,0xde,0xe6,0xf1,0xc9,0xec, 
	 0xd7,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x6d,0xfe,0x81,0xf6,0xf1,0xe3, 
	 0xf1,0xf0,0xe9,0xf8,0xf5,0xe9,0xf0,0xf1,0xe3,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xed,0xff,0xac,0xdf,0xff,0xff,0xff,0xff,0xff,0xc5,0x8a,0xfc,0x72,0xfc,0xa0, 
	 0x99,0xff,0xcc,0xbf,0xe5,0xb0,0xa6,0xb5,0xe6,0x74,0xd5,0xa1,0xaf,0xdd,0xff,0x9b, 
	 0xb0,0xd7,0x8c,0xd8,0x9f,0xc6,0xd5,0x71,0xd8,0xff,0x71,0xed,0xa8,0xaf,0x82,0xf2, 
	 0x81,0xbd,0xff,0xcb,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xc8,0xe2,0xa7,0xa6,0xff, 
	 0x7d,0x83,0xff,0x74,0xb2,0xff,0xe2,0xe5,0xc0,0x9d,0xbd,0xe9,0x68,0xc4,0xa9,0xab, 
	 0xdc,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x6c,0xff,0x77,0xfc,0xf1,0xe3, 
	 0xf1,0xf0,0xe9,0xf0,0xf0,0xe9,0xf0,0xf1,0xe3,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xed,0xff,0xf3,0xff,0xff,0xff,0xff,0xff,0xff,0xf4,0xfe,0xfa,0xfd,0xfb,0xff, 
	 0xf6,0xfd,0xf9,0xf9,0xff,0xf5,0xfe,0xf8,0xfd,0xfd,0xf8,0xff,0xeb,0xff,0xff,0xf5, 
	 0xf9,0xfa,0xfe,0xfb,0xff,0xf3,0xff,0xf8,0xff,0xff,0xf4,0xff,0xf4,0xff,0xf7,0xfe, 
	 0xff,0xf2,0xff,0xfb,0xfc,0xff,0xff,0xff,0xff,0xff,0xff,0xf9,0xfa,0xee,0xfe,0xff, 
	 0xf5,0xf8,0xfe,0xff,0xef,0xff,0xfc,0xfa,0xf3,0xff,0xfd,0xf6,0xff,0xf6,0xff,0xf3,
	 0xf9,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x6c,0xff,0x92,0xf9,0xf1,0xe3, 
	 0xf1,0xf0,0xe9,0xf0,0xf0,0xe9,0xf0,0xf1,0xe3,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xed,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xf2,0xff,0xff,0xff,0xff,0xff,0xff,0xf6,0xfe,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf3,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xf2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0xfc, 
	 0xf9,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf4,0xff,0xf2,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x6c,0xff,0x99,0xf9,0xf1,0xe3, 
	 0xf1,0xf0,0xe9,0xf0,0xf0,0xe9,0xf0,0xf1,0xe3,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xee,0xff,0xab,0xf4,0xff,0xff,0xff,0xff,0xff,0xba,0xbf,0xec,0xa7,0xff,0x94, 
	 0x9e,0xf4,0xd3,0x93,0xed,0xd8,0xf2,0xf3,0xff,0xf3,0xfe,0xcf,0xf8,0xd7,0xff,0xae, 
	 0xc2,0xd9,0xca,0xda,0x93,0xbf,0xe2,0xad,0xb3,0xff,0xd6,0xfc,0xf4,0xf6,0xf7,0xf5, 
	 0xda,0xd3,0xff,0xcc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xd4,0xa9,0xe5,0xce,0xfb, 
	 0xd5,0xff,0xff,0xff,0xff,0xff,0xe3,0x76,0xff,0xbe,0xe7,0xd5,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x6c,0xff,0x68,0xf7,0xf1,0xe3,
	 0xf1,0xf0,0xe9,0xf0,0xf0,0xe9,0xf0,0xf1,0xe3,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xed,0xff,0x82,0xe2,0xff,0xff,0xff,0xff,0xff,0xd3,0x8f,0xff,0x76,0xff,0x9d,
	 0xb8,0xe3,0xd7,0xc3,0xe5,0xb0,0xa6,0xb4,0xeb,0x6f,0xda,0x9c,0xb0,0xdd,0xff,0xa8, 
	 0xba,0xde,0x91,0xde,0x9b,0xc9,0xe2,0xa6,0xd6,0xff,0x6c,0xf4,0xac,0xa7,0x86,0xf6, 
	 0x7d,0xbe,0xff,0xd0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xd4,0xa9,0xe9,0x9d,0xad, 
	 0xdc,0xff,0xff,0xff,0xff,0xff,0xe2,0xaa,0xfc,0xb1,0x87,0xc9,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x6c,0xff,0xef,0xf1,0xf1,0xe3, 
	 0xf1,0xf0,0xe9,0xf0,0xf0,0xe9,0xf0,0xf1,0xe3,0xf1,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0, 
	 0xea,0xed,0xfe,0xed,0xf8,0xff,0xff,0xff,0xff,0xff,0xe2,0xf2,0xf3,0xef,0xf6,0xf6,
	 0xe3,0xfd,0xef,0xed,0xff,0xee,0xf5,0xeb,0xf8,0xf0,0xec,0xff,0xdc,0xff,0xff,0xe2, 
	 0xec,0xf0,0xf2,0xf3,0xf5,0xf1,0xf0,0xf1,0xfe,0xff,0xe8,0xfa,0xe2,0xfe,0xe5,0xfa, 
	 0xf8,0xe9,0xff,0xf3,0xf9,0xff,0xff,0xff,0xff,0xff,0xff,0xed,0xfa,0xff,0xf6,0xe4,
	 0xf9,0xff,0xff,0xff,0xff,0xff,0xf1,0xde,0xff,0xed,0xf7,0xec,0xff,0xff,0xff,0xff,
	 0xff,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x6c,0xff,0xf3,0xf2,0xf3,0xe6, 
	 0xf4,0xf3,0xec,0xf3,0xf3,0xec,0xf3,0xf3,0xe6,0xf4,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,
	 0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,0xf2,
	 0xea,0xed,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xff,0xff,0xff,0xff,0xf6,0xff,0xff,0xff,0xff,0xff,0xff,0xf7,0xff,0xff,0xff,
	 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf7,0xff,0xff,0xff,0xff,0xff, 
	 0xff,0xf7,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, 
	 0xf5,0xff,0xff,0xff,0xf4,0xff,0xff,0xff,0xff,0xff,0xff,0xf6,0xff,0xff,0xff,0xfb,
	 0xf9,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa6,0x66,0xe5,0xd8,0xd6,0xd7,0xce,
	 0xda,0xd9,0xd1,0xd7,0xd6,0xd9,0xe0,0xdd,0xce,0xdb,0xd8,0xd6,0xd6,0xd6,0xd6,0xd5,
	 0xd5,0xd6,0xd6,0xd6,0xd6,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,
	 0xea,0xee,0xff,0x95,0xf8,0xff,0xff,0xff,0xff,0xff,0xbc,0xc6,0xeb,0xb1,0xff,0xa1,
	 0x91,0xff,0xd4,0x9b,0xee,0xda,0xfc,0xff,0xff,0xff,0xff,0xd5,0xff,0xd6,0xff,0xb3,
	 0xc5,0xdb,0xd0,0xdc,0xa0,0xd1,0xfb,0xb3,0xb6,0xff,0xe4,0xf9,0xff,0xff,0xff,0xf5,
	 0xe8,0xd8,0xff,0xd0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xd3,0xea,0xa7,0xbf,0xff,
	 0xd8,0xff,0xff,0xdb,0xd9,0xff,0xe0,0xfa,0xb0,0xba,0xd0,0xd9,0xff,0xff,0xd4,0xff, 
	 0xd4,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa5,0x7b,0xc0,0xc9,0xe7,0xe0,0xc3, 
	 0xb4,0xcd,0xe2,0xde,0xe5,0x98,0x82,0xb0,0xc9,0xad,0xd4,0xe4,0xe0,0xdc,0xda,0xe8, 
	 0xea,0xed,0xff,0x9f,0xdf,0xff,0xff,0xff,0xff,0xff,0xe2,0x93,0xff,0x79,0xff,0x9e, 
	 0x9d,0xe8,0xdf,0xc6,0xe4,0xb0,0xa6,0xb4,0xef,0x6a,0xdf,0x97,0xb1,0xdd,0xff,0xb4, 
	 0xc4,0xe5,0x95,0xe3,0x9b,0x9d,0xdb,0xa7,0xb2,0xff,0x66,0xfb,0xb0,0x9e,0x8a,0xfb, 
	 0x78,0xbe,0xff,0xd4,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xd7,0xf4,0xdb,0xb3,0xff, 
	 0x72,0x86,0xff,0x6b,0xb3,0xff,0xe9,0xf3,0xdd,0xc5,0xe5,0xe7,0x5e,0xce,0x9f,0xac, 
	 0xdd,0xff,0xff,0xff,0xff,0xef,0xf0,0xf7,0x56,0xa4,0x80,0xcd,0xc7,0xea,0xc7,0xda, 
	 0xc1,0xc7,0xe2,0xcc,0xff,0x87,0x4b,0xa0,0xdb,0xbe,0xcb,0xda,0xd0,0xeb,0xf2,0xe2, 
	 0xd5,0xe3,0xea,0xdb,0xe8,0xfd,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb, 
	 0xea,0xee,0xfe,0xcf,0xff,0xff,0xff,0xff,0xff,0xff,0xd1,0xe7,0xec,0xe1,0xf0,0xed, 
	 0xd4,0xfb,0xe4,0xe1,0xff,0xe7,0xeb,0xdd,0xf3,0xe4,0xdf,0xff,0xcc,0xfd,0xff,0xcf,
	 0xde,0xe7,0xe7,0xea,0xeb,0xea,0xf6,0xd0,0xe8,0xff,0xdb,0xf6,0xcf,0xfa,0xd2,0xf5, 
 
};
	
#endif



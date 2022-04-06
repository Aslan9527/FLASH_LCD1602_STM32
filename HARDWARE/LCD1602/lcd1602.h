#ifndef __lcd1602_H
#define __lcd1602_H	 

#include "stm32f10x.h"
#include "delay.h"

/********************各端口定义*********************************/
#define GPIO_EN       GPIOC                 //  使能端口组
#define GPIO_EN_PIN   GPIO_Pin_7            //  使能端口号
#define RCC_GPIO_EN   RCC_APB2Periph_GPIOC  //  使能时钟组

#define GPIO_RW       GPIOC                 //  读/写选择端口组
#define GPIO_RW_PIN   GPIO_Pin_6            //  读/写选择端口号
#define RCC_GPIO_RW   RCC_APB2Periph_GPIOC  //  读/写时钟组

#define GPIO_RS       GPIOC                 //  数据/命令端口组
#define GPIO_RS_PIN   GPIO_Pin_5            //  数据/命令端口号
#define RCC_GPIO_RS   RCC_APB2Periph_GPIOC  //  数据/命令时钟组

#define GPIO_DATA_0       GPIOD         //  数据线0_端口组
#define GPIO_DATA_0_PIN   GPIO_Pin_0    //  数据线0_端口号
#define GPIO_DATA_1       GPIOD         //  数据线1_端口组
#define GPIO_DATA_1_PIN   GPIO_Pin_1    //  数据线1_端口号
#define GPIO_DATA_2       GPIOD         //  数据线2_端口组
#define GPIO_DATA_2_PIN   GPIO_Pin_2   //  数据线2_端口号
#define GPIO_DATA_3       GPIOD         //  数据线3_端口组
#define GPIO_DATA_3_PIN   GPIO_Pin_3   //  数据线3_端口号
#define GPIO_DATA_4       GPIOD         //  数据线4_端口组
#define GPIO_DATA_4_PIN   GPIO_Pin_4   //  数据线4_端口号
#define GPIO_DATA_5       GPIOD         //  数据线5_端口组
#define GPIO_DATA_5_PIN   GPIO_Pin_5   //  数据线5_端口号
#define GPIO_DATA_6       GPIOD         //  数据线6_端口组
#define GPIO_DATA_6_PIN   GPIO_Pin_6   //  数据线6_端口号
#define GPIO_DATA_7       GPIOD         //  数据线7_端口组
#define GPIO_DATA_7_PIN   GPIO_Pin_7   //  数据线7_端口号
#define RCC_GPIO_DATA   RCC_APB2Periph_GPIOD  //  数据线时钟组


/******************************************************************/


/***********************基本指令***********************************/
#define SET_EN  GPIO_SetBits(GPIO_EN, GPIO_EN_PIN)		//EN 使能  输出1
#define CLE_EN  GPIO_ResetBits(GPIO_EN, GPIO_EN_PIN)	//      输出0 
#define SET_RW  GPIO_SetBits(GPIO_RW, GPIO_RW_PIN)      //RW 读写  输出1
#define CLE_RW  GPIO_ResetBits(GPIO_RW, GPIO_RW_PIN)	//      输出0
#define SET_RS  GPIO_SetBits(GPIO_RS, GPIO_RS_PIN)		//RS 指令  输出1
#define CLE_RS  GPIO_ResetBits(GPIO_RS, GPIO_RS_PIN)	//      输出0
/******************************************************************/

void Lcd_GPIO_init(void);
void Lcd_Init( void ) ;
void Lcd_En_Toggle(void);
void Lcd_Busy(void);
void Gpio_data(unsigned char x);
void Lcd_Write_Command(unsigned char x,char Busy);
void Lcd_Write_Data( unsigned char x); 
void Lcd_SetXY(unsigned char x,unsigned char y);
void Lcd_Puts(unsigned char x,unsigned char y, unsigned char *string);
void Lcd_1Put(unsigned char x,unsigned char y, unsigned char Data0);

		 				    
#endif

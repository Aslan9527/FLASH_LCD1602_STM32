#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE核心板
//按键驱动代码	   
							  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PEin(4)  //PE4
//#define KEY1 PEin(3)	//PE3 


#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1


 

#define KEY0_PRES 	1	//KEY0按下
#define KEY1_PRES	2	//KEY1按下



void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif

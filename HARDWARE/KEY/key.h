#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F103ZE���İ�
//������������	   
							  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PEin(4)  //PE4
//#define KEY1 PEin(3)	//PE3 


#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����1


 

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	2	//KEY1����



void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif

#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//LED��������	   				
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PE1 BEEP , PE5 LEDΪ�����.��ʹ��ʱ��		    
//LED IO��ʼ��
void LED_Beep_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_5;				 //LED1-->PE.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 
}
 

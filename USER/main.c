#include "led.h"
#include "lcd1602.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "stmflash.h"

/************************************************
 FLASHģ��EEPROM �ܶ��MCU������������Ƭ��EEPROM��
 ����������ʱ����ڳɱ��Ŀ����ֲ�������EEPROM��
 ���Ծ�����Flash��ģ��EEPROM�洢
 W25Q16
************************************************/
char tab0[16];  
char tab1[16];  
//Ҫд�뵽STM32 FLASH���ַ�������
u8 TEXT_Buffer[]={"LiDongChuang"};
#define SIZE sizeof(TEXT_Buffer)		//���鳤��
#define FLASH_SAVE_ADDR  0X08070000		//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)

 int main(void)
 {	 
	u8 key,flash_add;
	u8 a=0;
	u16 i=0;
	u16 write_len;
	u8 datatemp[SIZE];

	delay_init();	    	//��ʱ������ʼ��	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
 	LED_Beep_Init();		//��ʼ����LED��Beep���ӵ�Ӳ���ӿ�
	KEY_Init();					//��ʼ������KEY0 PE4      KEY1 PE3
  Lcd_GPIO_init();    //��ʼ����lcdҺ����ʾ���ӵ�Ӳ���ӿ�
	Lcd_Init();	        //��ʼ��lcdҺ����ʾ
  sprintf(tab0,"KEY1��W KEY0��R");
	Lcd_Puts(0,0,(unsigned char *)tab0);
	delay_ms(2000); 
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)	//KEY1����,д��STM32 FLASH
		{
		
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
						
			sprintf(tab1,"Write Finished!");
	    Lcd_Puts(0,1,(unsigned char *)tab1);//��ʾ�������
			Beep=0;
		}
		if(key==KEY0_PRES)	//KEY0����,��ȡ�ַ�������ʾ
		{

			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
			
			sprintf(tab0,"Data: ");
	    Lcd_Puts(0,0,(unsigned char *)tab0);//��ʾ�������
	    Lcd_Puts(0,1,(unsigned char *)datatemp);//��ʾ�������ַ���
			Beep=0;
		}
				 
				if(USART_RX_STA&0x8000)
		  {					   
			  USART_RX_STA=0;			
				if(USART_RX_BUF[0]==0xFF)
         {
           flash_add =USART_RX_BUF[1]+FLASH_SAVE_ADDR;
           write_len = USART_RX_BUF[2];
					 for(a=0;a<write_len;a++)
					 {					
					   TEXT_Buffer[a]=USART_RX_BUF[a+3];
					 }
           STMFLASH_Write(flash_add,(u16*)TEXT_Buffer,SIZE);
					 STMFLASH_Read(flash_add,(u16*)datatemp,SIZE);
           
           printf("�ɹ���FLASH��ַд������\r\n");
           sprintf(tab0,"WriteData: ");
	         Lcd_Puts(0,0,(unsigned char *)tab0);
	         Lcd_Puts(0,1,(unsigned char *)datatemp);//��ʾ�������ַ���
           Beep=0;           
         }
			         //�����ݿ���
         if(USART_RX_BUF[0] ==0x00)
         {
           flash_add =USART_RX_BUF[1]+FLASH_SAVE_ADDR;
           STMFLASH_Read(flash_add,(u16*)datatemp,5);        
           printf("�ɹ���FLASH��ַ��������\r\n");
					 sprintf(tab0,"ReadData: ");
					 Lcd_Puts(0,0,(unsigned char *)tab0);
	         Lcd_Puts(0,1,(unsigned char *)datatemp);//��ʾ�������ַ���
           Beep=0; 
         }
			
			
		}
		
		i++;
		delay_ms(10);  
		if(i==100)
		{
			LED1=!LED1;//��ʾϵͳ��������
      Beep=1;			
			i=0;
		}		   
	} 
}



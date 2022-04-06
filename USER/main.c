#include "led.h"
#include "lcd1602.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "stmflash.h"

/************************************************
 FLASH模拟EEPROM 很多的MCU控制器不带有片上EEPROM，
 但是我们有时候鉴于成本的考虑又不想外扩EEPROM，
 所以经常用Flash来模拟EEPROM存储
 W25Q16
************************************************/
char tab0[16];  
char tab1[16];  
//要写入到STM32 FLASH的字符串数组
u8 TEXT_Buffer[]={"LiDongChuang"};
#define SIZE sizeof(TEXT_Buffer)		//数组长度
#define FLASH_SAVE_ADDR  0X08070000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)

 int main(void)
 {	 
	u8 key,flash_add;
	u8 a=0;
	u16 i=0;
	u16 write_len;
	u8 datatemp[SIZE];

	delay_init();	    	//延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	//串口初始化为115200
 	LED_Beep_Init();		//初始化与LED和Beep连接的硬件接口
	KEY_Init();					//初始化按键KEY0 PE4      KEY1 PE3
  Lcd_GPIO_init();    //初始化与lcd液晶显示连接的硬件接口
	Lcd_Init();	        //初始化lcd液晶显示
  sprintf(tab0,"KEY1：W KEY0：R");
	Lcd_Puts(0,0,(unsigned char *)tab0);
	delay_ms(2000); 
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)	//KEY1按下,写入STM32 FLASH
		{
		
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
						
			sprintf(tab1,"Write Finished!");
	    Lcd_Puts(0,1,(unsigned char *)tab1);//提示传送完成
			Beep=0;
		}
		if(key==KEY0_PRES)	//KEY0按下,读取字符串并显示
		{

			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
			
			sprintf(tab0,"Data: ");
	    Lcd_Puts(0,0,(unsigned char *)tab0);//提示传送完成
	    Lcd_Puts(0,1,(unsigned char *)datatemp);//显示读到的字符串
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
           
           printf("成功往FLASH地址写入数据\r\n");
           sprintf(tab0,"WriteData: ");
	         Lcd_Puts(0,0,(unsigned char *)tab0);
	         Lcd_Puts(0,1,(unsigned char *)datatemp);//显示读到的字符串
           Beep=0;           
         }
			         //读数据控制
         if(USART_RX_BUF[0] ==0x00)
         {
           flash_add =USART_RX_BUF[1]+FLASH_SAVE_ADDR;
           STMFLASH_Read(flash_add,(u16*)datatemp,5);        
           printf("成功从FLASH地址读出数据\r\n");
					 sprintf(tab0,"ReadData: ");
					 Lcd_Puts(0,0,(unsigned char *)tab0);
	         Lcd_Puts(0,1,(unsigned char *)datatemp);//显示读到的字符串
           Beep=0; 
         }
			
			
		}
		
		i++;
		delay_ms(10);  
		if(i==100)
		{
			LED1=!LED1;//提示系统正在运行
      Beep=1;			
			i=0;
		}		   
	} 
}



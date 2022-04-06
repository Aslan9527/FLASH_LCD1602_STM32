#include "lcd1602.h"

/************************端口初始化*******************************/
void Lcd_GPIO_init(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;   //声明结构体

    /********Data端口设置*************/
	 RCC_APB2PeriphClockCmd(RCC_GPIO_DATA, ENABLE);  //打开端口D时钟 
     GPIO_InitStructure.GPIO_Pin  = GPIO_DATA_0_PIN|GPIO_DATA_1_PIN|GPIO_DATA_2_PIN|GPIO_DATA_3_PIN|GPIO_DATA_4_PIN|GPIO_DATA_5_PIN|GPIO_DATA_6_PIN|GPIO_DATA_7_PIN; //  DB8~DB15
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //标准输出模式
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M时钟速度
     GPIO_Init(GPIO_DATA_0, &GPIO_InitStructure);      //初始化端口

//**All notes can be deleted and modified**//

	 /********读/写端口设置**********/
	 RCC_APB2PeriphClockCmd(RCC_GPIO_RW, ENABLE);    //打开端口时钟 
     GPIO_InitStructure.GPIO_Pin =  GPIO_RW_PIN;     // 使能端口
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //标准输出模式
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M时钟速度
     GPIO_Init(GPIO_RW, &GPIO_InitStructure);

	 /********指令/数据端口设置**********/
	 RCC_APB2PeriphClockCmd(RCC_GPIO_RS, ENABLE);    //打开端口时钟 
     GPIO_InitStructure.GPIO_Pin =  GPIO_RS_PIN;     // 使能端口
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽复用输出
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M时钟速度
     GPIO_Init(GPIO_RS, &GPIO_InitStructure);


}
/******************************************************************/



void Lcd_Init( void )  //初始化
{  
 	Lcd_GPIO_init();
	delay_us(1500);                     //延时15ms
	Lcd_Write_Command( 0x38,0);       // 写指令38H 不检测忙信号
	delay_us(500);				      //延时5ms
    Lcd_Write_Command( 0x38,0);       // 写指令38H 不检测忙信号
	delay_us(500);					  //延时5ms
    Lcd_Write_Command( 0x38,0);       // 写指令38H 不检测忙信号
   									  //以后每次写指令、读/写数据操作之前需检测忙信号
	Lcd_Write_Command( 0x38,1);       //显示模式设置 
    Lcd_Write_Command( 0x08,1);		  //显示关闭
	Lcd_Write_Command( 0x01,1);       //显示清屏
    Lcd_Write_Command( 0x06,1);       //显示光标移动设置 
    Lcd_Write_Command( 0x0C,1); 	  //显示开、光标不显示
} 
/******************************************************/

void Lcd_En_Toggle(void) //发使能脉冲
{
	SET_EN;        //使能1
	delay_us(5);   //延时160us
	CLE_EN;
}


void Lcd_Busy(void)//判断忙
{
	 unsigned int later0=0;
     GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_GPIO_DATA, ENABLE);    //打开DATA端口时钟 

     GPIO_InitStructure.GPIO_Pin  = GPIO_DATA_0_PIN|GPIO_DATA_1_PIN|GPIO_DATA_2_PIN|GPIO_DATA_3_PIN|GPIO_DATA_4_PIN|GPIO_DATA_5_PIN|GPIO_DATA_6_PIN|GPIO_DATA_7_PIN; //  DB8~DB15
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //输入模式 = 上拉输入
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M时钟速度
     GPIO_Init(GPIO_DATA_7, &GPIO_InitStructure);      //打开忙检测端口

 	 CLE_RS; //RS = 0//**All notes can be deleted and modified**//
	 //delay_us(2);   //延时20us
     while ((GPIO_ReadInputDataBit(GPIO_DATA_7,GPIO_DATA_7_PIN))&&(later0<20000)) //循环等待忙检测端口 = 0
	 {
	 	delay_us(5);
		later0++;	
	 }
	 CLE_EN; //EN = 0

     //恢复端口为输出状态 
   	 RCC_APB2PeriphClockCmd(RCC_GPIO_DATA, ENABLE);    //打开DATA端口时钟 
	 GPIO_InitStructure.GPIO_Pin  = GPIO_DATA_0_PIN|GPIO_DATA_1_PIN|GPIO_DATA_2_PIN|GPIO_DATA_3_PIN|GPIO_DATA_4_PIN|GPIO_DATA_5_PIN|GPIO_DATA_6_PIN|GPIO_DATA_7_PIN; //  DB8~DB15
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //50M时钟速度
     GPIO_Init(GPIO_DATA_7, &GPIO_InitStructure);

} 

void Gpio_data(unsigned char x)  //端口置入数据
{  
GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_0_PIN);  //DB0
GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_1_PIN);  //DB1
GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_2_PIN);  //DB2
GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_3_PIN);  //DB3
GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_4_PIN);  //DB4
GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_5_PIN);  //DB5
GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_6_PIN);  //DB6
GPIO_ResetBits(GPIO_DATA_0, GPIO_DATA_7_PIN);  //DB7
if(x&0X01)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_0_PIN);//DB0
if(x&0X02)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_1_PIN);//DB1
if(x&0X04)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_2_PIN);//DB2
if(x&0X08)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_3_PIN);//DB3
if(x&0X10)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_4_PIN);//DB4
if(x&0X20)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_5_PIN);//DB5
if(x&0X40)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_6_PIN);//DB6
if(x&0X80)GPIO_SetBits(GPIO_DATA_0, GPIO_DATA_7_PIN);//DB7
}


//向液晶里面写入指令  时序：RS=L,RW=L,Data0-Data7=指令码，E=高脉冲
void Lcd_Write_Command(unsigned char x,char Busy) 
{ 
    if(Busy) Lcd_Busy();
    //delay_us(1);   //延时10us
	CLE_RS;  //RS = 0 
    //delay_us(1);   //延时10us
	CLE_RW;  //RW = 0 
    //delay_us(4);   //延时40us
    Gpio_data(x);  //端口置入数据
    //delay_us(4);   //延时40us
	Lcd_En_Toggle();  //发使能脉冲
    //delay_us(1);   //延时100us
	Lcd_Busy(); //测忙

}
//向液晶里面写入数据  时序：RS=H,RW=L,Data0-Data7=指令码，E=高脉冲
void Lcd_Write_Data( unsigned char x) //向液晶里面写入数据 
{ 
	Lcd_Busy(); //测忙
    //delay_us(1);   //延时10us
	SET_RS;   //RS = 1 
    //delay_us(1);   //延时10us
    CLE_RW;   //RW = 0
    //delay_us(4);   //延时40us
    Gpio_data(x);
    //delay_us(4);   //延时40us
	Lcd_En_Toggle();  //发使能脉冲
    //delay_us(1);   //延时100us
	Lcd_Busy(); //测忙

} 

void Lcd_SetXY(unsigned char x,unsigned char y)   //字符初始位置设定，x表示列，y表示行 
{ 
     unsigned char addr; 
     if(y==0) 
          addr=0x80+x; 
     else if(y==1)
          addr=0xC0+x; 
     Lcd_Write_Command(addr,1) ; 
} 
/******************************************************/

void Lcd_Puts(unsigned char x,unsigned char y, unsigned char *string) //向1602写一个字符串 
{ 
   //unsigned char i=0;
   Lcd_SetXY(x,y); 
	while(*string) 
	  { 
	   Lcd_Write_Data(*string); 
       string++; 
      } 
}

void Lcd_1Put(unsigned char x,unsigned char y, unsigned char Data0)
{
   	Lcd_SetXY(x,y); 
	Lcd_Write_Data(Data0); 
}


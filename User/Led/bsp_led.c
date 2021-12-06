/**
  ******************************************************************************
	*	@file    bsp_led.c
	* @author	 Wu
	* @brief   led应用函数接口
  ******************************************************************************
  * @attention
	*
  * 硬件连接关系：															        *
  *						     C4   ---------  LED1            			*
  *						     C5   ---------  LED2	 								*
  *						 	   C6   ---------  LED3	 								*
  *						 	   C7   ---------  LED4	 								*
	*						     C8   ---------  LED5            			*
  *						     C9   ---------  LED6	 								*
  *						 	   C10  ---------  LED7	 								*
  *						 	   C11  ---------  LED8	 								*

**************************************************************************************
*/
  
#include "bsp_led.h"
#include "universe.h"

int LEDcount=0;		//全局变量，代表LED灯的数量

 /**
  * @brief  初始化控制LED的IO
  */
void LED_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOB和GPIOF的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); 

	/*选择要控制的GPIOB引脚*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;	

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIOC*/
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	/* 关闭所有led灯	*/
	GPIO_SetBits(GPIOC, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
}


 /**
  * @brief  根据调速函数传递的数值更改LED灯的数量
  */
void LEDchange(int status)
{
	if(status==1)                   //判断传参是1、-1或0
	{
		LEDcount = LEDcount + 1;
	}
	else if(status==-1)
	{
		LEDcount = LEDcount - 1;
	}
	else if(status==0)
	{
		LEDcount = 0;
	}
	switch(LEDcount)
	{
		case 0:
			GPIO_SetBits(GPIOC, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);     //灯全灭
			break;
		case 1:
			LED1_ON;
			GPIO_SetBits(GPIOC, GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
			break;
		case 2:
			LED2_ON;
			GPIO_SetBits(GPIOC, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
			break;
		case 3:
			LED3_ON;
			GPIO_SetBits(GPIOC, GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
			break;
		case 4:
			LED4_ON;
			GPIO_SetBits(GPIOC, GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
			break;
		case 5:
			LED5_ON;
			GPIO_SetBits(GPIOC, GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
			break;
		case 6:
			LED6_ON;
			GPIO_SetBits(GPIOC, GPIO_Pin_10|GPIO_Pin_11);
			break;
		case 7:
			LED7_ON;
			GPIO_SetBits(GPIOC, GPIO_Pin_11);
			break;
		case 8:
			LED8_ON;
			break;
	}
}

 /**
  * @brief  超速时，LED灯闪烁报警
  */
void LEDalert()
{
	LED1_TOGGLE;		//LED翻转
	LED2_TOGGLE;
	LED3_TOGGLE;
	LED4_TOGGLE;
	LED5_TOGGLE;
	LED6_TOGGLE;
	LED7_TOGGLE;
	LED8_TOGGLE;

	Delay(1000);		//延时

	LED1_TOGGLE;		//LED翻转
	LED2_TOGGLE;
	LED3_TOGGLE;
	LED4_TOGGLE;
	LED5_TOGGLE;
	LED6_TOGGLE;
	LED7_TOGGLE;
	LED8_TOGGLE;
	
	Delay(1000);		//延时
}

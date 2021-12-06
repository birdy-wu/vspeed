/**
  ******************************************************************************
  * @file    buzzer.c
  * @author  Wu
  * @brief   蜂鸣器应用接口
  ******************************************************************************
  * @attention
  *
  *	硬件连接关系：													  		      *
  *						 	   D4   ---------  J58  								*
  *
  ******************************************************************************
  */

#include "buzzer.h"

 /**
  * @brief  初始化控制蜂鸣器的IO
	* @author  Wu
  */
void BUZZER_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOD外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); 

	/*选择要控制的GPIOD引脚*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIOC*/
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	/* 停响蜂鸣器 */
	GPIO_SetBits(GPIOD, GPIO_Pin_4);
}

void Buzzeralert_start()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_4);
}

void Buzzeralert_stop()
{
	GPIO_SetBits(GPIOD, GPIO_Pin_4);
}

/************************END OF FILE************************/

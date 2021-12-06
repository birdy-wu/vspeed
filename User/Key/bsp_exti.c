/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  Wu
  * @brief   I/O线中断应用bsp
  ******************************************************************************
  * @attention
  *
  *	硬件连接关系：													  		      *
  *						 	   E5   ---------  KEY1 								*
  *						 	   E4   ---------  KEY2	 								*
  *						 	   E3   ---------  KEY3	 								*
  *
  ******************************************************************************
  */
  
#include "bsp_exti.h"
#include "misc.h"
#include "stm32f10x_exti.h"

 /**
  * @brief  配置嵌套向量中断控制器NVIC
	* @author Wu
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  配置 PE5 为线中断口，并设置中断优先级
  * @author Wu
  */
void EXTI_PE_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,ENABLE);
												
	/* 配置 NVIC */
	NVIC_Configuration();

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
	
	/* EXTI 配置GPIO模式*/	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // 上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* EXTI 配置GPIO模式*/
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource5); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

/************************END OF FILE************************/


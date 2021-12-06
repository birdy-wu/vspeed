/**
  ******************************************************************************
  * @file    bsp_pwm_output.c
  * @author  Wu
  * @brief   PWM输出驱动直流电机，并写出调速函数供中断调用
  ******************************************************************************
  * @attention
  *
  *	硬件连接关系：													  		      *
  *						 	   A1   ---------  PWM_A 								*
  *						 	   GND  ---------  DIR_A	 							*
  *                GND  ---------  EN_A                 *
  ******************************************************************************
  */

#include "bsp_pwm_output.h" 
#include "bsp_led.h"

extern int alert;

/* PWM信号电平跳变值 */
u16 CCR1_Val = 500;		//通道一作为测试
u16 CCR2_Val = 200;   //通道二A1口作为调速PWM输出，CCR2_Val取初值200


 /**
  * @brief  配置TIM2复用输出PWM时用到的I/O
	* @author Wu
  */
static void TIM2_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* 设置TIM2CLK 为 72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

  /* 开GPIOA的时钟 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA 配置： TIM2 通道一、二作为复用推挽*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  配置TIM2输出的PWM信号的模式，如周期、极性、占空比
  * @author Wu
  */
static void TIM2_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* 时基配置 */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //当定时器从0计数到999，即为1000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Prescaler = 0;	    //设置预分频：不预分频，即为72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频(这里用不到)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 模式配置：通道1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变，此通道作为测试用
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //使能通道1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 模式配置：通道2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置跳变值，输出另外一个占空比的PWM，此通道作为实际调速使用
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	  //使能通道2
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* TIM2 使能 */
  TIM_Cmd(TIM2, ENABLE); 
}


/**
  * @brief  speedup,speeddown,stop三个函数分别对应增速、减速、停止
  * @author Wu
  */
void speedup(void)
{
	if(CCR2_Val!=1000)
	{
	  CCR2_Val= CCR2_Val +100;		//增大电平跳变值，增加高电平的时间
	  TIM2_Mode_Config();	        //重配PWM输出
		LEDchange(1);               //调用LED改变数目的函数，增加显示的速度档位
	}
	else
	{
		alert = 1;
	}
}

void speeddown(void)
{
	if(CCR2_Val!=200)
	{
	  CCR2_Val= CCR2_Val -100;  //减小电平跳变值，减少高电平的时间
	  TIM2_Mode_Config();	
		LEDchange(-1);            //调用LED改变数目的函数，减少显示的速度档位
	}
	if(alert==1)
	{
		alert = 0;
	}
}

void stop(void)
{
	CCR2_Val= 100;
	TIM2_Mode_Config();	
	if(alert==1)
	{
		alert = 0;
	}
}

/**
  * @brief  TIM2 输出PWM信号初始化，只要调用这个函数
  *         TIM2的四个通道就会有PWM信号输出
  */
void TIM2_PWM_Init(void)
{
	TIM2_GPIO_Config();
	TIM2_Mode_Config();	
}

/************************END OF FILE************************/

/**
  ******************************************************************************
  * @file    bsp_pwm_output.c
  * @author  Wu
  * @brief   PWM�������ֱ���������д�����ٺ������жϵ���
  ******************************************************************************
  * @attention
  *
  *	Ӳ�����ӹ�ϵ��													  		      *
  *						 	   A1   ---------  PWM_A 								*
  *						 	   GND  ---------  DIR_A	 							*
  *                GND  ---------  EN_A                 *
  ******************************************************************************
  */

#include "bsp_pwm_output.h" 
#include "bsp_led.h"

extern int alert;

/* PWM�źŵ�ƽ����ֵ */
u16 CCR1_Val = 500;		//ͨ��һ��Ϊ����
u16 CCR2_Val = 200;   //ͨ����A1����Ϊ����PWM�����CCR2_Valȡ��ֵ200


 /**
  * @brief  ����TIM2�������PWMʱ�õ���I/O
	* @author Wu
  */
static void TIM2_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	/* ����TIM2CLK Ϊ 72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

  /* ��GPIOA��ʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA ���ã� TIM2 ͨ��һ������Ϊ��������*/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  ����TIM2�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
  * @author Wu
  */
static void TIM2_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* ʱ������ */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 0;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* PWM1 ģʽ���ã�ͨ��1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //��������ֵ�������������������ֵʱ����ƽ�������䣬��ͨ����Ϊ������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 ģʽ���ã�ͨ��2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //��������ֵ���������һ��ռ�ձȵ�PWM����ͨ����Ϊʵ�ʵ���ʹ��
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	  //ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* TIM2 ʹ�� */
  TIM_Cmd(TIM2, ENABLE); 
}


/**
  * @brief  speedup,speeddown,stop���������ֱ��Ӧ���١����١�ֹͣ
  * @author Wu
  */
void speedup(void)
{
	if(CCR2_Val!=1000)
	{
	  CCR2_Val= CCR2_Val +100;		//�����ƽ����ֵ�����Ӹߵ�ƽ��ʱ��
	  TIM2_Mode_Config();	        //����PWM���
		LEDchange(1);               //����LED�ı���Ŀ�ĺ�����������ʾ���ٶȵ�λ
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
	  CCR2_Val= CCR2_Val -100;  //��С��ƽ����ֵ�����ٸߵ�ƽ��ʱ��
	  TIM2_Mode_Config();	
		LEDchange(-1);            //����LED�ı���Ŀ�ĺ�����������ʾ���ٶȵ�λ
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
  * @brief  TIM2 ���PWM�źų�ʼ����ֻҪ�����������
  *         TIM2���ĸ�ͨ���ͻ���PWM�ź����
  */
void TIM2_PWM_Init(void)
{
	TIM2_GPIO_Config();
	TIM2_Mode_Config();	
}

/************************END OF FILE************************/

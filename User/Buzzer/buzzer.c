/**
  ******************************************************************************
  * @file    buzzer.c
  * @author  Wu
  * @brief   ������Ӧ�ýӿ�
  ******************************************************************************
  * @attention
  *
  *	Ӳ�����ӹ�ϵ��													  		      *
  *						 	   D4   ---------  J58  								*
  *
  ******************************************************************************
  */

#include "buzzer.h"

 /**
  * @brief  ��ʼ�����Ʒ�������IO
	* @author  Wu
  */
void BUZZER_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOD����ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIOD����*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   

	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIOC*/
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	/* ͣ������� */
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

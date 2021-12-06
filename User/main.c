/**
  ******************************************************************************
  *	@file    main.c
  * @author	 Wu
  * @brief   �������ļ�
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "bsp_pwm_output.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_key.h" 
#include "universe.h"
#include "buzzer.h"

#define CLI()      __set_PRIMASK(1)		/* �ر����ж� */  
#define SEI()			 __set_PRIMASK(0)		/* �������ж� */ 

int alert = 0;		//����ȫ�ֱ���

/**
  * @brief  ������
  * @author Wu
  */
int main(void)
{	
	int i = 0;
	char passwd[4] = {'B','0','6','C'};		//�����������
	char user[4] = {'G','G','G','G'};			//�����û����룬��ʼֵ��ΪG
	char key_test;

	BUZZER_GPIO_Config();
	Key_GPIO_Config();	

	while(1)                            
	{	   
		key_test = pressedkey();	//ɨ����󰴼�
		if(key_test!='G')					//�����������м�����
		{
			Buzzeralert_start();		//������ʾ��
			user[i] = key_test;
			i = i+1;
			Delay(300);
			Buzzeralert_stop();
		}
		if(user[3]!='G')					//����û�����4λ����
		{
			if(user[0]==passwd[0]&&user[1]==passwd[1]&&user[2]==passwd[2]&&user[3]==passwd[3]) break;   //���������ȷ������ѭ�����������г���
		}
	}
	
	CLI();	//�ر����ж�
	SEI();	//�������ж�
	
	/* LED GPIO ��ʼ��*/
  LED_GPIO_Config();	
	
	/* EXTI ���� */
	EXTI_PE_Config();	//��E3��E4��E5��Ϊ�����жϵ�GPIO��
	
	/* TIM2 PWM�������ʼ��,��ʹ��TIM2 PWM��� */
	TIM2_PWM_Init();
	
	/* �ȴ��жϣ�������Ƿ�Ӧ�ñ��� */
	while (1)
	{
		if(alert==1)
		{
			LEDalert();						//LED��˸����
			Buzzeralert_start();	//��������������
		}
		else
    {
		  Buzzeralert_stop();
		}
	}
}

/************************END OF FILE************************/

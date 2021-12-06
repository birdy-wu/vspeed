/**
  ******************************************************************************
	*	@file    bsp_led.c
	* @author	 Wu
	* @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
	*
  * Ӳ�����ӹ�ϵ��															        *
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

int LEDcount=0;		//ȫ�ֱ���������LED�Ƶ�����

 /**
  * @brief  ��ʼ������LED��IO
  */
void LED_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOB��GPIOF������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;	

	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIOC*/
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	/* �ر�����led��	*/
	GPIO_SetBits(GPIOC, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
}


 /**
  * @brief  ���ݵ��ٺ������ݵ���ֵ����LED�Ƶ�����
  */
void LEDchange(int status)
{
	if(status==1)                   //�жϴ�����1��-1��0
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
			GPIO_SetBits(GPIOC, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);     //��ȫ��
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
  * @brief  ����ʱ��LED����˸����
  */
void LEDalert()
{
	LED1_TOGGLE;		//LED��ת
	LED2_TOGGLE;
	LED3_TOGGLE;
	LED4_TOGGLE;
	LED5_TOGGLE;
	LED6_TOGGLE;
	LED7_TOGGLE;
	LED8_TOGGLE;

	Delay(1000);		//��ʱ

	LED1_TOGGLE;		//LED��ת
	LED2_TOGGLE;
	LED3_TOGGLE;
	LED4_TOGGLE;
	LED5_TOGGLE;
	LED6_TOGGLE;
	LED7_TOGGLE;
	LED8_TOGGLE;
	
	Delay(1000);		//��ʱ
}

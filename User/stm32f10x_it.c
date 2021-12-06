/**
  ******************************************************************************
  * @file    stm32f10x_it.c
  * @author  Wu
  * @brief   ���������˰����жϷ�����
  ******************************************************************************
  */

#include "stm32f10x_it.h"
#include "stm32f10x_exti.h"
#include "bsp_pwm_output.h"
#include "bsp_led.h"
#include "universe.h"

/**
  * @brief  This function handles NMI exception.
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  */
void SysTick_Handler(void)
{

}

/**
  * @brief  �˲���ʵ���жϵ��õ�����١����١�ֹͣ�����Ĺ���
  * @author Wu
  */
void EXTI9_5_IRQHandler(void)								//E5����
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		speedup();                              //����
		Delay(5);
		EXTI_ClearITPendingBit(EXTI_Line5);     //����жϱ�־λ
	}  
}
void EXTI4_IRQHandler(void)									//E4����
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		speeddown();                            //����
		Delay(5);
		EXTI_ClearITPendingBit(EXTI_Line4);
}
}
void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)	//E3����
	{
		stop();                                 //ͣת
    LEDchange(0);
		Delay(5);
		EXTI_ClearITPendingBit(EXTI_Line3);
  }
}


/************************END OF FILE************************/

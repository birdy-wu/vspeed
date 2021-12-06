/**
  ******************************************************************************
  * @file    stm32f10x_it.c
  * @author  Wu
  * @brief   在最后添加了按键中断服务函数
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
  * @brief  此部分实现中断调用电机增速、减速、停止函数的功能
  * @author Wu
  */
void EXTI9_5_IRQHandler(void)								//E5按键
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET) //确保是否产生了EXTI Line中断
	{
		speedup();                              //增速
		Delay(5);
		EXTI_ClearITPendingBit(EXTI_Line5);     //清除中断标志位
	}  
}
void EXTI4_IRQHandler(void)									//E4按键
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		speeddown();                            //减速
		Delay(5);
		EXTI_ClearITPendingBit(EXTI_Line4);
}
}
void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)	//E3按键
	{
		stop();                                 //停转
    LEDchange(0);
		Delay(5);
		EXTI_ClearITPendingBit(EXTI_Line3);
  }
}


/************************END OF FILE************************/

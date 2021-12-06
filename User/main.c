/**
  ******************************************************************************
  *	@file    main.c
  * @author	 Wu
  * @brief   工程主文件
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "bsp_pwm_output.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_key.h" 
#include "universe.h"
#include "buzzer.h"

#define CLI()      __set_PRIMASK(1)		/* 关闭总中断 */  
#define SEI()			 __set_PRIMASK(0)		/* 开放总中断 */ 

int alert = 0;		//报警全局变量

/**
  * @brief  主函数
  * @author Wu
  */
int main(void)
{	
	int i = 0;
	char passwd[4] = {'B','0','6','C'};		//定义密码变量
	char user[4] = {'G','G','G','G'};			//定义用户密码，初始值均为G
	char key_test;

	BUZZER_GPIO_Config();
	Key_GPIO_Config();	

	while(1)                            
	{	   
		key_test = pressedkey();	//扫描矩阵按键
		if(key_test!='G')					//如果矩阵键盘有键按下
		{
			Buzzeralert_start();		//按键提示音
			user[i] = key_test;
			i = i+1;
			Delay(300);
			Buzzeralert_stop();
		}
		if(user[3]!='G')					//如果用户输完4位密码
		{
			if(user[0]==passwd[0]&&user[1]==passwd[1]&&user[2]==passwd[2]&&user[3]==passwd[3]) break;   //如果密码正确，跳出循环，正常运行程序
		}
	}
	
	CLI();	//关闭总中断
	SEI();	//开放总中断
	
	/* LED GPIO 初始化*/
  LED_GPIO_Config();	
	
	/* EXTI 配置 */
	EXTI_PE_Config();	//以E3、E4、E5作为按键中断的GPIO口
	
	/* TIM2 PWM波输出初始化,并使能TIM2 PWM输出 */
	TIM2_PWM_Init();
	
	/* 等待中断，并检测是否应该报警 */
	while (1)
	{
		if(alert==1)
		{
			LEDalert();						//LED闪烁报警
			Buzzeralert_start();	//蜂鸣器发出声音
		}
		else
    {
		  Buzzeralert_stop();
		}
	}
}

/************************END OF FILE************************/

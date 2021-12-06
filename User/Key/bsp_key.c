/**
  ******************************************************************************
  * @file    bsp_key.c
	* @author  Wu
  * @brief   矩阵键盘扫描，返回数值
  ******************************************************************************
  * @attention
  *
  * 硬件连接关系：														  	      *
  *						 	   B0~3 ---------  矩阵键盘行	 					*
  *						 	   B4~7 ---------  矩阵键盘列					  *
  *
  ******************************************************************************
  */ 
  
#include "bsp_key.h" 
#include "universe.h"

/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口（PB）的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

char pressedkey(void)
{
  char KeyVal= 'G';
	
	GPIO_Write(GPIOB,((GPIOB->ODR & 0xfff0) | 0x1));
	
	if((GPIOB->IDR & 0x00f0)==0x0000)
		return 'G';
	else
	{	
		Delay(5);   
		if((GPIOB->IDR & 0x00f0)==0x0000)  
			return 'G';
	}

	GPIO_Write(GPIOB,((GPIOB->ODR & 0xfff0) | 0x1));	
	switch(GPIOB->IDR & 0x00f0)		               
	{
		case 0x0010: KeyVal='F';	break;
		case 0x0020: KeyVal='B';	break;
		case 0x0040: KeyVal='7';	break;
		case 0x0080: KeyVal='3';	break;
	}
    
	GPIO_Write(GPIOB,((GPIOB->ODR & 0xfff0) | 0x2));	
	switch(GPIOB->IDR & 0x00f0)		                
	{
		case 0x0010: KeyVal='E';	break;
		case 0x0020: KeyVal='A';	break;
		case 0x0040: KeyVal='6';	break;
		case 0x0080: KeyVal='2';	break;
	}

	GPIO_Write(GPIOB,((GPIOB->ODR & 0xfff0) | 0x4));
	switch(GPIOB->IDR & 0x00f0)		               
	{
		case 0x0010: KeyVal='D';	break;
		case 0x0020: KeyVal='9';	break;
		case 0x0040: KeyVal='5';	break;
		case 0x0080: KeyVal='1';	break;
	}
  GPIO_Write(GPIOB,((GPIOB->ODR & 0xfff0) | 0x8));	
	switch(GPIOB->IDR & 0x00f0)		              
	{
		case 0x0010: KeyVal='C';	break;
		case 0x0020: KeyVal='8';	break;
		case 0x0040: KeyVal='4';	break;
		case 0x0080: KeyVal='0';	break;
	}	
	return KeyVal;		
}

/************************END OF FILE************************/

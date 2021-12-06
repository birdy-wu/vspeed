/**
  ******************************************************************************
  * @file    bsp_key.c
	* @author  Wu
  * @brief   �������ɨ�裬������ֵ
  ******************************************************************************
  * @attention
  *
  * Ӳ�����ӹ�ϵ��														  	      *
  *						 	   B0~3 ---------  ���������	 					*
  *						 	   B4~7 ---------  ���������					  *
  *
  ******************************************************************************
  */ 
  
#include "bsp_key.h" 
#include "universe.h"

/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڣ�PB����ʱ��*/
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

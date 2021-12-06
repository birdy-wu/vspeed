#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_4)

#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_5)

#define LED3(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_6);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_6)

#define LED4(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_7)
					
#define LED5(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_8);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_8)

#define LED6(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_9);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_9)
					
#define LED7(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_10);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_10)

#define LED8(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_11)

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			{p->BSRR=i;}			//设置为高电平		
#define digitalLo(p,i)			{p->BRR=i;}				//输出低电平
#define digitalToggle(p,i)		{p->ODR ^=i;}			//输出反转状态


/* 定义控制IO的宏 */
#define LED1_TOGGLE		digitalToggle(GPIOC,GPIO_Pin_4)
#define LED1_OFF		digitalHi(GPIOC,GPIO_Pin_4)
#define LED1_ON			digitalLo(GPIOC,GPIO_Pin_4)

#define LED2_TOGGLE		digitalToggle(GPIOC,GPIO_Pin_5)
#define LED2_OFF		digitalHi(GPIOC,GPIO_Pin_5)
#define LED2_ON			digitalLo(GPIOC,GPIO_Pin_5)

#define LED3_TOGGLE		digitalToggle(GPIOC,GPIO_Pin_6)
#define LED3_OFF		digitalHi(GPIOC,GPIO_Pin_6)
#define LED3_ON			digitalLo(GPIOC,GPIO_Pin_6)

#define LED4_TOGGLE		digitalToggle(GPIOC,GPIO_Pin_7)
#define LED4_OFF		digitalHi(GPIOC,GPIO_Pin_7)
#define LED4_ON			digitalLo(GPIOC,GPIO_Pin_7)

#define LED5_TOGGLE		digitalToggle(GPIOC,GPIO_Pin_8)
#define LED5_OFF		digitalHi(GPIOC,GPIO_Pin_8)
#define LED5_ON			digitalLo(GPIOC,GPIO_Pin_8)

#define LED6_TOGGLE		digitalToggle(GPIOC,GPIO_Pin_9)
#define LED6_OFF		digitalHi(GPIOC,GPIO_Pin_9)
#define LED6_ON			digitalLo(GPIOC,GPIO_Pin_9)

#define LED7_TOGGLE		digitalToggle(GPIOC,GPIO_Pin_10)
#define LED7_OFF		digitalHi(GPIOC,GPIO_Pin_10)
#define LED7_ON			digitalLo(GPIOC,GPIO_Pin_10)

#define LED8_TOGGLE		digitalToggle(GPIOC,GPIO_Pin_11)
#define LED8_OFF		digitalHi(GPIOC,GPIO_Pin_11)
#define LED8_ON			digitalLo(GPIOC,GPIO_Pin_11)

void LED_GPIO_Config(void);
void LEDchange(int status);
void LEDalert(void);

#endif /* __LED_H */

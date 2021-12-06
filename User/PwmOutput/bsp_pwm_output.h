#ifndef __PWM_OUTPUT_H
#define	__PWM_OUTPUT_H

#include "stm32f10x.h"

void TIM2_PWM_Init(void);
void changespeed(void);
void speedup(void);
void speeddown(void);
void stop(void);
#endif /* __PWM_OUTPUT_H */


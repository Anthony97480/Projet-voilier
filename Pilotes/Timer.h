#ifndef _piloteTimer_h
#define _piloteTimer_h

#include "stm32f10x.h"

void InitTimer(TIM_TypeDef *TIM, int ARR, int PSC);

char LireFlag(TIM_TypeDef *TIM);

void ResetFlag(TIM_TypeDef *TIM);

void StopTimer(TIM_TypeDef *TIm);

void MyTimer_ActivateIT(TIM_TypeDef *TIM, char Prio, void (* Ma_fonction) (void));

void MyTimer_PWM(TIM_TypeDef *Timer, char Channel);

#endif

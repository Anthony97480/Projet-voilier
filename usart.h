#ifndef __usart_h
#define __usart_h

#include "stm32f10x.h"


void initUSARTClock(void);

void initUSART(USART_TypeDef* USART);

void usartSetBaudRate(USART_TypeDef* USART, int deb);

void usartInterruptEnableReception(USART_TypeDef* USART);

void Putchar(USART_TypeDef* USART, char c);

#endif
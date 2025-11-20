#include "stm32f10x.h"

void initUART(USART_TypeDef * UART);

int LireUART(USART_TypeDef * UART);

void UART_ActivateIT(USART_TypeDef * UART, char Prio);

void ResetFlag_UART(USART_TypeDef * UART);

int ReturnUART(void);

void putchar(USART_TypeDef * UART, char mot);
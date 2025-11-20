#include "UART.h"
#include "GPIO.h"

int valeur_UART = 0;

void initUART(USART_TypeDef * UART){ //UART2
	UART->CR1 |= 0x01 << 2; //transmission
	UART->CR1 |= 0x01 << 3; //reception
	UART->CR1 |= 0x01 << 13; // activation de l'UART
	
	UART->BRR |= (36000000 / 9600); //

}

void UART_ActivateIT(USART_TypeDef * UART, char Prio){
	UART->CR1 |= (0x01 << 5); //autorisation de l'interuption
	NVIC->ISER[1] |= (0x01 << 6); //autorisation du num 38 pour l'UART2
	NVIC->IPR[9] |= (Prio << 16); //fait référence à IP18 pour set la priorité de l'ADC1_2
}

void ResetFlag_UART(USART_TypeDef * UART){
	UART->SR &= 0x00 << 5; //reset du RXNE
}

void USART2_IRQHandler(void){
	ResetFlag_UART(USART2); //flag RXNE
	valeur_UART = LireUART(USART2);
}

int LireUART(USART_TypeDef * UART){
	return UART->DR;
}

int ReturnUART(void){
	return valeur_UART;
}

void putchar(USART_TypeDef * UART, char mot){
	SetBroche(GPIOA,2);
	UART->DR = mot;
}
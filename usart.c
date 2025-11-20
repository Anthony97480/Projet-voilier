#include "usart.h"



void initUSARTClock(void){
	
	RCC->APB1ENR  |= (1<<17); // acive la clock pour l'usart
}


void initUSART(USART_TypeDef* USART){
	
	//Initialiser l'usart bit UE à 1
	USART->CR1 |= 1 << 13;
	
	// TE à 1 
	USART->CR1 |= 1 << 3;
	
	//RE à 1
	USART->CR1 |= 1 << 2;
	
	
	
}


void usartSetBaudRate(USART_TypeDef* USART, int deb){
	
	//Baud rate permet de configurer l'émission de bit, mais il faut connaître la fréquence de l'horloge de bit. on veut un débit de 9600 bit par seconde donc on divise par le débit souhaité
	USART->BRR = 36000000/deb ;
	
}


void usartInterruptEnableReception(USART_TypeDef* USART){
	
	//RXNEIE à 1 pour utiliser les interruptions
	USART->CR1 |= 1 << 5;
	NVIC -> ISER[1] |= 1<<6;			// attribuer le droit au niveau du processeur, voir doc dans mannuel cortex M3
	NVIC -> IPR[38] = 3 << 4; // ordonner , mannuel page 125 cortexM3 3 = la priorité, dans la doc du coeur se sont des registre IP et le 28 eme été associé par stmn au tim2, les 4 1er bits ne sert à rien, et les 4 dernier codent la priorité IPR fait enfaite référence à IP
	
	
	
}


void Putchar(USART_TypeDef* USART, char c){
	
	USART->DR = c;
	// TXE = 1 ?
	while ((USART->SR & (1 << 7)) == (1<<7)){
	}
	
	
}
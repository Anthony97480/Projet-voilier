#include "stm32f10x.h"
#include "Pilote_GPIO.h"
#include "timer.h"
#include "adc.h"
#include "usart.h"

#define ARR_VALUE 35999  // on veut 50 Hz pour le timer 3
#define PSC_VAL 39			// avec ce psc on a les 50 Hz
#define CYCLE_RATE_PWM 10

/////////////////////////////////
//  fonction 'pas top top'     //
//  d'attente d'environ 250 ms //
/////////////////////////////////

char c;

void clignoterLED(void){

	ToggleBroche(GPIOA,5);
}

void Putchar1(USART_TypeDef* USART, char c){
	
	USART->DR = c;
	// TXE = 1 ?
	while ((USART->SR & (1 << 7)) == (1<<7)){
	}
	
	
}


void TimerPutChar(void){
	Putchar1(USART2, 'a');
}



void Attente (void)
{
	for (int i = 0 ; i < 1000000 ; i++){}
}
/////////////////////////////////

// s'execute lorsque RXNE vaut 1, pour tester, écrire dans la fenêtre de l'usart puis voir la valeur dans c
void  USART2_IRQHandler (void)
{
	c = USART2->DR ;
}

int main ( void )
{
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN ; //
	RCC->APB1ENR  |= (1<<0); // Active le timer 2 mais ne le démarre pas ! page 141 manuel 
	initUSARTClock();
	
	// pour avoir 500ms
	InitTIMER(35999, 999, TIM2);
	InitTIMER(ARR_VALUE, PSC_VAL, TIM3);
	
	initUSART(USART2);
	usartSetBaudRate(USART2, 9600);
	
	usartInterruptEnableReception(USART2);
	
	// Activation des pins
	
	// USART2 Tx configuré sur la broche PA2
	InitGPIO(GPIOA, 2, GPIO_AF_PP_2MHZ);
	
	// USART Rx configué sur la broche PA3
	InitGPIO(GPIOA, 3, GPIO_INPUT_FLOATING);
	
	// Dans CR1, Le bit M n'a pas besoin d'être modifié ca par défaut les données transmise sont déjà de 8 bits
	
	
	// setup interruption puis lancement
	InitTimerIT(TIM2, 3, TimerPutChar);
	StartTimer(TIM2);
	
	while(1){
	}
}




// Code PWM

/*

void clignoterLED(void){

	ToggleBroche(GPIOA,5);
}

int main ( void )
{

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPAEN ; //
	RCC->APB1ENR |= (1<<0); // Active le timer 2 mais ne le démarre pas ! page 141 manuel
	RCC->APB1ENR |= (1<<1); // Activer timer 3 sans le démarrer
	
	InitTIMER(35999, 999, TIM2);
	InitTIMER(ARR_VALUE, PSC_VAL, TIM3);
	
	ConfigPWM(TIM3,CYCLE_RATE_PWM,CHANNEL_2); // il ne reste plus qu'à selectionner la broche à initialiser, mais je peux faire en sorte que cela se fasse dans la fonction
	
	//mise en place interruption
	InitTimerIT(TIM2, 3, clignoterLED);

	// Init GPIO
	InitGPIO(GPIOA, 7, GPIO_AF_PP_2MHZ);
	InitGPIO(GPIOA, 5, GPIO_OUTPUT_PP_2MHZ);
	
	// démarre le timer : Page 403 pour piger on le lance à la fin parce que on risque d'avoir un bug après au niveau des interruptions.
	StartTimer(TIM2); 
	StartTimer(TIM3);
	
		while (1){
	}
}

*/














/* CODE PILOTAGE LES EN OPEN DRAIN ET BOUTON POUSSOIR EN FLOATING INPUT dans main

	while (1)
	{
		if ( (GPIOC->IDR & 1<<3) == (1<<3)){
			GPIOC->ODR |= 0x1 << 10;// ou GPIOC->BSRR = 1<<10 ;
			
		}
		else{
			GPIOC->BRR = (1<<10);
		}
	}

*/




/* CODE ALLUMAGE LD2 SANS Pilote_GPIO.c dans main

	while (1)
	// pour allumer ld2 apparement faut config le pin pa5 en mode out put push pull
	{
		if ((GPIOC->IDR & 1<<13) == (1<<13)){
			GPIOA->BRR = 1<<5 ; // reset odr to 0
	
		}
		
			else{
				
			GPIOA->BSRR = (1<<5); // set odr to 1
		}
	}


*/


/* // CODE ALLUMAGE LED AVEC FONCTION DE PILOTE_GPIO.H dans main

		while (1)
	// pour allumer ld2 apparement faut config le pin pa5 en mode out put push pull
	{
		
		if (LireBroche(GPIOC,13)){
			ResetBroche(GPIOA,5);
	
		}
	
		else{
			SetBroche(GPIOA, 5);
		}
	}
	
	
	

*/



/* CODE ALLUMAGE LED INIT MARCHE

	int main ( void )
{
	RCC->APB2ENR |= (1<<4) | RCC_APB2ENR_IOPAEN ;
	
	InitGPIO(GPIOA, 5, GPIO_OUTPUT_PP_2MHZ);
	InitGPIO(GPIOC, 13, GPIO_INPUT_FLOATING);
	
	// CODE ALLUMAGE LED AVEC FONCTION DE PILOTE_GPIO.h
		while (1)
	// pour allumer ld2 apparement faut config le pin pa5 en mode out put push pull
	{
		
		if (LireBroche(GPIOC,13)){
			ResetBroche(GPIOA,5);
	
		}
	
		else{
			SetBroche(GPIOA, 5);
		}
	}


}

*/

/*
void TestGPIO(void){

	
	// CODE ALLUMAGE LED AVEC FONCTION DE PILOTE_GPIO.h
	
	// pour allumer ld2 apparement faut config le pin pa5 en mode out put push pull
	
		
		if(TIM2->SR & 0x1<<0){ // le timer a claqué ?
		
		
			ToggleBroche(GPIOA,5); // toggle led
			
			TIM2->SR &= ~(0x1<<0); // bit UIF reset pour le rabaisser direct (ne modfie pas la valeur du timer)
			
		}
	
}
*/
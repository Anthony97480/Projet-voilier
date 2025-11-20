#include "stm32f10x.h"
#include "GPIO.h"
#include "Timer.h"
#include "adc.h"
#include "UART.h"



void clignote (void){
	ToggleBroche(GPIOA, 6);
}

void convert (void){
	StartConv(ADC1);
}

void send(void) {
	putchar(USART2, 'a');
	ResetBroche(GPIOA,2);
}

int main ( void )
{
	
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) | (0x01 << 11); //activer les GPIO (A, B et C) et Timer1
	RCC->APB2ENR |= (0x01 << 9) | (0x01 << 10); //activer les ADC1 et ADC2
	RCC->APB1ENR |= (0x01 << 0) | (0x01 << 1) | (0x01 << 2); //activer les timer 2, 3 et 4 
	RCC->CFGR |= (0x02 << 14); //diviser la fréquence des ADC de 72M à 12M (division par 6)
	RCC->APB1ENR |= (0x01 << 17); //activation de l'USART2
	
	InitGPIO(GPIOA, 0, INPUTANALOG);
	InitGPIO(GPIOA, 6, OUTPUTALTERNATEPUSHPULL);
	InitGPIO(GPIOA, 8, OUTPUTPUSHPULL);
	
	InitGPIO(GPIOA, 2, OUTPUTALTERNATEPUSHPULL);
	InitGPIO(GPIOA, 3, INPUTFLOATING);
	
	//MyTimer_PWM(TIM3, 1);
	//InitTimer(TIM3, 10000, 143); //période 0.02s

	//ADC_ActivateIT(ADC1, 3);
	//initADC(ADC1, 0);
	//MyTimer_ActivateIT(TIM2, 0, convert);
	//InitTimer(TIM2, 9999, 3599); //période 0.5s
	
	UART_ActivateIT(USART2, 3);
	initUART(USART2);
	MyTimer_ActivateIT(TIM2, 0, send);
	InitTimer(TIM2, 9999, 3599); //période 0.5s
	
	while (1)
	{
		SetBroche(GPIOA,3);
		int valeur = ReturnUART();
		ResetBroche(GPIOA,3);
		//int valeur = ReturnConv();
	}
		
		/*if (LireBroche(GPIOA,0)){
			SetBroche(GPIOA, 8);
		}
		else{
			//ResetBroche(GPIOA,8);
		}*/
		
}

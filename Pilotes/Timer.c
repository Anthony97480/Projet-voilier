#include "Timer.h"

void (* PFoncTIM1) (void);
void (* PFoncTIM2) (void);
void (* PFoncTIM3) (void);
void (* PFoncTIM4) (void);

void InitTimer(TIM_TypeDef *TIM, int ARR, int PSC){
	
	TIM ->ARR = ARR ; 
	TIM -> PSC = PSC ; 
	TIM ->CR1 |= (0x01 << 0); // enable le compteur
}


char LireFlag(TIM_TypeDef *TIM){
	if ((TIM->SR & ((0x01) << 0)) == ((0x01 << 0))){
		
		return 1 ;
	}
	else return 0;

}

void ResetFlag(TIM_TypeDef *TIM){
	TIM->SR &= ~(0x01 << 0);
}


void StopTimer(TIM_TypeDef *TIM){
	TIM->CR1 &= ~(0x01 << 0);
}



void TIM1_UP_IRQHandler (void){
	if (PFoncTIM1 !=0){
		ResetFlag(TIM1);
		(*PFoncTIM1)();
	}
}

void TIM2_IRQHandler (void){
	if (PFoncTIM2 !=0){
		ResetFlag(TIM2);
		(*PFoncTIM2)();
	}
}

void TIM3_IRQHandler (void){
	if (PFoncTIM3 !=0){
		ResetFlag(TIM3);
		(*PFoncTIM3)();
	}
}

void TIM4_IRQHandler (void){
	if (PFoncTIM4 !=0){
		ResetFlag(TIM4);
		(*PFoncTIM4)();
	}
}


void MyTimer_ActivateIT(TIM_TypeDef *TIM, char Prio, void (* Ma_fonction) (void)){
	if (TIM == TIM1){ //Update interuption 
		PFoncTIM1 = Ma_fonction;
		TIM->DIER |= (0x01 << 0);//UIE à 1
		NVIC->ISER[0] |= (0x01 << 25); //autorisation du num 28
		NVIC->IPR[25] |= (Prio << 0); //fait référence à IP
	}
	
	if (TIM == TIM2){
		PFoncTIM2 = Ma_fonction;
		TIM->DIER |= (0x01 << 0);//UIE à 1
		NVIC->ISER[0] |= (0x01 << 28); //autorisation du num 28
		NVIC->IPR[28] |= (Prio << 0); //fait référence à IP
	}
	
	if (TIM == TIM3){
		PFoncTIM3 = Ma_fonction;
		TIM->DIER |= (0x01 << 0);//UIE à 1
		NVIC->ISER[0] |= (0x01 << 29); //autorisation du num 28
		NVIC->IPR[29] |= (Prio << 0); //fait référence à IP
	}
	
	if (TIM == TIM4){
		PFoncTIM4 = Ma_fonction;
		TIM->DIER |= (0x01 << 0);//UIE à 1
		NVIC->ISER[0] |= (0x01 << 30); //autorisation du num 28
		NVIC->IPR[30] |= (Prio << 0); //fait référence à IP
	}
}

void MyTimer_PWM(TIM_TypeDef *Timer, char Channel){
	
	if(Channel == 1){
	Timer->CCMR1 |= (0x06) << 4; //mettre le mode PWM dans OC1M situer sur les bit 4 à 6
	Timer->CCER |= (0x01) << 0;
	Timer->CCR1 |= (0x01F4) << 0; //5% de ARR
	}
	
	if(Channel == 2){
	Timer->CCMR1 |= (0x06) << 4; //mettre le mode PWM dans OC1M situer sur les bit 4 à 6
	Timer->CCER |= (0x01) << 0;
	Timer->CCR2 |= (0x01F4) << 0; //5% de ARR
	}
	
	if(Channel == 3){
	Timer->CCMR1 |= (0x06) << 4; //mettre le mode PWM dans OC1M situer sur les bit 4 à 6
	Timer->CCER |= (0x01) << 0;
	Timer->CCR3 |= (0x01F4) << 0; //5% de ARR
	}
	
	if(Channel == 4){	
	Timer->CCMR1 |= (0x06) << 4; //mettre le mode PWM dans OC1M situer sur les bit 4 à 6
	Timer->CCER |= (0x01) << 0;
	Timer->CCR4 |= (0x01F4) << 0; //5% de ARR
	}

	
	
}












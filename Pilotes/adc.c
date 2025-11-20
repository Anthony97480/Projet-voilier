#include "adc.h"

int valeur_ADC = 0;

void initADC(ADC_TypeDef * ADC, char Channel){
	ADC->CR2 |= (0x01) << 1*0; //réveiller le périf
	ADC->CR2 |= (0x01) << 1*20; //dire que c'est un trigger externe qui fait la conv
	ADC->CR2 |= (0x07) << 1*17; //dire que c'est le software qui va être le trigger
	
	ADC->SQR1 |= (0x00) << 1*20; //demander de réaliser 1 seul conv
	ADC->SQR3 |= Channel << 1*0; //numéro de voix utiliser
}

void StartConv(ADC_TypeDef * ADC){
	ADC->CR2 |= (0x01) << 1*22; //lancé la conv sur le software
	ADC->CR2 |= (0x01) << 1*0; //activer la conv
}

int LireConv(ADC_TypeDef * ADC){
	return ADC->DR;
}

void ADC_ActivateIT(ADC_TypeDef * ADC, char Prio){
	ADC->CR1 |= (0x01 << 5); //autorisation de l'interuption
	NVIC->ISER[0] |= (0x01 << 18); //autorisation du num 18 pour l'ADC1_2
	NVIC->IPR[18] |= (Prio << 0); //fait référence à IP18 pour set la priorité de l'ADC1_2
}

void ResetFlag_ADC(ADC_TypeDef *ADC){
	ADC->SR &= 0x00 << 1;
}

void ADC1_2_IRQHandler (void){
	//adc1
	if((ADC1->CR1 & (0x01 << 5)) == (0x01 << 5)){
		ResetFlag_ADC(ADC1);
		valeur_ADC = LireConv(ADC1);;
	}
	
	//adc2
	if((ADC2->CR1 & (0x01 << 5)) == (0x01 << 5)){
		ResetFlag_ADC(ADC2);
		valeur_ADC = LireConv(ADC2);
	}
}

int ReturnConv(){
	return valeur_ADC;
}
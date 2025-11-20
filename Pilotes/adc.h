#include "stm32f10x.h"

void initADC(ADC_TypeDef * ADC, char Channel);

void StartConv(ADC_TypeDef * ADC);

int LireConv(ADC_TypeDef * ADC);

void ADC_ActivateIT(ADC_TypeDef * ADC, char Prio);

void ResetFlag_ADC(ADC_TypeDef *ADC);

int ReturnConv(void);
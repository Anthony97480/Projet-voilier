#ifndef _piloteGPIO_h
#define _piloteGPIO_h

#include "stm32f10x.h"

#define OUTPUTPUSHPULL 0x02
#define OUTPUTALTERNATEPUSHPULL 0x0A
#define INPUTFLOATING 0x04
#define INPUTANALOG 0x00

void InitGPIO(GPIO_TypeDef *PORT, char BROCHE, char CONFIG);

char LireBroche(GPIO_TypeDef *PORT, char BROCHE );

void SetBroche(GPIO_TypeDef *PORT, char BROCHE);

void ResetBroche(GPIO_TypeDef *PORT, char BROCHE);

void ToggleBroche(GPIO_TypeDef *PORT, char BROCHE);







#endif

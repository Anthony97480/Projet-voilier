#include "GPIO.h"

void InitGPIO(GPIO_TypeDef *PORT, char BROCHE, char CONFIG){
	
	if(BROCHE < 8){
		PORT->CRL &= ~((0x0F)<<(4*BROCHE));
		PORT->CRL |= (CONFIG) << (4*BROCHE);
	} else {
		PORT->CRH &= ~((0x0F)<<(4*(BROCHE-8)));
		PORT->CRH |= (CONFIG) << (4*(BROCHE - 8));
	}
}


char LireBroche(GPIO_TypeDef *PORT, char BROCHE ){

	if ((PORT->IDR & ((0x01)<<BROCHE)) == ((0x01)<<BROCHE)){
		
		return 1 ;
	}
	else return 0;
}

void SetBroche(GPIO_TypeDef *PORT, char BROCHE){

	PORT->ODR |= ((0x01)<< BROCHE);
}
	


void ResetBroche(GPIO_TypeDef *PORT, char BROCHE){

	PORT->ODR &= ~(0x01 << BROCHE);
}

void ToggleBroche(GPIO_TypeDef *PORT, char BROCHE){

	PORT->ODR ^= (0x01 << BROCHE);
	
}
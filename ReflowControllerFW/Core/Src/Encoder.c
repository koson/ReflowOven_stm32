#include "Encoder.h"


void Encoder_Init(Encoder *enc, GPIO_TypeDef *GPIOx, uint16_t GPIO_PinA, uint16_t GPIO_PinB){

	enc->pinA = 0;
	enc->pinB = 0;



	/*
	enc->pinA = GPIO_PinA;
	enc->pinB = GPIO_PinB;
	enc->aLastState = HAL_GPIO_ReadPin(GPIOx, enc->pinA);
	*/
}

int Encoder_Read(Encoder *enc, GPIO_TypeDef *GPIOx){

	enc->aState << 1;
	enc->bState << 1;

	enc->aState = enc->aState | BITMASK;
	enc->bState = enc->aState | BITMASK;

	enc->aState = enc->aState | HAL_GPIO_ReadPin(GPIOx, enc->pinA);
	enc->bState = enc->bState | HAL_GPIO_ReadPin(GPIOx, enc->pinB);

	//turn left
	if (enc->aState == 0b00001001 && enc->bState == 0b00000011){
		return -1;
	}
	//turn right
	if (enc->aState == 0b00000011 && enc->bState == 0b00001001){
		return 1;
	}
	return 0;

	/*
	enc->aState = HAL_GPIO_ReadPin(GPIOx, enc->pinA);
	if (enc->aState != enc->aLastState){
		if (HAL_GPIO_ReadPin(GPIOx, enc->pinB) != enc->aState){
			enc->aLastState = enc->aState;
			return 1;
		}
		else {
			enc->aLastState = enc->aState;
			return -1;
		}
	}
	enc->aLastState = enc->aState;
	return 0;
	*/

}

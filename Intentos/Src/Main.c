/*
 * 002a_IntroGPIOxMain.c
 *
 *  Created on: Mar 10, 2023
 *      Author:Maria Jose Uribe Henao
 *
 * Con este programa se desea desarrolar la Tarea 2 del curso de Taller V.
 *
 */

#include <stdint.h>

#include "stm32f411xx_hal.h"
#include "GPIOxDriver.h"

/* Funcion principal del programa. Es aca donde se ejecuta todo */
int main(void){

	GPIO_Handler_t handlerPinC9 = {0};

	handlerPinC9.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC9.GPIO_PinConfig.GPIO_PinNumber = PIN_9;                       // Escribimos el Numero del Pin
	handlerPinC9.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC9.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC9.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC9.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC9.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	GPIO_Handler_t handlerPinC8 = {1};

	handlerPinC8.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC8.GPIO_PinConfig.GPIO_PinNumber = PIN_8;                       // Escribimos el Numero del Pin
	handlerPinC8.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC8.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC8.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC8.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC8.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna


	// Este es el ciclo principal, donde se ejecuta todo el programa
	while(1){
		GPIOxTogglePin(&handlerPinC9);
		uint8_t a =GPIO_ReadPin(&handlerPinC9);
		GPIOxTogglePin(&handlerPinC9);
		a = GPIO_ReadPin(&handlerPinC9);
	    NOP();

	}

}








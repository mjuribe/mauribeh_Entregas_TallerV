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
	/*
	 * Definimos el handler para el PIN que deseamos configurar
	 */
	GPIO_Handler_t handlerUserLedPin = {1};

	// Deseamos trabajar con el puerto GPIOA
	handlerUserLedPin.pGPIOx = GPIOA;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinNumber = PIN_5;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;

	// Cargamos la configuracion del PIN especifico
	GPIO_Config(&handlerUserLedPin);

	// Hacemos que el PIN_A5 quede encendido
	GPIO_WritePin(&handlerUserLedPin, SET);

	// Leemos el estado del PIN
	uint32_t a = GPIO_ReadPin(&handlerUserLedPin);

	// Este es el ciclo principal, donde se ejecuta todo el programa
	while(1){
		NOP();
	}
}

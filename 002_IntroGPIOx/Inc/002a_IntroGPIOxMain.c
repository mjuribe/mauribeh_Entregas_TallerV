/*
 * 002a_IntroGPIOxMain.c
 *
 *  Created on: Mar 10, 2023
 *      Author:Maria Jose Uribe Henao
 *
 * Con este programa se desea mostrar el uso basico de los registros que controlan
 * al Micro (SFR) y la forma adecuada para utilizar los operadores &, |, ~ y =, para
 * cambiar la configuracion de algun registro.
 * Tambein es importante para entender la utilidad de los numeros BIN y HEX.
 *
 * Es necesario tener a la mano tanto el manual de referencia del micro como la hoja de
 * datos del micro (documentos diferentes y complementarios).
 *
 * HAL -> Hardware Abstraction Layer.
 *
 * Este programa introduce el periferico mas simple que tiene el micro, que es el
 * encargado de manejar los pines de cada puerto del micro.
 *
 * Cada PINx de cada puerto GPIO puede desarrollar funciones basicas de tipo entrada
 * y salida de datos digitales (o sea 1's y 0's), ademas se les puede asignar funciones
 * especiales que generalmente estan ligadas a otro periferico adicional (proximamente)
 *
 * De igual forma, varias caracteristicas pueden ser configuradas para cada PINx
 * especifico como son:
 * - la velocidad a la que puede responder
 * - Tipo de entrada (pull up, pull down, open drain (flotante))
 * - Tipo de salida (push-pull, open drain,,,)
 * - Entrada analoga
 *
 * Debemos definir entonces todos los registros que manejan el periferico GIOx y luego
 * crear algunas funciones para utilizar adecuadamente el equipo.
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
	GPIO_Handler_t handlerUserLedPin = {0};

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

	// Este es el ciclo principal, donde se ejecuta todo el programa
	while(1){
		NOP();
	}
}

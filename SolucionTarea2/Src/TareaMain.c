/*
 * SolucionTarea2.c
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

/* Funcion principal del programa. Es aca donde se ejecutan las tres actividades correspondientes */
int main(void){
	/*
	 *  --------------- ACTIVIDAD 1 ---------------
	 *
	 * a. La funcion GPIO_ReadPin() que fue desarrollada en el video del Driver para el puerto GPIOx tenia un
	 * error que no nos permitia obtener el valor real, ese error era que en el momento de leer el estado
	 * del PinX corria el registro IDR (Input Data Register) tantas veces a la derecha como el numero del
	 * Pin y guardaba ese valor en PinValue sin limpiar los demas bits del IDR, por lo que no se tomaban en
	 * cuenta y por esto no nos permitia obtener el valor real del PinX que estuvieramos leyendo.
	 * b.  La solucion a este error, era limpiar las posiciones a la izquierda del PinX que estuviera leyendo
	 * por medio de una mascara y almacenar ese estado en el PinValue.
	 * La funcion corregida se encuentra en GPIOxDriver.c
	 *
	 * c. A continuacion se presentara un ejemplo de la lectura del estado del LED2 en el PinA5 cuando esta
	 * encendido
	 *
	//Definimos el handler para el PIN que deseamos configurar
	GPIO_Handler_t handlerUserLedPin = {0};

	handlerUserLedPin.pGPIOx = GPIOA;                                              // Deseamos trabajar con el puerto GPIOA
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinNumber = PIN_5;                       // Escribimos el Numero del Pin
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerUserLedPin.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna
	// Cargamos la configuracion del PIN especifico
	GPIO_Config(&handlerUserLedPin);

	// Hacemos que el PIN_A5 quede encendido
	GPIO_WritePin(&handlerUserLedPin, SET);

	// Leemos el estado del PIN
	uint32_t Estado = GPIO_ReadPin(&handlerUserLedPin);
	 */



	/*  --------------- ACTIVIDAD 2 ---------------
	 *
	 * Se desea crear una funcion denomindad GPIOxTooglePin que cambie el estado del pin.
	 * Sabemos que la funcion XOR permite que dos estados iguales se anulen (1^1=0 y 0^0=0) y dos estados
	 * diferentes se complementen (1^0=0 y 0^1=0).
	 * Por lo que si deseo el cambio de estado necesito una mascara con 1 en la posicion del PinX que
	 * deseo suichear operando un xor para el estado especifico del PinX.
	 * Como es una funcion que se desea volver a utilizar se encuentra en el archivo GPIOxDriver.c
	 *
	 * A continuacion se presentara el funcionamiento de la funcion Toggle que cambia el estado del Pin.
	 * Como el PIN_A5 lo prendimos, la funcion Toggle lo apagara.
	 *
     // Cambio del estado del Pin
	 GPIOxTooglePin(&handlerUserLedPin);
	 */

	/*
	 * --------------- ACTIVIDAD 3 ---------------
	 *
	 * Se desea realizar un contador binario de segundos.
	 *
	 * A continuacion se presenta la configuracion de los pines que se utilizaran:
	 * PC9 bit-6, PC6 bit-5, PB8 bit-4, PA6 bit-3, PC7 bit-2, PC8 bit-1, PA7 bit-0
	 */

	//Definimos el handler para el PIN que deseamos configurar
	GPIO_Handler_t handlerPinC9 = {0}; //bit-6

	handlerPinC9.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC9.GPIO_PinConfig.GPIO_PinNumber = PIN_9;                       // Escribimos el Numero del Pin
	handlerPinC9.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC9.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC9.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC9.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC9.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna
    // Cargamos la configuracion del PinC9
	GPIO_Config(&handlerPinC9);

	GPIO_Handler_t handlerPinC6 = {0};  //bit-5

	handlerPinC6.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC6.GPIO_PinConfig.GPIO_PinNumber = PIN_6;                       // Escribimos el Numero del Pin
	handlerPinC6.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC6.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC6.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC6.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna
	// Cargamos la configuracion del PinC6
	GPIO_Config(&handlerPinC6);

	GPIO_Handler_t handlerPinB8 = {0};  //bit-4

	handlerPinB8.pGPIOx = GPIOB;                                              // Deseamos trabajar con el puerto GPIOB
	handlerPinB8.GPIO_PinConfig.GPIO_PinNumber = PIN_8;                       // Escribimos el Numero del Pin
	handlerPinB8.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinB8.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinB8.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinB8.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinB8.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna
	// Cargamos la configuracion del PinB8
	GPIO_Config(&handlerPinB8);

	GPIO_Handler_t handlerPinA6 = {0}; //bit-3

	handlerPinA6.pGPIOx = GPIOA;                                              // Deseamos trabajar con el puerto GPIOA
	handlerPinA6.GPIO_PinConfig.GPIO_PinNumber = PIN_6;                       // Escribimos el Numero del Pin
	handlerPinA6.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinA6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinA6.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinA6.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinA6.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna
	// Cargamos la configuracion del PinA6
	GPIO_Config(&handlerPinA6);

	GPIO_Handler_t handlerPinC7 = {0}; //bit-2

	handlerPinC7.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC7.GPIO_PinConfig.GPIO_PinNumber = PIN_7;                       // Escribimos el Numero del Pin
	handlerPinC7.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC7.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC7.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC7.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC7.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna
	// Cargamos la configuracion del PinC7
	GPIO_Config(&handlerPinC7);

	GPIO_Handler_t handlerPinC8 = {0}; //bit-1

	handlerPinC8.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC8.GPIO_PinConfig.GPIO_PinNumber = PIN_8;                       // Escribimos el Numero del Pin
	handlerPinC8.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC8.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC8.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC8.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC8.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna
	// Cargamos la configuracion del PinC8
	GPIO_Config(&handlerPinC8);

	GPIO_Handler_t handlerPinA7 = {0}; // bit-0

	handlerPinA7.pGPIOx = GPIOA;                                              // Deseamos trabajar con el puerto GPIOA
	handlerPinA7.GPIO_PinConfig.GPIO_PinNumber = PIN_7;                       // Escribimos el Numero del Pin
	handlerPinA7.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinA7.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinA7.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinA7.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinA7.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna
	// Cargamos la configuracion del PinA7
	GPIO_Config(&handlerPinA7);

	// Configuracion del Boton de Usuario que esta en el PINC13
	GPIO_Handler_t handlerPinC13 = {0};

	handlerPinC13.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC13.GPIO_PinConfig.GPIO_PinNumber = PIN_13;                      // Escribimos el Numero del Pin
	handlerPinC13.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_IN;                // Modo del pin de entrada
	handlerPinC13.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica
	handlerPinC13.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC13.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna
	// Cargamos la configuracion del PinC13 (Boton de Usuario)
	GPIO_Config(&handlerPinC13);

    // Definicion de la variable contador
	uint32_t counter=1;

	// Ciclo Principal
	while(1){
		// Delay de aproximadamente un segundo
		for (uint32_t i = 0; i < 1380000; i++);
		/* Switch que permite llevar el contador principal a 1 si llega a 61 en el ciclo ascendente o que
		 * lleva el contador a 60 si llega a 0 en el ciclo descendente.
		 */
		switch(counter){
		case(61):
			counter = 1;   // Conteo ascendente
			break;
		case(0):
			counter = 60;  // Conteo descendente
			break;
		default:
			break;
		}
		// Se enciende el led correspondiente segun la posicion
		/*
		 * Se hace un desplazamiento a la izquierda segun el bit asignado y un "and" (&) con el numero del contador,
		 * para poder definir si ese bit hace parte del numero en el que va la cuenta y cambiar su estado.
		 */
		GPIO_WritePin(&handlerPinA7, (0b1 << 0) & counter);        // bit-0
		GPIO_WritePin(&handlerPinC8, ((0b1 << 1) & counter) >> 1); // bit-1
		GPIO_WritePin(&handlerPinC7, ((0b1 << 2) & counter) >> 2); // bit-2
		GPIO_WritePin(&handlerPinA6, ((0b1 << 3) & counter) >> 3); // bit-3
		GPIO_WritePin(&handlerPinB8, ((0b1 << 4) & counter) >> 4); // bit-4
		GPIO_WritePin(&handlerPinC6, ((0b1 << 5) & counter) >> 5); // bit-5
		GPIO_WritePin(&handlerPinC9, ((0b1 << 6) & counter) >> 6); // bit-6

		/*
		 * Verificar si el Boton de Usuario esta o no presionado
		 * Si no esta presionado es un valor de 1, si lo esta es un valor de 0.
		 */
		if (GPIO_ReadPin(&handlerPinC13)){
			counter++; // Ciclo ascendente
			} else {
			counter--; // Ciclo descendente
			}


	}

}








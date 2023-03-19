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

	/*
	 *  ---- ACTIVIDAD 1 ----
	 * El error que la funcion GPIO_ReadPin() tenia era que en el momento de leer el estado no limpiaba
	 * las demas bits del input data register por esto no nos permitia obtener el valor real del PinX
	 * que estuvieramos leyendo.
	 */

	// Leemos el estado del PIN
	uint32_t Estado = GPIO_ReadPin(&handlerUserLedPin);

	/*  ---- ACTIVIDAD 2 ----
	 * Funcionamiento de la funcion Toggle que cambia el estado del Pin.
	 * Como el PIN_A5 lo prendimos, la funcion Toggle lo apagara.
	 */

    // Cambio del estado del Pin
	GPIOxTooglePin(&handlerUserLedPin);
	GPIOxTooglePin(&handlerUserLedPin);

	GPIO_Handler_t handlerPinB4 = {0};

	handlerPinB4.pGPIOx = GPIOB;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinB4.GPIO_PinConfig.GPIO_PinNumber = PIN_4;                       // Escribimos el Numero del Pin
	handlerPinB4.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinB4.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinB4.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinB4.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinB4.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	GPIO_WritePin(&handlerPinB4, SET);


	/*
	 * ---- ACTIVIDAD 3 ----
	 * Configuracion de los pines que se utilizaran PC9 bit-6, PC6 bit-5, PB8 bit-4, PA6 bit-3, PC7 bit-2,
	 * PC8 bit-1, PA7 bit-0
	 */
	GPIO_Handler_t handlerPinC9 = {0};

	handlerPinC9.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC9.GPIO_PinConfig.GPIO_PinNumber = PIN_9;                       // Escribimos el Numero del Pin
	handlerPinC9.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC9.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC9.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC9.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC9.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	GPIO_Handler_t handlerPinC6 = {0};

	handlerPinC6.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC6.GPIO_PinConfig.GPIO_PinNumber = PIN_6;                       // Escribimos el Numero del Pin
	handlerPinC6.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC6.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC6.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC6.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	GPIO_Handler_t handlerPinB8 = {0};

	handlerPinB8.pGPIOx = GPIOB;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinB8.GPIO_PinConfig.GPIO_PinNumber = PIN_8;                       // Escribimos el Numero del Pin
	handlerPinB8.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinB8.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinB8.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinB8.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinB8.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	GPIO_Handler_t handlerPinA6 = {0};

	handlerPinA6.pGPIOx = GPIOA;                                              // Deseamos trabajar con el puerto GPIOA
	handlerPinA6.GPIO_PinConfig.GPIO_PinNumber = PIN_6;                       // Escribimos el Numero del Pin
	handlerPinA6.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinA6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinA6.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinA6.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinA6.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	GPIO_Handler_t handlerPinC7 = {0};

	handlerPinC7.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC7.GPIO_PinConfig.GPIO_PinNumber = PIN_7;                       // Escribimos el Numero del Pin
	handlerPinC7.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC7.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC7.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC7.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC7.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	GPIO_Handler_t handlerPinC8 = {0};

	handlerPinC8.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC8.GPIO_PinConfig.GPIO_PinNumber = PIN_8;                       // Escribimos el Numero del Pin
	handlerPinC8.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC8.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC8.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC8.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC8.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	GPIO_Handler_t handlerPinA7 = {0};

	handlerPinA7.pGPIOx = GPIOA;                                              // Deseamos trabajar con el puerto GPIOA
	handlerPinA7.GPIO_PinConfig.GPIO_PinNumber = PIN_7;                       // Escribimos el Numero del Pin
	handlerPinA7.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinA7.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinA7.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinA7.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinA7.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

    // Configuracion del boton de usuario
	RCC ->AHB1ENR &= ~(1<<0); // Limpiando la posicion 0 del registro
	RCC ->AHB1ENR |= (1<<0);

	GPIO_Handler_t handlerPinC13 = {0};

	handlerPinC13.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC13.GPIO_PinConfig.GPIO_PinNumber = PIN_13;                       // Escribimos el Numero del Pin
	handlerPinC13.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC13.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC13.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

    /*
	uint32_t GPIO_ReadPin(GPIO_Handler_t *pPinHandler){
		uint32_t pinValue = 0;
		pinValue = (pPinHandler ->pGPIOx->IDR >> pPinHandler ->GPIO_PinConfig.GPIO_PinNumber);
		pinValue &= 1;
		return pinValue;
	}*/
	(GPIO_ReadPin(&handlerPinA7) >> 0b0 );
	(GPIO_ReadPin(&handlerPinC8) >> 0b10 );
	(GPIO_ReadPin(&handlerPinC7) >> 0b11 );
	(GPIO_ReadPin(&handlerPinA6) >> 0b11 );
	(GPIO_ReadPin(&handlerPinB8) >> 0b100 );
	(GPIO_ReadPin(&handlerPinC6) >> 0b101 );
	(GPIO_ReadPin(&handlerPinC9) >> 0b110 );

    if (GPIO_ReadPin(&handlerPinC13) != 0b1){
    	for(uint8_t cont=1; cont<=60; cont++){
    		GPIOA -> ODR |= cont;
    		GPIOB -> ODR |= cont;
    		GPIOC -> ODR |= cont;

    		for (uint32_t z=0; z<=1380000; z++){
    		}

    	}
	} else {
    	for(uint8_t cont=60; cont>=1; cont--){
    		for (uint32_t z=0; z<=1380000; z++){
    		}

    	}

	}

	// Este es el ciclo principal, donde se ejecuta todo el programa
	while(1){
		NOP();
	}


}








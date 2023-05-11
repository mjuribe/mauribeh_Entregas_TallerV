/**
 * **************************************************************************************************
 * @file
 * @author
 * @brief
 * **************************************************************************************************
 */


#include <stdint.h>
#include <stm32f4xx.h>
#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "ExtiDriver.h"
#include "USARTxDriver.h"
#include <math.h>

// Handler del Blinky simple
GPIO_Handler_t handlerBlinkyPin = {0};

GPIO_Handler_t handlerUserButton = {0};
EXTI_Config_t handlerUserButtonExti = {0};

BasicTimer_Handler_t handlerBlinkyTimer = {0};

/* Elemento para hacer la comunicacion serial */
GPIO_Handler_t handlerPinTX ={0};
GPIO_Handler_t handlerPinRX ={0};
USART_Handler_t usart2Comm={0};
uint8_t sendMsg=0;
uint8_t usart2DataReceived=0;

char bufferMsg[64]={0};

float valueA= 123.4567f;
float valueB= 987.7654f;
float valueC= 0.0f;

// Definicion de las cabeceras de las funciones
void initSystem(void);

int main (void){

	// Activamos el coprocesador matematico FPU
	SCB->CPACR |= (0xF << 20);

	// Iniciamos todos los elementos del sistema
	initSystem();

	/* Loop forever */
	while(1){
		if(usart2DataReceived!='\0'){

			/* Realiza operacion de punto flotante cuando se recibe
			 * algun caracter por el puerto serial */
			valueC=valueA*valueB;
			sprintf(bufferMsg, "ValueC = %#.3f \n", valueC);
			writeMsg(&usart2Comm, bufferMsg);
			usart2DataReceived = '\0';


		}
	}

}

void initSystem(void){

}


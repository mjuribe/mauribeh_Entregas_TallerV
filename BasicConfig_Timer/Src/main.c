/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Maria Jose Uribe Henao
 * @brief          : Configuracion basica de un proyecto
 ******************************************************************************
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stm32f4xx.h>
#include "GPIOxDriver.h"

GPIO_Handler_t handlerOnBoardLed = {0};

int main (void){

	/* Configuracion del Pin */
	handlerOnBoardLed.pGPIOx                          = GPIOA;
	handlerOnBoardLed.GPIO_PinConfig.GPIO_PinNumber   = PIN_5;
	handlerOnBoardLed.GPIO_PinConfig.GPIO_PinMode     = GPIO_MODE_OUT;
	handlerOnBoardLed.GPIO_PinConfig.GPIO_PinOPType   = GPIO_OTYPE_PUSHPULL;
	handlerOnBoardLed.GPIO_PinConfig.GPIO_PinSpeed    = GPIO_OSPEED_FAST;

	GPIO_Config(&handlerOnBoardLed);

	/* Configuracion del TIMER */

    // Activando la senal del reloj
	RCC -> APB1ENR &= ~RCC_APB1ENR_TIM2EN;
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;

	// Direccion
	TIM2-> CR1 &= ~TIM_CR1_DIR;

	// Preescaler
	TIM2 -> PSC = 16000;

	// Configurar el CNT
	TIM2 -> CNT = 0;

	// COnfigurar ARR
	TIM2 -> ARR = 250;

	// Activar el timer
	TIM2 -> CR1 |= TIM_CR1_CEN;

	while (1){

		if(TIM2 -> ST & TIM_SR_UIF){
			TIM2-> SR &= ~TIM_SR_UIF;
			//GPIO_TooglePin(&handlerOnBoardLed);

		}
	}




}

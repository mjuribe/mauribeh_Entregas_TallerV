/*
 * PLLDriver.c
 *
 *  Created on: May 17, 2023
 *      Author: majo
 */

#include "PLLDriver.h"

void PLL_100Mhz(void){
	RCC -> PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC);

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM); // Limpiamos
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLM_3); // Ponemos un 8 en el PLLM

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN); // Limpiamos
	/* Ponemos PLLN en 100 */
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLN_2);
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLN_5);
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLN_6);

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP); // Limpiamos

	/* Latencia del FLASH_ACR para que se demore y pueda hacer el registro */
	// 3 Wait states
	FLASH -> ACR &= ~(FLASH_ACR_LATENCY); // Limpiamos
	FLASH -> ACR |= (FLASH_ACR_LATENCY_1WS);
	FLASH -> ACR |= (FLASH_ACR_LATENCY_2WS);

	/* Configuramos el MC01 (PIN A8 como funcion alternativa 00) */

	// Seleccionamos la senal PLL
	RCC -> CFGR |= RCC_CFGR_MCO1_0;
	RCC -> CFGR |= RCC_CFGR_MCO1_1;

	// Utilizamos un prescaler para poder ver la senal en el osciloscopio
	RCC -> CFGR |= RCC_CFGR_MCO1PRE_0;
	RCC -> CFGR |= RCC_CFGR_MCO1PRE_1;
	RCC -> CFGR |= RCC_CFGR_MCO1PRE_2;

	// Encender el PLL

	RCC->CR |= RCC_CR_PLLON;

	// Esperamos que el PLL se cierre (estabilizacion)
	while (!(RCC->CR & RCC_CR_PLLRDY)){
		__NOP();
	}

	// Cambiamos el CPU Clock source cambiando los SW bits (System Clock Switch)
	/* System Clock Switch para PLL */
	RCC -> CFGR &= ~(RCC_CFGR_SW); // Limpiamos
	RCC -> CFGR |= (RCC_CFGR_SW_1);

}

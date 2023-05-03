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
#include "stm32f411xx_hal.h"
/**
 * Funcion principal del programa
 */
int main(void)
{
	// Configuracion inicial del MCU
	RCC ->AHB1ENR &= ~(1<<0); // Limpiando la posicion 0 del registro
	RCC ->AHB1ENR |= (1<<0);

	// Configurando el pin PA5 como salida
	GPIOA -> MODER &= ~(0b11 << 10); // Limpiando las posiciones 11:10 del MODER
	GPIOA -> MODER |= (0b01 << 10); // Configurando el pinA5 como salida

	// Config. OSPEED
	GPIOA -> OTYPER &= ~(1 << 5); //Limpiamos la posicion, configuracion push-pull

	// Config. OSPEED
	GPIOA -> OSPEEDR &= ~(0b11 << 10); // Limpiando las posiciones 11:10
	GPIOA -> OSPEEDR |= (0b10 << 10);  // Velocidad de salida en Fast

	// Config. de las resistencias de PU-PD
	GPIOA -> PUPDR &= ~(0b11 << 10);

	//Config. el pin PAS como salida
	GPIOA -> ODR &= ~(1 << 5); //Limpiamos la salida PAS, apaga el led
	for (uint32_t i = 0; i < 1380000; i++);
	GPIOA -> ODR |= (1 << 5);  //Enciende el LED

	for (uint32_t i = 0; i < 1380000; i++);
	GPIOA -> ODR &= (0 << 5);  //Apaga el LED

	for (uint32_t i = 0; i < 1380000; i++);
	GPIOA -> ODR |= (1 << 5);  //Enciende el LED

	for (uint32_t i = 0; i < 1380000; i++);
	GPIOA -> ODR &= (0 << 5);  //Apaga el LED
	for (uint32_t i = 0; i < 1380000; i++);
	GPIOA -> ODR |= (1 << 5);  //Enciende el LED

	for (uint32_t i = 0; i < 1380000; i++);
	GPIOA -> ODR &= (0 << 5);  //Apaga el LED



    /* Loop forever */
	while(1){

	}
	return 0;
}

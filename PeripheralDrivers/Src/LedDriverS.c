/*
 * LedDriverS.c
 *
 *  Created on: Jun 27, 2023
 *      Author: majo
 */

#include "LedDriverS.h"


void escribirUnoS(void){
	GPIOA->ODR |= (1 << 6);
	delay_50ns(16);
	GPIOA->ODR &= ~(1 << 6);
	delay_50ns(9);
}

void escribirCeroS(void){
	GPIOA->ODR |= (1 << 6);
	delay_50ns(5);
	GPIOA->ODR &= ~(1 << 6);
	delay_50ns(5);
}

void rojoS(void){
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirUnoS();
	escribirUnoS();
	escribirUnoS();
	escribirUnoS();
	escribirUnoS();
	escribirUnoS();
	escribirUnoS();
	escribirUnoS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
}

void apagadoS(void){
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
	escribirCeroS();
}

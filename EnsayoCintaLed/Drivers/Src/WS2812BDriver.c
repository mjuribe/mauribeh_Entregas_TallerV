/*
 * WS2812BDriver.C
 *
 *  Created on: Jun 27, 2023
 *      Author: majo
 */


#include "GPIOxDriver.h"
#include "WS2812BDriver.h"

//void escribirUno(GPIO_Handler_t *pGPIOHandler){
void escribirUno(void){

//pGPIOHandler->pGPIOx->ODR |= (0b1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);
GPIOB->ODR |= 0b1;

__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();

//pGPIOHandler->pGPIOx->ODR &= ~(0b1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);
GPIOB->ODR &= ~0b1;

__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
}

void escribirCero(void){

//pGPIOHandler->pGPIOx->ODR |= (0b1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);
GPIOB->ODR |= 0b1;

__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();


//pGPIOHandler->pGPIOx->ODR &= ~(0b1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);
GPIOB->ODR &= ~0b1;

__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();
__NOP();

}

void limpiarLed(void){
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();

}

void verde(void){
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
}

void fucsia(void){
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
}

void azul(void){
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
}


void rojo(void){
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
}


void amarillo(void){
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
}

void cian(void){
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
}

void naranja(void){
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirUno();
escribirUno();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
}

void blanco(void){
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirCero();
escribirUno();
escribirUno();
}

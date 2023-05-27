/**
 * **************************************************************************************************
 * @file      : Led.c
 * @author    : Maria Jose Uribe Henao
 * @brief     :
 * **************************************************************************************************
 */

#include <stdint.h>
#include <stm32f4xx.h>
#include "ExtiDriver.h"
#include "BasicTimer.h"
#include "GPIOxDriver.h"
#include "PLLDriver.h"
#include "LedDriver.h"

/* Definicion de los elementos handler del sistema */
GPIO_Handler_t handlerPinPLL = {0}; // Funcion Alternativa
GPIO_Handler_t handlerPinPrueba = {0};  // Tiempos para los leds
// Handler del Blinky simple
GPIO_Handler_t handlerBlinkyPin = {0};

// Handler de los timers
BasicTimer_Handler_t handlerBlinkyTimer = {0};
BasicTimer_Handler_t handlerResetTimer = {0};

/* Prototipos de las funciones del main*/
void init_hardware(void);
void escribirUno(void);
void escribirCero(void);
void Color(uint8_t r,uint8_t g,uint8_t b);
void correrArreglo(void);
void resetLed(void);
uint8_t variable = 0;
uint32_t colorLED = 0;
/**/

uint8_t x = 0;
int (*Arreglo[24])();
//int (*Intento[2])();

int main(void) {

	/*Inicialización de todos los elementos del sistema*/
	init_hardware();

//	azul();
//	verde();
//	verde();
//	verde();

//	int (*Intento[2])={
//	(void *)&escribirUno,
//	(void *)&escribirCero,
//	};


	Color(0,0,0);
	correrArreglo();
//	Color(0,150,0);
//	correrArreglo();
//	Color(150,0,150);
//	correrArreglo();
//	Color(0,150,150);
//	correrArreglo();
//	Color(150,0,0);
//	correrArreglo();
//	x=1;
//
//	if ((variable > 1) | (variable < 10 )){
//		Color(150,150,0);
//		correrArreglo();
//		Color(0,150,0);
//		correrArreglo();
//		Color(150,0,150);
//		correrArreglo();
//		Color(0,150,150);
//		correrArreglo();
//		Color(150,0,0);
//		correrArreglo();
//	} else if ((variable > 10) | (variable < 20 )){
//		Color(0,150,0);
//		correrArreglo();
//		Color(0,150,0);
//		correrArreglo();
//		Color(150,0,0);
//		correrArreglo();
//		Color(0,150,0);
//		correrArreglo();
//		Color(150,0,0);
//		correrArreglo();
//	}
//


	while(1){
	}
	return 0;

}

/**/
void init_hardware(void) {

	PLL_100Mhz();

	// ----------------------------BLINKY SIMPLE ----------------------------------------
	/* Configuracion del LED2 - PA5 - Blinky Simple */
	handlerBlinkyPin.pGPIOx = GPIOA;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinNumber = PIN_5;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_FAST;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;

	//Cargar la configuracion del LED2 en los registros
	GPIO_Config(&handlerBlinkyPin);

	/*Configuracion del Pin para ver la velocidad */
	handlerPinPLL.pGPIOx = GPIOA;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinNumber = PIN_8;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_FAST;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;

	/* Cargamos la configuracion del Pin en los registros*/
	GPIO_Config(&handlerPinPLL);

	/*Configuracion del Pin para el control de los leds */
	handlerPinPrueba.pGPIOx = GPIOA;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinNumber = PIN_6;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_FAST;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;

	/* Cargamos la configuracion del Pin en los registros*/
	GPIO_Config(&handlerPinPrueba);

	// ---------------------------- TIMERS ----------------------------------------
	/* Configuracion del TIM2 para que haga un blinky cada 250ms */
	handlerBlinkyTimer.ptrTIMx = TIM2;
	handlerBlinkyTimer.TIMx_Config.TIMx_mode = BTIMER_MODE_UP;
	handlerBlinkyTimer.TIMx_Config.TIMx_speed = BTIMER_SPEED_100MHz_1ms;
	handlerBlinkyTimer.TIMx_Config.TIMx_period = 500;
	handlerBlinkyTimer.TIMx_Config.TIMx_interruptEnable = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerBlinkyTimer);

	handlerResetTimer.ptrTIMx = TIM3;
	handlerResetTimer.TIMx_Config.TIMx_mode = BTIMER_MODE_UP;
	handlerResetTimer.TIMx_Config.TIMx_speed = BTIMER_SPEED_100MHz_10us;
	handlerResetTimer.TIMx_Config.TIMx_period = 5;
	handlerResetTimer.TIMx_Config.TIMx_interruptEnable = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerResetTimer);

}


void Color(uint8_t r,uint8_t g,uint8_t b){
	colorLED = 0;

	colorLED |= (g << 0);
	colorLED |= (r << 8);
	colorLED |= (b << 16);

//	void (*punteroCero)(void);
//	punteroCero = &escribirCero();
//
//	void (*punteroUno)(void);
//	punteroUno = &escribirUno();

	for(int8_t i = 0; i<24; i++){
		if (((colorLED >> i)&(0b1)) == 1){
			*(Arreglo+i)= (void *)&escribirUno;
		}
		else if (((colorLED >> i)&(0b1)) == 0){
			*(Arreglo+i)= (void *)&escribirCero;
		}
	}

}

void correrArreglo(void){
	Arreglo[0]();
	Arreglo[1]();
	Arreglo[2]();
	Arreglo[3]();
	Arreglo[4]();
	Arreglo[5]();
	Arreglo[6]();
	Arreglo[7]();
	Arreglo[8]();
	Arreglo[9]();
	Arreglo[10]();
	Arreglo[11]();
	Arreglo[12]();
	Arreglo[13]();
	Arreglo[14]();
	Arreglo[15]();
	Arreglo[16]();
	Arreglo[17]();
	Arreglo[18]();
	Arreglo[19]();
	Arreglo[20]();
	Arreglo[21]();
	Arreglo[22]();
	Arreglo[23]();

}



/* Funciones de los timers */
// Blinky Simple
void BasicTimer2_Callback(void){
	GPIOxTooglePin(&handlerBlinkyPin);
	variable++;
	if (variable == 50){
		variable=0;
	}
}
void BasicTimer3_Callback(void){
//	if(x==1){
//		GPIOA->ODR &= ~(1 << 6);
//		x=0;
//	}
}





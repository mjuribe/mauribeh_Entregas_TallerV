/**
 * **************************************************************************************************
 * @file     : clock_main.c
 * @author   : Maria Jose Uribe Henao
 * @brief    : Main proyecto
 * **************************************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stm32f4xx.h>
#include "arm_math.h"

#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "ExtiDriver.h"
#include "USARTxDriver.h"
#include "SysTickDriver.h"
#include "I2CDriver.h"
#include "PwmDriver.h"
#include "PLLDriver.h"
#include "RtcDriver.h"
#include "AdcDriver.h"
#include "LedDriver.h"

/* Definicion de las macros */
#define PLL_100_CLOCK_CONFIGURED  2
#define PLL_100  1

/* Definicion de variables */

// Handler pin del Blinky simple
GPIO_Handler_t handlerBlinkyPin = { 0 };
GPIO_Handler_t handlerPinLed = { 0 };

/* Handler del RTC */
RTC_t handlerRTC = { 0 };

/* Handler de los timers */
BasicTimer_Handler_t handlerBlinkyTimer = { 0 };

// Definicion de las cabeceras de las funciones
void initSystem(void);

int main(void) {
	// Activamos el coprocesador matematico FPU
	SCB->CPACR |= (0xF << 20);
	//Inicio del sistemaS
	initSystem();
	//Frecuencia del micro a 80MHz
	configPLL(PLL_100);
	// Se configura el systick a 80MHz
	config_SysTick_ms(PLL_100_CLOCK_CONFIGURED);

	while (1) {
		delay_ms(1000);
		verde();
		rojo();
		magenta();
		amarillo();
		delay_ms(1000);
		azul();
		apagado();
		amarillo();
		apagado();

	} // Fin del while
	return (0);
} // Fin del main

void initSystem(void) {

	// ----------------------------BLINKY SIMPLE ----------------------------------------
	/* Configuracion del LED - PH1 - Blinky Simple */
	handlerBlinkyPin.pGPIOx                             = GPIOA;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinNumber      = PIN_5;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OTYPE_PUSHPULL;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_OSPEED_FAST;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;

	//Cargar la configuracion del LED2 en los registros
	GPIO_Config(&handlerBlinkyPin);

	// ---------------------------- CONFIGURACION DE LOS TIMERS  ----------------------------------------
	/* Configuracion del TIM2 para que haga un blinky cada 250ms */
	handlerBlinkyTimer.ptrTIMx                               = TIM2;
	handlerBlinkyTimer.TIMx_Config.TIMx_mode                 = BTIMER_MODE_UP;
	handlerBlinkyTimer.TIMx_Config.TIMx_speed                = BTIMER_SPEED_100Mhz_100us;
	handlerBlinkyTimer.TIMx_Config.TIMx_period               = 2500;
	handlerBlinkyTimer.TIMx_Config.TIMx_interruptEnable      = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerBlinkyTimer);

	// ---------------------------- CONFIGURACION PIN CONTROL DE LEDS  ----------------------------------------
	/*Configuracion del Pin para el control de los leds */
	handlerPinLed.pGPIOx                                     = GPIOA;
	handlerPinLed.GPIO_PinConfig.GPIO_PinNumber              = PIN_6;
	handlerPinLed.GPIO_PinConfig.GPIO_PinMode                = GPIO_MODE_OUT;
	handlerPinLed.GPIO_PinConfig.GPIO_PinOPType              = GPIO_OTYPE_PUSHPULL;
	handlerPinLed.GPIO_PinConfig.GPIO_PinSpeed               = GPIO_OSPEED_FAST;
	handlerPinLed.GPIO_PinConfig.GPIO_PinPuPdControl         = GPIO_PUPDR_NOTHING;
	handlerPinLed.GPIO_PinConfig.GPIO_PinAltFunMode          = AF0;

	/* Cargamos la configuracion del Pin en los registros*/
	GPIO_Config(&handlerPinLed);

	// ---------------------------- CONFIGURACION INICIAL DEL RTC ----------------------------------------
	handlerRTC.seconds                                  = 12;
	handlerRTC.minutes                                  = 34;
	handlerRTC.hour                                     = 6;
	handlerRTC.weekDay                                  = RTC_WEEKDAY_WEDNESDAY;
	handlerRTC.date                                     = 7;
	handlerRTC.month                                    = 6;
	handlerRTC.year                                     = 23;
	config_RTC(&handlerRTC);

}

/* Callbacks de los Timers */
void BasicTimer2_Callback(void) {
	GPIOxTooglePin(&handlerBlinkyPin);
}






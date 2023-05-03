
#include <stdint.h>
#include <stm32f4xx.h>
#include "ExtiDriver.h"
#include "BasicTimer.h"
#include "GPIOxDriver.h"

/* Definicion de los elementos handler del sistema */
GPIO_Handler_t handlerPinPrueba = {0}; // PIN PA5
GPIO_Handler_t handlerPinPLL = {0}; // Funcion Alternativa


/* Prototipos de las funciones del main*/
void init_hardware(void);
void escribirUno(void);
/**/

int main(void) {

	/*Inicialización de todos los elementos del sistema*/

	init_hardware();

	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();
	escribirUno();

	return 0;

}

/**/
void init_hardware(void) {

	/*Configuracion del BlinkyPin - PA5 para usarlo como LED de estado */
	handlerPinPrueba.pGPIOx = GPIOA;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinNumber = PIN_5;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_FAST;
	handlerPinPrueba.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;
	/* Cargamos la configuracion del BlinkyPin en los registros*/
	GPIO_Config(&handlerPinPrueba);

	/*Configuracion del Pin para ver la velocidad */
	handlerPinPLL.pGPIOx = GPIOA;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinNumber = PIN_8;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_FAST;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;
	handlerPinPLL.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AFRH_AFRH0_0;

	/* Cargamos la configuracion del BlinkyPin en los registros*/
	GPIO_Config(&handlerPinPLL);

	RCC -> PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC);

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM); // Limpiamos
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLM_3); // Ponemos un 8 en el PLLM

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN); // Limpiamos
	/* Ponemos PLLN en 100 */
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLN_2);
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLN_5);
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLN_6);

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP); // Limpiamos
//	//Ponemos  PLLP en 2
//	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP_0);
//	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP_1);

	/* Latencia del FLASH_ACR para que se demore y pueda hacer el registro */
	// 3 Wait states
	FLASH -> ACR &= ~(FLASH_ACR_LATENCY); // Limpiamos
	FLASH -> ACR |= (FLASH_ACR_LATENCY_1WS);
	FLASH -> ACR |= (FLASH_ACR_LATENCY_2WS);

	/* System Clock Switch para PLL */
	RCC -> CFGR &= ~(RCC_CFGR_SW); // Limpiamos
	RCC -> CFGR |= (RCC_CFGR_SW_1);

	/* Configuramos el MC01 (PIN A8 como funcion alternativa) */

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


}








void escribirUno(void) {


	__NOP();

	GPIOA->ODR &= ~(1 << 5);
	__NOP();

	GPIOA->ODR |= (1 << 5);
	__NOP();
	__NOP();
	__NOP();
	__NOP();

	GPIOA->ODR &= ~(1 << 5);
	__NOP();

	GPIOA->ODR |= (1 << 5);	__NOP();
	__NOP();
	__NOP();
	__NOP();





}



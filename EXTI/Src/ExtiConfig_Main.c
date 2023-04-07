#include <stdint.h>
#include <stm32f4xx.h>
#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "ExtiDriver.h"

/* Definicion de los elementos del sistema */
GPIO_Handler_t handlerLED2 = {0};
GPIO_Handler_t handlerUserButton = {0};
BasicTimer_Handler_t handlerBlinkyTimer = {0};
BasicTimer_Handler_t handlerTimer3 = {0};
BasicTimer_Handler_t handlerTimer4 = {0};
uint32_t counterExti13=0;
uint32_t timer2=0;
uint32_t timer3=0;
uint32_t timer4=0;
EXTI_Config_t handlerExti = {0};

/* Prototipos de las funciones */
void callback_extInt13(void);
void init_Hardware(void);

int main (void){
	// Inicializacion de todos los elementos del sistema */
	init_Hardware();

	while(1){
	}
}

void init_Hardware(void){
	/* COnfiguracion del LED2 - PA5 */
	handlerLED2.pGPIOx = GPIOA;
	handlerLED2.GPIO_PinConfig.GPIO_PinNumber = PIN_5;
	handlerLED2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	handlerLED2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;
	handlerLED2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_FAST;
	handlerLED2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;

	//Cargar la configuracion del LED2 en los registros
	GPIO_Config(&handlerLED2);
	GPIO_WritePin(&handlerLED2, SET);

	/* Configuracion del TIM2 para que haga un blinky cada 300ms */
	handlerBlinkyTimer.ptrTIMx = TIM2;
	handlerBlinkyTimer.TIMx_Config.TIMx_mode = BTIMER_MODE_UP;
	handlerBlinkyTimer.TIMx_Config.TIMx_speed = BTIMER_SPEED_1ms;
	handlerBlinkyTimer.TIMx_Config.TIMx_period = 250;
	handlerBlinkyTimer.TIMx_Config.TIMx_interruptEnable = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerBlinkyTimer);

	/* Configuracion del TIM2 para que haga un blinky cada 300ms */
	handlerTimer3.ptrTIMx = TIM3;
	handlerTimer3.TIMx_Config.TIMx_mode = BTIMER_MODE_UP;
	handlerTimer3.TIMx_Config.TIMx_speed = BTIMER_SPEED_1ms;
	handlerTimer3.TIMx_Config.TIMx_period = 500;
	handlerTimer3.TIMx_Config.TIMx_interruptEnable = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerTimer3);

	/* Configuracion del TIM2 para que haga un blinky cada 300ms */
	handlerTimer4.ptrTIMx = TIM4;
	handlerTimer4.TIMx_Config.TIMx_mode = BTIMER_MODE_UP;
	handlerTimer4.TIMx_Config.TIMx_speed = BTIMER_SPEED_1ms;
	handlerTimer4.TIMx_Config.TIMx_period = 750;
	handlerTimer4.TIMx_Config.TIMx_interruptEnable = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerTimer4);

	/* Configuracion del exti */
	/* Configurar el pin como una entrada digital */
	handlerUserButton.pGPIOx = GPIOC;
	handlerUserButton.GPIO_PinConfig.GPIO_PinNumber = PIN_13;
	handlerUserButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	handlerUserButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;

	/* Cargando la configuracion en los registros del MCU */
	handlerExti.pGPIOHandler = &handlerUserButton;
	handlerExti.edgeType = EXTERNAL_INTERRUPT_RISING_EDGE;
	extInt_Config(&handlerExti);
//
//	/* 2. Activando la clock signal del SYSCFG */
//	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//
//	/* 3. Configurando el Mux 13 para que utilice el puerto C  0xF -> 0b1111*/
//	SYSCFG -> EXTICR[3]&= ~(0xF << SYSCFG_EXTICR4_EXTI13_Pos);
//	SYSCFG -> EXTICR[3]|= SYSCFG_EXTICR4_EXTI13_PC; // Seleccionando el puerto C para el Mux13
//
//	/* Configurar el tipo de flanco */ //REVISAR REFERENCE MANUAL 205
//	EXTI->FTSR = 0; // Desactivamos todos los posibles flancos de bajada
//	EXTI->RTSR = 0; // Llevando el registro a un valor conocido
//	EXTI->RTSR |= EXTI_RTSR_TR13;
//
//	/* 4.b Activar interrupcion */
//	EXTI->IMR = 0;
//	EXTI->IMR |= EXTI_IMR_IM13; // Activamos la interrupcion 13
//
//	/* 5.a Desactivar TODAS las interrupciones */
//	__disable_irq();
//
//	/*5.b Matricular la interrupcion en el NVIC */
//	NVIC_EnableIRQ(EXTI15_10_IRQn);
//
//	/* 5.c Crear ISR */
//	/* 5.d Crear el callback */
//	/* 5.e Activar las interrupciones */
//	__enable_irq();
//



}// Termina el init_Hardware

void callback_extInt13(void){
	counterExti13++;
}


void BasicTimer2_Callback(void){
	GPIOxTooglePin(&handlerLED2);
	timer2++;
}

void BasicTimer3_Callback(void){
	timer3++;

}

void BasicTimer4_Callback(void){
	timer4++;

}

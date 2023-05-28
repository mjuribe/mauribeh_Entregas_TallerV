/**
 * **************************************************************************************************
 * @file     : Maria Jose Uribe Henao
 * @author   : TestPWM_Main.c
 * @brief    : Pruebas a un PWM Simple
 * **************************************************************************************************
 */


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stm32f4xx.h>

#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "ExtiDriver.h"
#include "USARTxDriver.h"
#include "SysTickDriver.h"
#include "I2CDriver.h"
#include "PwmDriver.h"
#include <math.h>

// Handler del Blinky simple
GPIO_Handler_t handlerBlinkyPin = {0};
BasicTimer_Handler_t handlerBlinkyTimer = {0};

/* Elemento para hacer la comunicacion serial */
GPIO_Handler_t handlerPinTX ={0};
GPIO_Handler_t handlerPinRX ={0};
USART_Handler_t usart2Comm={0};
uint8_t sendMsg=0;
uint8_t usart2DataReceived=0;
uint8_t printMsg = 0;

/* Elementos para el PWM */
GPIO_Handler_t handlerPinPwmChannel = {0};
PWM_Handler_t handlerSignalPWM = {0};

uint16_t duttyValue = 1500;

char bufferMsg[64] = {0};

// Definicion de las cabeceras de las funciones
void initSystem(void);

int main (void){

	// Activamos el coprocesador matematico FPU
	SCB->CPACR |= (0xF << 20);

	// Iniciamos todos los elementos del sistema
	initSystem();

	/* Loop forever */
	while(1){
		/* Verificando el PWM */
		if(usart2DataReceived != '\0'){
			if (usart2DataReceived == 'd'){
				// Down
				duttyValue -=10;
				updateDuttyCycle(&handlerSignalPWM, duttyValue);
			}
			/* Para probar el seno */
			if (usart2DataReceived == 'u'){
				// Up
				duttyValue +=10;
				// Lanzamos un nuevo ciclo de adquisiciones
				updateDuttyCycle(&handlerSignalPWM, duttyValue);
			}
			/* Imprimimos el mensaje */
			sprintf(bufferMsg, "dutty =%u \n", (unsigned int)duttyValue);
			writeMsg(&usart2Comm, bufferMsg);

			/* Cambiamos el estado del elemento que controla la entrada */
			usart2DataReceived = '\0';

		}


	}//Fin del while

} //Fin del main


void initSystem(void){

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

	/* Configuracion del TIM2 para que haga un blinky cada 300ms */
	handlerBlinkyTimer.ptrTIMx = TIM2;
	handlerBlinkyTimer.TIMx_Config.TIMx_mode = BTIMER_MODE_UP;
	handlerBlinkyTimer.TIMx_Config.TIMx_speed = BTIMER_SPEED_100us;
	handlerBlinkyTimer.TIMx_Config.TIMx_period = 2500;
	handlerBlinkyTimer.TIMx_Config.TIMx_interruptEnable = BTIMER_INTERRUP_ENABLE;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerBlinkyTimer);

	/* Configuracion de la comunicacion serial*/
	handlerPinTX.pGPIOx                               = GPIOA;
	handlerPinTX.GPIO_PinConfig.GPIO_PinNumber        = PIN_2;
	handlerPinTX.GPIO_PinConfig.GPIO_PinMode          = GPIO_MODE_ALTFN;
	handlerPinTX.GPIO_PinConfig.GPIO_PinAltFunMode    = AF7;
	GPIO_Config(&handlerPinTX);

	handlerPinRX.pGPIOx                               = GPIOA;
	handlerPinRX.GPIO_PinConfig.GPIO_PinNumber        = PIN_3;
	handlerPinRX.GPIO_PinConfig.GPIO_PinMode          = GPIO_MODE_ALTFN;
	handlerPinRX.GPIO_PinConfig.GPIO_PinAltFunMode    = AF7;
	GPIO_Config(&handlerPinRX);

	usart2Comm.ptrUSARTx                       = USART2;
	usart2Comm.USART_Config.USART_baudrate     = USART_BAUDRATE_19200;
	usart2Comm.USART_Config.USART_datasize     = USART_DATASIZE_8BIT;
	usart2Comm.USART_Config.USART_parity       = USART_PARITY_NONE;
	usart2Comm.USART_Config.USART_stopbits     = USART_STOPBIT_1;
	usart2Comm.USART_Config.USART_mode         = USART_MODE_RXTX;
	usart2Comm.USART_Config.USART_enableIntRX  = USART_RX_INTERRUP_ENABLE;
	usart2Comm.USART_Config.USART_enableIntTX  = USART_TX_INTERRUP_DISABLE;

	USART_Config(&usart2Comm);

	/* Configuramos el PWM */
	handlerPinPwmChannel.pGPIOx                                = GPIOC;
	handlerPinPwmChannel.GPIO_PinConfig.GPIO_PinNumber         = PIN_7;
	handlerPinPwmChannel.GPIO_PinConfig.GPIO_PinMode           = GPIO_MODE_ALTFN;
	handlerPinPwmChannel.GPIO_PinConfig.GPIO_PinOPType         = GPIO_OTYPE_PUSHPULL;
	handlerPinPwmChannel.GPIO_PinConfig.GPIO_PinSpeed          = GPIO_OSPEED_FAST;
	handlerPinPwmChannel.GPIO_PinConfig.GPIO_PinPuPdControl    = GPIO_PUPDR_NOTHING;
	handlerPinPwmChannel.GPIO_PinConfig.GPIO_PinAltFunMode     = AF2;

	/* Cargamos la configuracion en los registros del MCU */
	GPIO_Config(&handlerPinPwmChannel);

	/* Configuracion del TIM3 para que genere la signal PWM*/
	handlerSignalPWM.ptrTIMx                = TIM3;
	handlerSignalPWM.config.channel         = PWM_CHANNEL_2;
	handlerSignalPWM.config.duttyCicle      = duttyValue;
	handlerSignalPWM.config.periodo         = 20000;
	handlerSignalPWM.config.prescaler       = 16;

	/* Cargamos la configuracion en los registros del MCU */
	pwm_Config(&handlerSignalPWM);

	enableOutput(&handlerSignalPWM);
	startPwmSignal(&handlerSignalPWM);
}

void BasicTimer2_Callback(void){
	GPIOxTooglePin(&handlerBlinkyPin);
	printMsg++;
	sendMsg++;
}

void usart2Rx_Callback(void){
	usart2DataReceived = getRxData();
}



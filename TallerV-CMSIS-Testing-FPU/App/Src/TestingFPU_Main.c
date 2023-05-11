/**
 * **************************************************************************************************
 * @file
 * @author
 * @brief
 * **************************************************************************************************
 */


#include <stdint.h>
#include <stm32f4xx.h>
#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "ExtiDriver.h"
#include "USARTxDriver.h"
#include <math.h>

// Handler del Blinky simple
GPIO_Handler_t handlerBlinkyPin = {0};

GPIO_Handler_t handlerUserButton = {0};
EXTI_Config_t handlerUserButtonExti = {0};

BasicTimer_Handler_t handlerBlinkyTimer = {0};

/* Elemento para hacer la comunicacion serial */
GPIO_Handler_t handlerPinTX ={0};
GPIO_Handler_t handlerPinRX ={0};
USART_Handler_t usart2Comm={0};
uint8_t sendMsg=0;
uint8_t usart2DataReceived=0;

char bufferMsg[64]={0};

float valueA= 123.4567f;
float valueB= 987.7654f;
float valueC= 0.0f;

// Definicion de las cabeceras de las funciones
void initSystem(void);

int main (void){

	// Activamos el coprocesador matematico FPU
	SCB->CPACR |= (0xF << 20);

	// Iniciamos todos los elementos del sistema
	initSystem();

	/* Loop forever */
	while(1){
		if(usart2DataReceived!='\0'){

			/* Realiza operacion de punto flotante cuando se recibe
			 * algun caracter por el puerto serial */
			valueC=valueA*valueB;
			sprintf(bufferMsg, "ValueC = %#.3f \n", valueC);
			writeMsg(&usart2Comm, bufferMsg);
			usart2DataReceived = '\0';


		}
	}

}

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
	handlerBlinkyTimer.TIMx_Config.TIMx_speed = BTIMER_SPEED_1ms;
	handlerBlinkyTimer.TIMx_Config.TIMx_period = 250;
	handlerBlinkyTimer.TIMx_Config.TIMx_interruptEnable = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerBlinkyTimer);

	/* Configuracion del exti */
	/* Configurar el pin como una entrada digital que entregara la interrupcion EXTI 13*/
	handlerUserButton.pGPIOx                               = GPIOC;
	handlerUserButton.GPIO_PinConfig.GPIO_PinNumber        = PIN_13;
	handlerUserButton.GPIO_PinConfig.GPIO_PinMode          = GPIO_MODE_IN;
	handlerUserButton.GPIO_PinConfig.GPIO_PinPuPdControl   = GPIO_PUPDR_NOTHING;
	GPIO_Config(&handlerUserButton);

	/* Cargando la configuracion en los registros del MCU */
	handlerUserButtonExti.pGPIOHandler = &handlerUserButton;
	handlerUserButtonExti.edgeType     = EXTERNAL_INTERRUPT_RISING_EDGE;
	extInt_Config(&handlerUserButtonExti);

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
	//usart2Comm.USART_Config.USART_enableIntRX  = USART_RX_INTERRUP_ENABLE; REVISAR!!!!!!!!
	//usart2Comm.USART_Config.USART_enableIntTX  = USART_TX_INTERRUP_DISABLE;

	USART_Config(&usart2Comm);

}

void callback_extInt13(void){
}


void BasicTimer2_Callback(void){
	GPIOxTooglePin(&handlerBlinkyPin);
}


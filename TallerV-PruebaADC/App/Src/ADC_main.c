/**
 * **************************************************************************************************
 * @file     : Maria Jose Uribe Henao
 * @author   : AccelTest_Main.c
 * @brief    : PRUEBAS EXAMEN - TALLER V
 * **************************************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stm32f4xx.h>

#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "USARTxDriver.h"
#include "AdcDriver.h"
#include "PwmDriver.h"

/* Definicion de variables */
/* Elementos para hacer la comunicacion serial */
GPIO_Handler_t handlerPinTX = {0};
GPIO_Handler_t handlerPinRX = {0};
USART_Handler_t handlerCommTerminal = {0};

// Handler del Blinky simple
GPIO_Handler_t handlerBlinkyPin = {0};
BasicTimer_Handler_t handlerMuestreo = {0};

/* Handler de los timers */
BasicTimer_Handler_t handlerBlinkyTimer = {0};

/* Handler para las señales por PWM */
GPIO_Handler_t handlerPinPwmChannel1 = {0};
PWM_Handler_t handlerSignalPwm1 = {0};
uint16_t duttyValue1 = 10;

/* Contadores y banderas */
uint8_t rxData = 0;
uint8_t bandera = 0;
uint8_t counterADC =0;
uint16_t numADC =0;

/* Arreglos */
char bufferData[64]= "Accel ADXL-345";
uint32_t datosADC[2][256]={0};

ADC_Config_t adcConfig1 = {0};
uint16_t adcData[2] = {0};
uint16_t adcDataSingle;
bool adcIsComplete = false;

char greetingMsg[] = "Taller V \n";

// Definicion de las cabeceras de las funciones
void initSystem(void);

int main (void){

	//Inicio del sistemaS
	initSystem();

	writeChar(&handlerCommTerminal, 'h');

	while(1){

		if(rxData != '\0'){

			writeChar(&handlerCommTerminal, rxData);
			if(rxData == 'm'){
				writeMsg(&handlerCommTerminal, greetingMsg);
			}else if(rxData == 'a'){
				writeMsg(&handlerCommTerminal, "ADC");
				for (int i=0; i<256; i++){
					sprintf(bufferData, "%u ; %u ; %d \n", (unsigned int )datosADC[0][i],(unsigned int )datosADC[1][i], i);
					writeMsg(&handlerCommTerminal, bufferData);
				}
				rxData = '\0';
			}
			//Para que no vuelva entrar. Solo cambia debido a la interrupcion
			rxData = '\0';
		}

//		//Hacemos un analisis de la cadena de datos obtenida
//		if (adcIsComplete == true){
//			//sprintf(bufferData, "%u \n", (unsigned int )adcDataSingle);
//			sprintf(bufferData, "%u\t%u \n", (unsigned int )adcData[0],(unsigned int )adcData[1]);
//			writeMsg(&handlerCommTerminal, bufferData);
//			adcIsComplete = false;
//
//		}
	} // Fin del while
	return(0);
} // Fin del main


void initSystem(void){

	// ----------------------------BLINKY SIMPLE ----------------------------------------
	/* Configuracion del LED - PH0 - Blinky Simple */
	handlerBlinkyPin.pGPIOx                             = GPIOA;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinNumber      = PIN_5;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OTYPE_PUSHPULL;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_OSPEED_FAST;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;

	//Cargar la configuracion del LED2 en los registros
	GPIO_Config(&handlerBlinkyPin);
	GPIO_WritePin(&handlerBlinkyPin, SET);

	// ---------------------------- CONFIGURACION DE LOS TIMERS  ----------------------------------------
	/* Configuracion del TIM2 para que haga un blinky cada 250ms */
	handlerBlinkyTimer.ptrTIMx                               = TIM2;
	handlerBlinkyTimer.TIMx_Config.TIMx_mode                 = BTIMER_MODE_UP;
	handlerBlinkyTimer.TIMx_Config.TIMx_speed                = BTIMER_SPEED_100us;
	handlerBlinkyTimer.TIMx_Config.TIMx_period               = 2500;
	handlerBlinkyTimer.TIMx_Config.TIMx_interruptEnable      = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerBlinkyTimer);

	// ---------------------------- CONFIGURACION DE LA COMUNICACION SERIAL  ----------------------------------------
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

	handlerCommTerminal.ptrUSARTx                       = USART2;
	handlerCommTerminal.USART_Config.USART_baudrate     = USART_BAUDRATE_115200;
	handlerCommTerminal.USART_Config.USART_datasize     = USART_DATASIZE_8BIT;
	handlerCommTerminal.USART_Config.USART_parity       = USART_PARITY_NONE;
	handlerCommTerminal.USART_Config.USART_stopbits     = USART_STOPBIT_1;
	handlerCommTerminal.USART_Config.USART_mode         = USART_MODE_RXTX;
	handlerCommTerminal.USART_Config.USART_enableIntRX  = USART_RX_INTERRUP_ENABLE;
	handlerCommTerminal.USART_Config.USART_enableIntTX  = USART_TX_INTERRUP_DISABLE;
	handlerCommTerminal.USART_Config.USART_frequency    = 16;

	USART_Config(&handlerCommTerminal);

//	// ---------------------------- CONFIGURACION DEL PWM  ----------------------------------------
	handlerPinPwmChannel1.pGPIOx                                = GPIOB;
	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinNumber         = PIN_9;
	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinMode           = GPIO_MODE_ALTFN;
	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinOPType         = GPIO_OTYPE_PUSHPULL;
	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinSpeed          = GPIO_OSPEED_FAST;
	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinPuPdControl    = GPIO_PUPDR_NOTHING;
	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinAltFunMode     = AF2;
	/* Cargamos la configuracion en los registros del MCU */
	GPIO_Config(&handlerPinPwmChannel1);

	/* Configuracion del TIM3 para que genere la signal PWM*/
	handlerSignalPwm1.ptrTIMx                = TIM4;
	handlerSignalPwm1.config.channel         = PWM_CHANNEL_4;
	handlerSignalPwm1.config.duttyCicle      = 3;
	handlerSignalPwm1.config.periodo         = 6;
	handlerSignalPwm1.config.prescaler       = 16;
	/* Cargamos la configuracion en los registros del MCU */
	pwm_Config(&handlerSignalPwm1);
	enableOutput(&handlerSignalPwm1);
	startPwmSignal(&handlerSignalPwm1);

	/* Cargando la configuracion para la conversion ADC */
	adcConfig1.numberOfChannels   = 2;
	uint8_t channels[2] 		  = { ADC_CHANNEL_0, ADC_CHANNEL_1 };
	adcConfig1.channel            = channels;
	adcConfig1.dataAlignment      = ADC_ALIGNMENT_RIGHT;
	adcConfig1.resolution         = ADC_RESOLUTION_12_BIT;
	uint16_t samplingPeriods[2]   = {0};
	samplingPeriods[0]			  = ADC_SAMPLING_PERIOD_28_CYCLES;
	samplingPeriods[1]			  = ADC_SAMPLING_PERIOD_28_CYCLES;
	adcConfig1.samplingPeriod     = samplingPeriods;
	adcConfig1.externalTrigger    = ADC_EXTERN_TIM_4_CHANNEL_4_RISING;
	adcConfig1.mode               = MULTIPLE;
	adc_Config(&adcConfig1);

}

/* Callbacks de las interrupciones */
void usart2Rx_Callback(void){
	rxData = getRxData();
}

/* Callbacks de los Timers */
void BasicTimer2_Callback(void){
	GPIOxTooglePin(&handlerBlinkyPin);
}

void adcComplete_Callback(void){

	adcData[counterADC] = getADC();
	datosADC[counterADC][numADC]= adcData[counterADC];
	counterADC++;
	if(numADC==256){
		numADC=0;
	}
	if(counterADC==2){
		counterADC=0;
		numADC++;
	}
	adcIsComplete = true;
}


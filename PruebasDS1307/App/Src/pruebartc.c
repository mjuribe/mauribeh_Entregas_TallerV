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
#include "AdcDriver.h"
#include "LedDriver.h"
#include "lines.h"
#include "Rtc1307.h"

/* Definicion de las macros */
#define PLL_100_CLOCK_CONFIGURED  2
#define PLL_100  1

/* Definicion de variables */

// Handler pin del Blinky simple
GPIO_Handler_t handlerBlinkyPin = { 0 };
GPIO_Handler_t handlerPinLed = { 0 };

/* Handler del RTC */
//RTC_t handlerRTC = { 0 };

/* Handler de los timers */
BasicTimer_Handler_t handlerBlinkyTimer = { 0 };
BasicTimer_Handler_t handlerMuestreo = { 0 };

/* Elementos para hacer la comunicacion serial */
GPIO_Handler_t handlerPinTX = { 0 };
GPIO_Handler_t handlerPinRX = { 0 };
USART_Handler_t handlerCommTerminal = { 0 };

/* Configuración para el I2C */
GPIO_Handler_t handlerI2CSDA =	{0};
GPIO_Handler_t handlerI2CSCL =	{0};
I2C_Handler_t  handlerRTC	 = {0};

uint8_t 	i2cBuffer 			= 0;
uint32_t 	systemTicks 		= 0;
uint32_t 	systemTicksStart 	= 0;
uint32_t 	systemTicksEnd		= 0;

/* Configuración para el RTC */
rtc_t			dateAndTimeRTC = {0};
uint8_t 			dataRTC[7];
getTime_t		dataRTCtest = {0};

uint8_t* reloj;
uint8_t hour[4];
uint8_t tomadedatos=1;
uint8_t stringComplete = 0;
uint8_t rxData = 0;
uint16_t counterReception = 0;
uint8_t parametro=0;
uint8_t colorled=0;

/* Configuracion de comandos por terminal serial*/
char bufferData[64] = "Inicio";
char bufferReception[64];
char userMsg[64];
char cmd[64];
char bufferDate[64];
char bufferTime[64];
unsigned int firstParameter = 10000;
unsigned int secondParameter = 10000;
unsigned int thirdParameter = 10000;
unsigned int tim=0;

// Definicion de las cabeceras de las funciones
void initSystem(void);
void minutero(void);
void manecillahora(uint16_t horaconf);
void parseCommands(char *ptrBufferReception);

int main(void) {
	// Activamos el coprocesador matematico FPU
	SCB->CPACR |= (0xF << 20);
	//Inicio del sistemaS
	initSystem();
	//Frecuencia del micro a 80MHz
	configPLL(PLL_100);
	// Se configura el systick a 80MHz
	config_SysTick_ms(PLL_100_CLOCK_CONFIGURED);
	writeMsg(&handlerCommTerminal, "PROYECTO TALLER V \n");

	while (1) {
//		if(tomadedatos==1){
//			tomadedatos=0;
//			minutero();
//		}
		if(rxData != '\0'){
			// Hacemos un "eco" con el valor que nos llega por el serial
			writeChar(&handlerCommTerminal, rxData);


			// Leemos los valores del los segundos transcurridos
			if(rxData == 's'){
				uint8_t sec = RTC_readByte(&handlerRTC,0x00);
				//uint8_t seconds = (sec & 0b00001111);
				sprintf(bufferData, "Segundos = %.2d \n",(int) sec);
				writeMsg(&handlerCommTerminal, bufferData);
				rxData = '\0';
			}
			else if(rxData == 'i'){
				RTC_init(&handlerRTC);
				dateAndTimeRTC.seconds 	= 30;
				dateAndTimeRTC.minutes 	= 59;
				dateAndTimeRTC.hour 	= 3;
				dateAndTimeRTC.weekDay 	= 3;
				dateAndTimeRTC.date		= 11;
				dateAndTimeRTC.month 	= 5;
				dateAndTimeRTC.year		= 7;

				RTC_SetDateTime(&handlerRTC, &dateAndTimeRTC);
				writeMsg(&handlerCommTerminal, "Inicializado correctamente");

				rxData = '\0';
			}
			else if(rxData == 'm'){
				uint8_t min = RTC_readByte(&handlerRTC,0x01);
				//uint8_t minutes = (min & 0b00001111);
				sprintf(bufferData, "Minutos = %.2d \n",(int) min);
				writeMsg(&handlerCommTerminal, bufferData);
				rxData = '\0';
			}
			else if(rxData == 'f'){
				//RTC_ReadDateTimeFull(&handlerRTC,dataRTC);
				uint8_t sec = RTC_readByte(&handlerRTC,0x00);
				uint8_t min = RTC_readByte(&handlerRTC,0x01);
				uint8_t hora = RTC_readByte(&handlerRTC,0x02);
				uint8_t day = RTC_readByte(&handlerRTC,0x04);
				uint8_t month = RTC_readByte(&handlerRTC,0x05);
				uint8_t year = RTC_readByte(&handlerRTC,0x06);

				sprintf(bufferData, "TIME: %.2d:%.2d:%.2d \n", (int) hora, (int) min, (int) sec);
				writeMsg(&handlerCommTerminal, bufferData);
				sprintf(bufferData, "La fecha actual es %.2d/%.2d/%.2d \n", (int) day, (int) month, (int) year);
				writeMsg(&handlerCommTerminal, bufferData);
				rxData = '\0';
			}
			rxData = '\0';
		}
		// El caracter '@' nos indica que es el final de la cadena
//			if (rxData != '\0') {
//				bufferReception[counterReception] = rxData;
//				counterReception++;
//
//				// If the incoming character is a newline, set a flag
//				// so the main loop can do something about it
//				if (rxData == '#') {
//					stringComplete = 1;
//
//					//Agrego esta linea para crear el string con el null al final
//					bufferReception[counterReception] = '\0';
//					counterReception = 0;
//				}
//				//Para que no vuelva entrar. Solo cambia debido a la interrupcion
//				rxData = '\0';
//			}
//
//			//Hacemos un analisis de la cadena de datos obtenida
//			if (stringComplete) {
//				parseCommands(bufferReception);
//				stringComplete = 0;
//			}

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

	/* Configuracion del TIM3 para un muestreo de la hora  */
	handlerMuestreo.ptrTIMx                               = TIM3;
	handlerMuestreo.TIMx_Config.TIMx_mode                 = BTIMER_MODE_UP;
	handlerMuestreo.TIMx_Config.TIMx_speed                = BTIMER_SPEED_100Mhz_100us;
	handlerMuestreo.TIMx_Config.TIMx_period               = 10000;
	handlerMuestreo.TIMx_Config.TIMx_interruptEnable      = 1;

	/* Cargando la configuracion del TIM3 en los registros */
	BasicTimer_Config(&handlerMuestreo);

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
	handlerCommTerminal.USART_Config.USART_frequency    = 100;
	handlerCommTerminal.USART_Config.USART_baudrate     = USART_BAUDRATE_115200;
	handlerCommTerminal.USART_Config.USART_datasize     = USART_DATASIZE_8BIT;
	handlerCommTerminal.USART_Config.USART_parity       = USART_PARITY_NONE;
	handlerCommTerminal.USART_Config.USART_stopbits     = USART_STOPBIT_1;
	handlerCommTerminal.USART_Config.USART_mode         = USART_MODE_RXTX;
	handlerCommTerminal.USART_Config.USART_enableIntRX  = USART_RX_INTERRUP_ENABLE;
	handlerCommTerminal.USART_Config.USART_enableIntTX  = USART_TX_INTERRUP_DISABLE;
	USART_Config(&handlerCommTerminal);

	// Configuramos los pines para el I2C SCL
	handlerI2CSCL.pGPIOx								= GPIOB;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinNumber			= PIN_10;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_ALTFN;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_OPENDRAIN;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_PULLUP;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_FAST;
	handlerI2CSCL.GPIO_PinConfig.GPIO_PinAltFunMode		= AF4;

	GPIO_Config(&handlerI2CSCL);

	// Configuramos los pines para el I2C SDA
	handlerI2CSDA.pGPIOx								= GPIOB;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinNumber			= PIN_3;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinMode			= GPIO_MODE_ALTFN;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinOPType			= GPIO_OTYPE_OPENDRAIN;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinPuPdControl	= GPIO_PUPDR_PULLUP;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinSpeed			= GPIO_OSPEED_FAST;
	handlerI2CSDA.GPIO_PinConfig.GPIO_PinAltFunMode		= AF9;

	GPIO_Config(&handlerI2CSDA);

	handlerRTC.ptrI2Cx								= I2C2;
	handlerRTC.modeI2C								= I2C_MODE_FM;
	handlerRTC.slaveAddress							= 0b1101000;
	handlerRTC.mainClock							= MAIN_CLOCK_100_MHz_FOR_I2C;
	handlerRTC.maxI2C_FM							= I2C_MAX_RISE_TIME_FM_100MHz;
	handlerRTC.modeI2C_FM							= I2C_MODE_FM_SPEED_400KHz_100MHz;

	i2c_config(&handlerRTC);

}

//void parseCommands(char *ptrBufferReception) {
//	/* Lee la cadena de caracteres a la que apunta el "ptrBufferReception
//	 * y almacena en tres elementos diferentes: un string llamado "cmd",
//	 * y tres integer llamados "firstParameter", "secondParameter" y "thirdParameter"
//	 * De esta forma podemos introducir informacion al micro desde el puerto
//	 */
//	sscanf(ptrBufferReception, "%s %u %u %u %s", cmd, &firstParameter,
//			&secondParameter, &thirdParameter, userMsg);
//	if (strcmp(cmd, "help") == 0) {
//			writeMsg(&handlerCommTerminal, "Help Menu CMDsunsigned int thirdParameter = 10000;: \n");
//			writeMsg(&handlerCommTerminal, "1)  help     --> Print this menu \n");
//			writeMsg(&handlerCommTerminal, "\n");
//			writeMsg(&handlerCommTerminal, "3)  rtctime  --> Configurar la hora  #1 #2 #3 \n");
//			writeMsg(&handlerCommTerminal, "    El primer parametro es la hora \n");
//			writeMsg(&handlerCommTerminal, "    El segundo parametro son los minutos \n");
//			writeMsg(&handlerCommTerminal, "    El tercer parametro son los segundos \n");
//			writeMsg(&handlerCommTerminal, "\n");
//			writeMsg(&handlerCommTerminal, "5)  actualtime --> Hora configurada \n");
//			writeMsg(&handlerCommTerminal, "\n");
//	} else if (strcmp(cmd, "rtctime") == 0) {
//		writeMsg(&handlerCommTerminal, "CMD: rtctime = #Hora #Minutos #Segundos \n");
//		if (firstParameter >= 0 && firstParameter < 24 && secondParameter >= 0
//				&& secondParameter < 60 && thirdParameter >= 0
//				&& thirdParameter < 60) {
////			handlerRTC.hour = firstParameter;
////			handlerRTC.minutes = secondParameter;
////			handlerRTC.seconds = thirdParameter;
////			//config_RTC(&handlerRTC);
//			sprintf(bufferData, "Hora Configurada = %.2u:%.2u:%.2u \n",
//					firstParameter, secondParameter, thirdParameter);
//			writeMsg(&handlerCommTerminal, bufferData);
//			minutero();
//		} else {
//			writeMsg(&handlerCommTerminal, "Hora no valida\n");
//		}
//	} else if (strcmp(cmd, "actualtime") == 0) {
//		writeMsg(&handlerCommTerminal, "CMD: actualhour = Hora configurada");
//		printTime(bufferTime);
//		writeMsg(&handlerCommTerminal, bufferTime);
//	}
//}

/* Callbacks de los Timers */
void BasicTimer2_Callback(void) {
	GPIOxTooglePin(&handlerBlinkyPin);
}

/* Callbacks de las interrupciones */
void usart2Rx_Callback(void) {
	rxData = getRxData();
}


void BasicTimer3_Callback(void) {
	tim++;
	if(tim==2){
		tomadedatos=1;
		tim=0;
		//colorled++;
	}
	if(colorled==6){
		colorled=0;
	}
}
//
//void minutero(void){
//	reloj = getTime();
//	hour[0]=reloj[0];
//	hour[1]=reloj[1];
//	hour[2]=reloj[2];
//	if(hour[1]<5){
//		turnoff();
//		delay_ms(100);
//		itis(colorled);
//		delay_ms(4);
//	}else if(hour[1]>=5 && hour[1]<10){
//		turnoff();
//		delay_ms(1);
//		itis(colorled);
//		delay_ms(4);
//		fivemin(colorled);
//		delay_ms(4);
//		past(colorled);
//		delay_ms(4);
//	} else if(hour[1]>=10 && hour[1]<15){
//		itis(colorled);
//		delay_ms(4);
//		tenmin(colorled);
//		delay_ms(4);
//		past(colorled);
//		delay_ms(4);
//	} else if(hour[1]>=15 && hour[1]<20){
//		itis(colorled);
//		delay_ms(4);
//		quarter(colorled);
//		delay_ms(4);
//		past(colorled);
//		delay_ms(4);
//	} else if(hour[1]>=20 && hour[1]<25){
//		itis(colorled);
//		delay_ms(4);
//		twentymin(colorled);
//		delay_ms(4);
//		past(colorled);
//		delay_ms(4);
//	} else if(hour[1]>=25 && hour[1]<30){
//		itis(colorled);
//		delay_ms(4);
//		twentymin(colorled);
//		delay_ms(4);
//		fivemin(colorled);
//		delay_ms(4);
//		past(colorled);
//		delay_ms(4);
//	} else if(hour[1]>=30 && hour[1]<35){
//		itis(colorled);
//		delay_ms(4);
//		half(colorled);
//		delay_ms(4);
//		past(colorled);
//		delay_ms(4);
//	} else if(hour[1]>=35 && hour[1]<40){
//		itis(colorled);
//		delay_ms(4);
//		twentymin(colorled);
//		delay_ms(4);
//		fivemin(colorled);
//		delay_ms(4);
//		to(colorled);
//		delay_ms(4);
//	} else if(hour[1]>=40 && hour[1]<45){
//		itis(colorled);
//		delay_ms(4);
//		twentymin(colorled);
//		delay_ms(4);
//		to(colorled);
//		delay_ms(4);
//    } else if(hour[1]>=45 && hour[1]<50){
//		itis(colorled);
//		delay_ms(4);
//		quarter(colorled);
//		delay_ms(4);
//		to(colorled);
//		delay_ms(4);
//	}else if(hour[1]>=50 && hour[1]<55){
//		itis(colorled);
//		delay_ms(4);
//		tenmin(colorled);
//		delay_ms(4);
//		to(colorled);
//		delay_ms(4);
//	}else if(hour[1]>=55 && hour[1]<=59){
//		itis(colorled);
//		delay_ms(4);
//		fivemin(colorled);
//		delay_ms(4);
//		to(colorled);
//		delay_ms(4);
//	}
//	if(hour[1]<35){
//		parametro=hour[0];
//		manecillahora(parametro);
//	}else if (hour[1]>=35){
//		parametro=hour[0]+1;
//		manecillahora(parametro);
//	}
//}
//
//
//void manecillahora(uint16_t horaconf){
//	switch (horaconf){
//	case 1:
//		one(colorled);
//		break;
//	case 2:
//		two(colorled);
//		break;
//	case 3:
//		three(colorled);
//		break;
//	case 4:
//		four(colorled);
//		break;
//	case 5:
//		five(colorled);
//		break;
//	case 6:
//		six(colorled);
//		break;
//	case 7:
//		seven(colorled);
//		break;
//	case 8:
//		eight(colorled);
//		break;
//	case 9:
//		nine(colorled);
//		break;
//	case 10:
//		ten(colorled);
//		break;
//	case 11:
//		eleven(colorled);
//		break;
//	case 12:
//		twelve(colorled);
//		break;
//	}
//	delay_ms(4);
//	if(hour[1]<5){
//		oclock(colorled);
//	}
//
//}
//

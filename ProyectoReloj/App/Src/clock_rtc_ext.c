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
#include "PLLDriver.h"
#include "LedDriver.h"
#include "Rtc1307.h"
#include "lines.h"

/* Definicion de las macros */
#define PLL_100_CLOCK_CONFIGURED  2
#define PLL_100  1

/* Definicion de variables */
// Definicion de handler de los pines del encoder
GPIO_Handler_t handlerPinC4 = {0}; //Switch
GPIO_Handler_t handlerPinA11 = {0}; //CLK
GPIO_Handler_t handlerPinB12 = {0}; //DT
GPIO_Handler_t  handlerPinTrans = {0};

// Definicion de los contadores
uint32_t counterExtiSwitch=0;
uint8_t counterExtiGiro=0;
uint8_t UnOrDec=0;
int32_t snakeCounter=0;
int32_t counter=0;
uint32_t counter1 =0;
uint32_t counter2 =0;


// Handler pin del Blinky simple
GPIO_Handler_t handlerBlinkyPin = { 0 };
GPIO_Handler_t handlerPinLed = { 0 };

/* Configuración para el I2C - RTC DS1307 */
GPIO_Handler_t handlerI2CSDA =	{0};
GPIO_Handler_t handlerI2CSCL =	{0};
I2C_Handler_t  handlerRTC	 = {0};

// Definicion de los handler de los Exti
EXTI_Config_t handlerExtiGiro = {0};   // El que controlara la interrupcion del giro del encoder
EXTI_Config_t handlerExtiSwitch = {0}; // El que controlara el boton del encoder

/* Handler de los timers */
BasicTimer_Handler_t handlerBlinkyTimer = { 0 };
BasicTimer_Handler_t handlerMuestreo = { 0 };

/* Elementos para hacer la comunicacion serial */
GPIO_Handler_t handlerPinTX = { 0 };
GPIO_Handler_t handlerPinRX = { 0 };
USART_Handler_t handlerCommTerminal = { 0 };

/* Configuración para el RTC */
rtc_t			dateAndTimeRTC = {0};
uint8_t 		dataRTC[7];
getTime_t		dataRTCtest = {0};

uint8_t tomadedatos=1;
uint8_t stringComplete = 0;
uint8_t rxData = 0;
uint16_t counterReception = 0;
uint8_t parametro=0;
uint8_t colorled=0;
uint8_t min=0;
uint8_t hora=0;

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
uint32_t tim=0;

// Definicion de las cabeceras de las funciones
void initSystem(void);
void minutero(void);
void manecillahora(uint16_t horaconf);
void parseCommands(char *ptrBufferReception);
void callback_extInt4(void);
void callback_extInt11(void);

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
	//itis(1);
//	turnoff();
//	delay_ms(1000);
//	itis(1);
//	delay_ms(1000);
	itisoneoclock(1);

	while (1) {
//		if(tomadedatos==1){
//			delay_ms(20);
//			tomadedatos=0;
//			minutero();
//		}
		// El caracter '@' nos indica que es el final de la cadena
			if (rxData != '\0') {
				bufferReception[counterReception] = rxData;
				counterReception++;

				// If the incoming character is a newline, set a flag
				// so the main loop can do something about it
				if (rxData == '#') {
					stringComplete = 1;

					//Agrego esta linea para crear el string con el null al final
					bufferReception[counterReception] = '\0';
					counterReception = 0;
				}
				//Para que no vuelva entrar. Solo cambia debido a la interrupcion
				rxData = '\0';
			}

			//Hacemos un analisis de la cadena de datos obtenida
			if (stringComplete) {
				parseCommands(bufferReception);
				stringComplete = 0;
			}

	} // Fin del while
	return (0);
} // Fin del main

void initSystem(void) {

	RCC->CR &= ~(RCC_CR_HSITRIM_Msk);
	RCC->CR |= (12 << RCC_CR_HSITRIM_Pos);

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

	/*Configuracion del Pin para el control de los leds */
	handlerPinTrans.pGPIOx                                     = GPIOA;
	handlerPinTrans.GPIO_PinConfig.GPIO_PinNumber              = PIN_7;
	handlerPinTrans.GPIO_PinConfig.GPIO_PinMode                = GPIO_MODE_OUT;
	handlerPinTrans.GPIO_PinConfig.GPIO_PinOPType              = GPIO_OTYPE_PUSHPULL;
	handlerPinTrans.GPIO_PinConfig.GPIO_PinSpeed               = GPIO_OSPEED_FAST;
	handlerPinTrans.GPIO_PinConfig.GPIO_PinPuPdControl         = GPIO_PUPDR_NOTHING;
	handlerPinTrans.GPIO_PinConfig.GPIO_PinAltFunMode          = AF0;

	/* Cargamos la configuracion del Pin en los registros*/
	GPIO_Config(&handlerPinTrans);

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

	// ---------------------------- PINES DEL ENCODER ----------------------------------------
	/* Configurar el pin como una entrada digital - Boton - SW */
	handlerPinC4.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOA
	handlerPinC4.GPIO_PinConfig.GPIO_PinNumber = PIN_4;                       // Escribimos el Numero del Pin
	handlerPinC4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;                  // Modo del pin de entrada
	handlerPinC4.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_PULLDOWN;     // No aplica

	// CLK
	handlerPinA11.pGPIOx = GPIOA;                                              // Deseamos trabajar con el puerto GPIOA
	handlerPinA11.GPIO_PinConfig.GPIO_PinNumber = PIN_11;                      // Escribimos el Numero del Pin
	handlerPinA11.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_IN;                // Modo del pin de salida
	handlerPinA11.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinA11.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_PULLDOWN;     // No aplica porque es de salida
	handlerPinA11.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinA11.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	// DT
	handlerPinB12.pGPIOx = GPIOB;                                              // Deseamos trabajar con el puerto GPIOB
	handlerPinB12.GPIO_PinConfig.GPIO_PinNumber = PIN_12;                      // Escribimos el Numero del Pin
	handlerPinB12.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_IN;                // Modo del pin de salida
	handlerPinB12.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinB12.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_PULLDOWN;     // No aplica porque es de salida
	handlerPinB12.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinB12.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	// Cargamos la configuracion de los pines del encoder
	GPIO_Config(&handlerPinC4);
	GPIO_Config(&handlerPinA11);
	GPIO_Config(&handlerPinB12);

	// ---------------------------- INTERRUPCIONES EXTI ----------------------------------------
	/* Configuracion del exti del boton del encoder */
	// Cargando la configuracion en los registros del MCU
	handlerExtiSwitch.pGPIOHandler = &handlerPinC4;
	handlerExtiSwitch.edgeType = EXTERNAL_INTERRUPT_RISING_EDGE;
	extInt_Config(&handlerExtiSwitch);

	/* Configuracion del exti del giro del encoder */
	handlerExtiGiro.pGPIOHandler = &handlerPinA11;
	handlerExtiGiro.edgeType = EXTERNAL_INTERRUPT_FALLING_EDGE;
	extInt_Config(&handlerExtiGiro);

}

void parseCommands(char *ptrBufferReception) {

	/* Lee la cadena de caracteres a la que apunta el "ptrBufferReception
	 * y almacena en tres elementos diferentes: un string llamado "cmd",
	 * y tres integer llamados "firstParameter", "secondParameter" y "thirdParameter"
	 * De esta forma podemos introducir informacion al micro desde el puerto
	 */
	sscanf(ptrBufferReception, "%s %u %u %u %s", cmd, &firstParameter,
			&secondParameter, &thirdParameter, userMsg);
	if (strcmp(cmd, "help") == 0) {
			writeMsg(&handlerCommTerminal, "Help Menu CMDsunsigned int thirdParameter = 10000;: \n");
			writeMsg(&handlerCommTerminal, "1)  help     --> Print this menu \n");
			writeMsg(&handlerCommTerminal, "\n");
			writeMsg(&handlerCommTerminal, "3)  rtctime  --> Configurar la hora  #1 #2 #3 \n");
			writeMsg(&handlerCommTerminal, "    El primer parametro es la hora \n");
			writeMsg(&handlerCommTerminal, "    El segundo parametro son los minutos \n");
			writeMsg(&handlerCommTerminal, "    El tercer parametro son los segundos \n");
			writeMsg(&handlerCommTerminal, "\n");
			writeMsg(&handlerCommTerminal, "5)  actualtime --> Hora configurada \n");
			writeMsg(&handlerCommTerminal, "\n");
	} else if (strcmp(cmd, "rtctime") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: rtctime = #Hora #Minutos #Segundos \n");
		if (firstParameter >= 0 && firstParameter < 24 && secondParameter >= 0
				&& secondParameter < 60 && thirdParameter >= 0
				&& thirdParameter < 60) {
			RTC_init(&handlerRTC);
			dateAndTimeRTC.seconds 	= thirdParameter;
			dateAndTimeRTC.minutes 	= secondParameter;
			dateAndTimeRTC.hour 	= firstParameter;
			RTC_SetDateTime(&handlerRTC, &dateAndTimeRTC);
			sprintf(bufferData, "Hora Configurada = %.2u:%.2u:%.2u \n",
					firstParameter, secondParameter, thirdParameter);
			writeMsg(&handlerCommTerminal, bufferData);
			minutero();
		} else {
			writeMsg(&handlerCommTerminal, "Hora no valida\n");
		}
	} else if (strcmp(cmd, "actualtime") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: actualhour = Hora configurada ");
		uint8_t second = RTC_readByte(&handlerRTC,0x00);
		uint8_t minute = RTC_readByte(&handlerRTC,0x01);
		uint8_t hour = RTC_readByte(&handlerRTC,0x02);
		sprintf(bufferData, "%.2d:%.2d:%.2d \n", (int) hour, (int) minute, (int) second);
		writeMsg(&handlerCommTerminal, bufferData);
	}
}

/* Callbacks de los Timers */
void BasicTimer2_Callback(void) {
	GPIOxTooglePin(&handlerBlinkyPin);
}

/* Callbacks de las interrupciones */
void usart2Rx_Callback(void) {
	rxData = getRxData();
}

/* Funciones de los EXTI */
// Funcion del boton del encoder
void callback_extInt4(void){
	if (counterExtiSwitch){
		counterExtiSwitch=0;
	} else {
		counterExtiSwitch=1;
	}
}

//// Funcion del giro del encoder
void callback_extInt11(void){
	counterExtiGiro = GPIO_ReadPin(&handlerPinB12); // Estado del Pin que controla el giro
	if(counterExtiGiro){
		colorled++; // Ciclo descendente
	}
	else{
		colorled--; // Ciclo ascendente
	}
	if(colorled>5){
		colorled=0;
	} else if(colorled<1){
		colorled=5;
	}
	tomadedatos=1;
}


void BasicTimer3_Callback(void) {
	tim++;
	counter++;
	if(tim==10){
		tomadedatos=1;
		tim=0;
	}
	if(counter==30){
		colorled++;
		if(colorled>5){
			colorled=0;
		}
	}
}

void minutero(void){
	min  = RTC_readByte(&handlerRTC,0x01);
	hora = RTC_readByte(&handlerRTC,0x02);
	if(min<5){
		GPIO_WritePin(&handlerPinTrans, 1);
		delay_ms(1000);
		GPIO_WritePin(&handlerPinTrans, 0);
		delay_ms(100);
		itis(colorled);
		delay_ms(4);
	}else if(min>=5 && min<10){
		itis(colorled);
		delay_ms(4);
		fivemin(colorled);
		delay_ms(4);
		past(colorled);
		delay_ms(4);
	} else if(min>=10 && min<15){
		turnoff();
		delay_ms(4);
		turnoff();
		delay_ms(4);
		itis(colorled);
		delay_ms(4);
		tenmin(colorled);
		delay_ms(4);
		past(colorled);
		delay_ms(4);
	} else if(min>=15 && min<20){
		turnoff();
		delay_ms(4);
		turnoff();
		delay_ms(4);
		itis(colorled);
		delay_ms(4);
		quarter(colorled);
		delay_ms(4);
		past(colorled);
		delay_ms(4);
	} else if(min>=20 && min<25){
		turnoff();
		delay_ms(4);
		turnoff();
		delay_ms(4);
		itis(colorled);
		delay_ms(4);
		twentymin(colorled);
		delay_ms(4);
		past(colorled);
		delay_ms(4);
	} else if(min>=25 && min<30){
		turnoff();
		delay_ms(4);
		turnoff();
		delay_ms(4);
		itis(colorled);
		delay_ms(4);
		twentymin(colorled);
		delay_ms(4);
		fivemin(colorled);
		delay_ms(4);
		past(colorled);
		delay_ms(4);
	} else if(min>=30 && min<35){
		turnoff();
		delay_ms(4);
		turnoff();
		delay_ms(4);
		itis(colorled);
		delay_ms(4);
		half(colorled);
		delay_ms(4);
		past(colorled);
		delay_ms(4);
	} else if(min>=35 && min<40){
		turnoff();
		delay_ms(4);
		turnoff();
		delay_ms(4);
		itis(colorled);
		delay_ms(4);
		twentymin(colorled);
		delay_ms(4);
		fivemin(colorled);
		delay_ms(4);
		to(colorled);
		delay_ms(4);
	} else if(min>=40 && min<45){
		turnoff();
		delay_ms(4);
		turnoff();
		delay_ms(4);
		itis(colorled);
		delay_ms(4);
		twentymin(colorled);
		delay_ms(4);
		to(colorled);
		delay_ms(4);
    } else if(min>=45 && min<50){
		turnoff();
		delay_ms(4);
		turnoff();
		delay_ms(4);
		itis(colorled);
		delay_ms(4);
		quarter(colorled);
		delay_ms(4);
		to(colorled);
		delay_ms(4);
	}else if(min>=50 && min<55){
		turnoff();
		delay_ms(4);
		turnoff();
		delay_ms(4);
		itis(colorled);
		delay_ms(4);
		tenmin(colorled);
		delay_ms(4);
		to(colorled);
		delay_ms(4);
	}else if(min>=55 && min<=59){
		turnoff();
		delay_ms(4);
		turnoff();
		delay_ms(4);
		itis(colorled);
		delay_ms(4);
		fivemin(colorled);
		delay_ms(4);
		to(colorled);
		delay_ms(4);
	}
	if(min<35){
		parametro=hora;
		manecillahora(parametro);
	}else if (min>=35){
		parametro=hora+1;
		if (parametro==13){
			parametro=1;
		}
		manecillahora(parametro);
	}
}


void manecillahora(uint16_t horaconf){
	switch (horaconf){
	case 1:
		one(colorled);
		break;
	case 2:
		two(colorled);
		break;
	case 3:
		three(colorled);
		break;
	case 4:
		four(colorled);
		break;
	case 5:
		five(colorled);
		break;
	case 6:
		six(colorled);
		break;
	case 7:
		seven(colorled);
		break;
	case 8:
		eight(colorled);
		break;
	case 9:
		nine(colorled);
		break;
	case 10:
		ten(colorled);
		break;
	case 11:
		eleven(colorled);
		break;
	case 12:
		twelve(colorled);
		break;
	case 13:
		one(colorled);
		break;
	case 14:
		two(colorled);
		break;
	case 15:
		three(colorled);
		break;
	case 16:
		four(colorled);
		break;
	case 17:
		five(colorled);
		break;
	case 18:
		six(colorled);
		break;
	case 19:
		seven(colorled);
		break;
	case 20:
		eight(colorled);
		break;
	case 21:
		nine(colorled);
		break;
	case 22:
		ten(colorled);
		break;
	case 23:
		eleven(colorled);
		break;
	case 0:
		twelve(colorled);
		break;
	}
	delay_ms(4);
	if(min<5){
		oclock(colorled);
	}

}


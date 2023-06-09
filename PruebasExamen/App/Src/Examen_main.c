/**
 * **************************************************************************************************
 * @file     : Examen_main.c
 * @author   : Maria Jose Uribe Henao
 * @brief    : PRUEBAS EXAMEN - TALLER V
 * **************************************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stm32f4xx.h>

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

/* Definicion de las macros */
#define PLL_100_CLOCK_CONFIGURED  2
#define PLL_100  1
// Registros del Acelerometro ADXL 345
#define ACCEL_ADDRESS          	 0x1D
#define ACCEL_XOUT_L             50     //DATAX0
#define ACCEL_XOUT_H             51     //DATAX1
#define ACCEL_YOUT_L             52     //DATAYO
#define ACCEL_YOUT_H             53     //DATAY1
#define ACCEL_ZOUT_L             54     //DATAZ0
#define ACCEL_ZOUT_H             55     //DATAZ1
#define BW_RATE                  44     //Output Data Rate
#define POWER_CTL                45
#define WHO_AM_I                 0      //DEVID

/* Definicion de variables */

/* Elementos para hacer la comunicacion serial */
GPIO_Handler_t handlerPinTX = {0};
GPIO_Handler_t handlerPinRX = {0};
USART_Handler_t handlerCommTerminal = {0};

// Handler del Blinky simple
GPIO_Handler_t handlerBlinkyPin = {0};

// Handler pin del MCO
GPIO_Handler_t handlerPinMCO = {0};

/* Handler del RTC */
RTC_t handlerRTC = {0};

/* Handler de los timers */
BasicTimer_Handler_t handlerBlinkyTimer = {0};
BasicTimer_Handler_t handlerMuestreo = {0};

// Variables para el acelerometro
uint8_t AccelX_low =0;
uint8_t AccelX_high=0;
int16_t AccelX=0;
uint8_t AccelY_low=0 ;
uint8_t AccelY_high=0;
int16_t AccelY=0;
uint8_t AccelZ_low=0;
uint8_t AccelZ_high=0;
int16_t AccelZ=0;

/*Configuracion para el I2C */
GPIO_Handler_t handlerI2cSDA = {0};
GPIO_Handler_t handlerI2cSCL = {0};
I2C_Handler_t handlerAccelerometer = {0};

/* Handler para las señales por PWM */
GPIO_Handler_t handlerPinPwmChannel1 = {0};
PWM_Handler_t handlerSignalPwm1 = {0};
uint16_t duttyValue1 = 10;

/* Contadores y banderas */
uint8_t  rxData = 0;
uint8_t  i2cBuffer ={0};
uint32_t interrupcion=0;
uint8_t  bandera=0;
uint8_t  counterLastLine;
uint16_t counterReception=0;
uint8_t  counterADC =0;
uint16_t numADC =0;
uint8_t  adcArrayOn =0;

/* Configuracion ADC */
ADC_Config_t adcConfig1 = {0};
uint16_t adcDataSingle;
uint8_t stringComplete = 0;

/* Arreglos */
uint32_t datosADC[2][256]={0};
uint16_t adcData[2] = {0};
char bufferData[64]= "Accel ADXL-345";
float datosAccel[3][2000];

/* Configuracion de comandos por terminal serial*/
char bufferReception[64];
char userMsg[64];
char cmd[64];
unsigned int firstParameter =0;
unsigned int secondParameter =0;

// Definicion de las cabeceras de las funciones
void initSystem(void);
void guardarDato(void);
void parseCommands(char *ptrBufferReception);
void selectMCOparam(uint16_t param);
void selectMCOpresc(uint16_t prescaler);

int main (void){
	// Activamos el coprocesador matematico FPU
	SCB->CPACR |= (0xF << 20);
	//Inicio del sistemaS
	initSystem();
	//Frecuencia del micro a 80MHz
	configPLL(PLL_100);
	// Se configura el systick a 80MHz
	config_SysTick_ms(PLL_100_CLOCK_CONFIGURED);
	//Imprimir un mensaje de inicio
	writeMsg(&handlerCommTerminal, "Examen - Taller V \n"
			"Accel ADXL-345 \n"
			"Frecuencia del microcontrolador: 100 MHz \n");

	while(1){
		// El caracter '@' nos indica que es el final de la cadena
		if(rxData != '\0'){
			bufferReception[counterReception] = rxData;
			counterReception++;

			// If the incoming character is a newline, set a flag
			// so the main loop can do something about it
			if(rxData == '@'){
				stringComplete = 1;

				//Agrego esta linea para crear el string con el null al final
				bufferReception[counterReception] = '\0';
				counterReception = 0;
			}
			//Para que no vuelva entrar. Solo cambia debido a la interrupcion
			rxData = '\0';
		}

		//Hacemos un analisis de la cadena de datos obtenida
		if (stringComplete){
			parseCommands(bufferReception);
			stringComplete = 0;
		}
	} // Fin del while
	return(0);
} // Fin del main


void initSystem(void){


	RCC->CR &= ~(RCC_CR_HSEON);
	RCC->CR &= ~(RCC_CR_HSEBYP);
	RCC->CR &= ~(RCC_CR_HSERDY);

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

	// ---------------------------- CONFIGURACION DE LOS TIMERS  ----------------------------------------
	/* Configuracion del TIM2 para que haga un blinky cada 250ms */
	handlerBlinkyTimer.ptrTIMx                               = TIM2;
	handlerBlinkyTimer.TIMx_Config.TIMx_mode                 = BTIMER_MODE_UP;
	handlerBlinkyTimer.TIMx_Config.TIMx_speed                = BTIMER_SPEED_100Mhz_100us;
	handlerBlinkyTimer.TIMx_Config.TIMx_period               = 2500;
	handlerBlinkyTimer.TIMx_Config.TIMx_interruptEnable      = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerBlinkyTimer);

	/*Configuracion del Pin para ver la velocidad */
	handlerPinMCO.pGPIOx                                  = GPIOA;
	handlerPinMCO.GPIO_PinConfig.GPIO_PinNumber           = PIN_8;
	handlerPinMCO.GPIO_PinConfig.GPIO_PinMode             = GPIO_MODE_ALTFN;
	handlerPinMCO.GPIO_PinConfig.GPIO_PinOPType           = GPIO_OTYPE_PUSHPULL;
	handlerPinMCO.GPIO_PinConfig.GPIO_PinSpeed            = GPIO_OSPEED_FAST;
	handlerPinMCO.GPIO_PinConfig.GPIO_PinPuPdControl      = GPIO_PUPDR_NOTHING;
	handlerPinMCO.GPIO_PinConfig.GPIO_PinAltFunMode       = AF0;

	/* Cargamos la configuracion del Pin en los registros*/
	GPIO_Config(&handlerPinMCO);

	// ---------------------------- CONFIGURACION DE LA COMUNICACION SERIAL  ----------------------------------------
	handlerPinTX.pGPIOx                               = GPIOA;
	handlerPinTX.GPIO_PinConfig.GPIO_PinNumber        = PIN_11;
	handlerPinTX.GPIO_PinConfig.GPIO_PinMode          = GPIO_MODE_ALTFN;
	handlerPinTX.GPIO_PinConfig.GPIO_PinAltFunMode    = AF8;
	GPIO_Config(&handlerPinTX);

	handlerPinRX.pGPIOx                               = GPIOA;
	handlerPinRX.GPIO_PinConfig.GPIO_PinNumber        = PIN_12;
	handlerPinRX.GPIO_PinConfig.GPIO_PinMode          = GPIO_MODE_ALTFN;
	handlerPinRX.GPIO_PinConfig.GPIO_PinAltFunMode    = AF8;
	GPIO_Config(&handlerPinRX);

	handlerCommTerminal.ptrUSARTx                       = USART6;
	handlerCommTerminal.USART_Config.USART_frequency    = 100;
	handlerCommTerminal.USART_Config.USART_baudrate     = USART_BAUDRATE_115200;
	handlerCommTerminal.USART_Config.USART_datasize     = USART_DATASIZE_8BIT;
	handlerCommTerminal.USART_Config.USART_parity       = USART_PARITY_NONE;
	handlerCommTerminal.USART_Config.USART_stopbits     = USART_STOPBIT_1;
	handlerCommTerminal.USART_Config.USART_mode         = USART_MODE_RXTX;
	handlerCommTerminal.USART_Config.USART_enableIntRX  = USART_RX_INTERRUP_ENABLE;
	handlerCommTerminal.USART_Config.USART_enableIntTX  = USART_TX_INTERRUP_DISABLE;

	USART_Config(&handlerCommTerminal);

	handlerRTC.seconds                                  = 12;
	handlerRTC.minutes                                  = 34;
	handlerRTC.hour                                     = 6;
	handlerRTC.weekDay                                  = RTC_WEEKDAY_WEDNESDAY;
	handlerRTC.date                                     = 7;
	handlerRTC.month                                    = 6;
	handlerRTC.year                                     = 23;
	config_RTC(&handlerRTC);
	// ---------------------------- CONFIGURACION INICIAL DEL MCO  ----------------------------------------
	// Seleccionamos la senal HSI
	RCC -> CFGR &= ~RCC_CFGR_MCO1;
	RCC -> CFGR &= ~RCC_CFGR_MCO1PRE;

	// ---------------------------- CONFIGURACION DEL PWM  ------------------------------------------------
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
	handlerSignalPwm1.config.duttyCicle      = 5;
	handlerSignalPwm1.config.periodo         = 10;
	handlerSignalPwm1.config.prescaler       = 100;
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
void usart6Rx_Callback(void){
	rxData = getRxData();
}

void selectMCOparam(uint16_t param){
	if(param==0){
		// Seleccionamos la senal PLL
		RCC -> CFGR &= ~RCC_CFGR_MCO1;
		RCC -> CFGR |= RCC_CFGR_MCO1_0;
		RCC -> CFGR |= RCC_CFGR_MCO1_1;
	} else if (param==1){
		// Seleccionamos la senal HSI
		RCC -> CFGR &= ~RCC_CFGR_MCO1;
	} else if(param==2){
		// Seleccionamos la senal LSE
		RCC -> CFGR &= ~RCC_CFGR_MCO1;
		RCC -> CFGR |= RCC_CFGR_MCO1_0;
		RCC -> CFGR &= ~RCC_CFGR_MCO1_1;
	}
}

void selectMCOpresc(uint16_t prescaler){
	if (prescaler ==0){
		RCC -> CFGR &= ~RCC_CFGR_MCO1PRE;
	}
	if(prescaler ==2){
		// Utilizamos un prescaler para poder ver la senal en el osciloscopio
		RCC -> CFGR &= ~RCC_CFGR_MCO1PRE;
		RCC -> CFGR |= RCC_CFGR_MCO1PRE_2;
	}
	else if(prescaler ==3){
		// Utilizamos un prescaler para poder ver la senal en el osciloscopio
		RCC -> CFGR |= RCC_CFGR_MCO1PRE_0;
		RCC -> CFGR &= ~RCC_CFGR_MCO1PRE_1;
		RCC -> CFGR |= RCC_CFGR_MCO1PRE_2;
	}
	else if(prescaler ==4){
		// Utilizamos un prescaler para poder ver la senal en el osciloscopio
		RCC -> CFGR &= ~RCC_CFGR_MCO1PRE_0;
		RCC -> CFGR |= RCC_CFGR_MCO1PRE_1;
		RCC -> CFGR |= RCC_CFGR_MCO1PRE_2;
	}
	else if(prescaler ==5){
		// Utilizamos un prescaler para poder ver la senal en el osciloscopio
		RCC -> CFGR |= RCC_CFGR_MCO1PRE_0;
		RCC -> CFGR |= RCC_CFGR_MCO1PRE_1;
		RCC -> CFGR |= RCC_CFGR_MCO1PRE_2;
	}

}

void parseCommands(char *ptrBufferReception){

	/* Lee la cadena de caracteres a la que apunta el "ptrBufferReception
	 * y almacena en tres elementos diferentes: un string llamado "cmd",
	 * y dos integer llamados "firstParameter" y "secondParameter"
	 * De esta forma podemos introducir informacion al micro desde el puerto
	 */
	sscanf(ptrBufferReception, "%s %u %u %s", cmd, &firstParameter, &secondParameter, userMsg);
	if (strcmp(cmd, "help") == 0){
		writeMsg(&handlerCommTerminal, "Help Menu CMDs: \n");
		writeMsg(&handlerCommTerminal, "1)  help -> Print this menu \n");
		writeMsg(&handlerCommTerminal, "2)  mcoparam -> Escribir un valor de 0,1 o 2 \n"
				"A los que corresponden: PLL(0), HSI(1), LSE(2)  \n");
		writeMsg(&handlerCommTerminal, "3)  mcopres -> Escribir un valor de 0,2,3,4 o 5 \n"
				"El PLL como minimo debe tener un prescaler de 2 \n");
		writeMsg(&handlerCommTerminal, "4)  rtcsecon -> El primer parametro es los segundos \n");
		writeMsg(&handlerCommTerminal, "5)  rtchour -> Configurar la hora\n"
				"El primer parametro es la hora y el segundo los minutos\n");
		writeMsg(&handlerCommTerminal, "6)  rtcdate -> El primer parametro es el dia \n"
				"EL segundo parametro es el mes \n");
		writeMsg(&handlerCommTerminal, "7)  rtcyear -> El primer parametro \n");
		writeMsg(&handlerCommTerminal, "8)  adcvel: Velocidad de muestreo \n");
		writeMsg(&handlerCommTerminal, "9)  adcarray: Presentacion de los arreglos \n");
		writeMsg(&handlerCommTerminal, "10) acceldata: Captura de datos \n");
		writeMsg(&handlerCommTerminal, "11) accelfreq: Frecuencias \n");

	}
	else if (strcmp(cmd, "mcoparam") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: mcoparam pll(0)-hsi(1)-lse(2) \n");
		if(firstParameter != 0 || firstParameter != 1 ||  firstParameter != 2){
			sprintf(bufferData, "El parametro a medir es %u \n", firstParameter);
			writeMsg(&handlerCommTerminal, bufferData);
			writeMsg(&handlerCommTerminal, "Este es un numero o caracter no especificado\n"
					"Solo son validos los numeros 0, 1 o 2 \n");
		} else {
			sprintf(bufferData, "Parametro a medir = %u \n", firstParameter);
			writeMsg(&handlerCommTerminal, bufferData);
			selectMCOparam(firstParameter);
		}
	}
	else if (strcmp(cmd, "mcopres") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: mcopres 0-2-3-4-5\n "
				"Warning!! PLL minimum 2 \n");
		if(firstParameter != 0 || firstParameter != 2 ||  firstParameter != 3 ||
				firstParameter != 4 ||  firstParameter != 5 ){
			sprintf(bufferData, "El prescaler escogido es %u \n", firstParameter);
			writeMsg(&handlerCommTerminal, bufferData);
			writeMsg(&handlerCommTerminal, "Este es un numero o caracter no especificado\n"
					"Solo son validos los numeros 0, 2, 3, 4 o 5 \n");
		} else {
			sprintf(bufferData, "Prescaler = %u \n", firstParameter);
			writeMsg(&handlerCommTerminal, bufferData);
			selectMCOpresc(firstParameter);
		}
	}
	else if (strcmp(cmd, "rtcsecon") == 0) {
		writeMsg(&handlerCommTerminal, "");
		sprintf(bufferData, "Prescaler = %u \n", firstParameter);
		writeMsg(&handlerCommTerminal, bufferData);
	}
	else if (strcmp(cmd, "rtchour") == 0) {
		handlerRTC.hour                                     = firstParameter;
		handlerRTC.minutes                                  = secondParameter;
		config_RTC(&handlerRTC);
		sprintf(bufferData, "Hora Configurada = %u:%u \n", firstParameter, secondParameter);
		writeMsg(&handlerCommTerminal, bufferData);
	}
	else if (strcmp(cmd, "rtcdate") == 0) {
		writeMsg(&handlerCommTerminal, "");
		sprintf(bufferData, "Prescaler = %u \n", firstParameter);
		writeMsg(&handlerCommTerminal, bufferData);
	}
	else if (strcmp(cmd, "rtcyear") == 0) {
		writeMsg(&handlerCommTerminal, "");
		sprintf(bufferData, "Prescaler = %u \n", firstParameter);
		writeMsg(&handlerCommTerminal, bufferData);
	}
	else if (strcmp(cmd, "adcvel") == 0) {
		writeMsg(&handlerCommTerminal, "");
		sprintf(bufferData, "Prescaler = %u \n", firstParameter);
		writeMsg(&handlerCommTerminal, bufferData);
	}
	else if (strcmp(cmd, "adcarray") == 0) {
		adcArrayOn =1;
		writeMsg(&handlerCommTerminal, "ADC\n");
		while (adcArrayOn){
			__NOP();
		}
		if(adcArrayOn==0){
			for (int i=0; i<256; i++){
				sprintf(bufferData, "%u\t%u \n", (unsigned int )datosADC[0][i],(unsigned int )datosADC[1][i]);
				writeMsg(&handlerCommTerminal, bufferData);
			}
		}
	}
	else if (strcmp(cmd, "acceldata") == 0) {

	}
	else if (strcmp(cmd, "accelfreq") == 0) {

	}
	else {
		// Se imprime el mensaje "Wrong CMD" si la escritura no corresponde a los CMD implementados
		writeMsg(&handlerCommTerminal, "Wrong CMD \n");
	}
}

/* Callbacks de las interrupciones */
void usart6x_Callback(void){
	rxData = getRxData();
}

/* Callbacks de los Timers */
void BasicTimer2_Callback(void){
	GPIOxTooglePin(&handlerBlinkyPin);
}

/* Callback del ADC */
void adcComplete_Callback(void){
	if (adcArrayOn){
		datosADC[counterADC][numADC]= getADC();
		if(numADC==255){
			adcArrayOn=0;
			numADC=0;
		}
		counterADC++;
		if(counterADC==2){
			counterADC=0;
			numADC++;
		}
	}
}


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
GPIO_Handler_t handlerPinTX = { 0 };
GPIO_Handler_t handlerPinRX = { 0 };
USART_Handler_t handlerCommTerminal = { 0 };

// Handler pin del Blinky simple
GPIO_Handler_t handlerBlinkyPin = { 0 };

// Handler pin del MCO
GPIO_Handler_t handlerPinMCO = { 0 };

/* Handler del RTC */
RTC_t handlerRTC = { 0 };

/* Handler de los timers */
BasicTimer_Handler_t handlerBlinkyTimer = { 0 };
BasicTimer_Handler_t handlerMuestreo = { 0 };

// Variables para el acelerometro
uint8_t AccelX_low = 0;
uint8_t AccelX_high = 0;
int16_t AccelX = 0;
uint8_t AccelY_low = 0;
uint8_t AccelY_high = 0;
int16_t AccelY = 0;
uint8_t AccelZ_low = 0;
uint8_t AccelZ_high = 0;
int16_t AccelZ = 0;
uint16_t datoAccel[16] = { 0 };
bool muestreo = false;
uint8_t tomadedatos = 0;

float32_t stopTime = 1.0;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
arm_rfft_fast_instance_f32 config_Rfft_fast_f32;
arm_cfft_radix4_instance_f32 configRadix4_f32;
arm_status status = ARM_MATH_ARGUMENT_ERROR;
arm_status statusInitFFT = ARM_MATH_ARGUMENT_ERROR;
uint16_t fttSize = 128;

/*Configuracion para el I2C */
GPIO_Handler_t handlerI2cSDA = { 0 };
GPIO_Handler_t handlerI2cSCL = { 0 };
I2C_Handler_t handlerAccelerometer = { 0 };

/* Handler para las señales por PWM */
GPIO_Handler_t handlerPinPwmChannel1 = { 0 };
PWM_Handler_t handlerSignalPwm1 = { 0 };
uint16_t duttyValue1 = 10;

/* Contadores y banderas */
uint8_t rxData = 0;
uint8_t i2cBuffer = { 0 };
uint32_t interrupcion = 0;
uint8_t bandera = 0;
uint32_t counterAccel;
uint16_t counterReception = 0;
uint8_t counterADC = 0;
uint16_t numADC = 0;
uint8_t adcArrayOn = 0;

/* Configuracion ADC */
ADC_Config_t adcConfig1 = { 0 };
uint8_t stringComplete = 0;

/* Arreglos */
uint32_t datosADC[2][256] = { 0 };
uint16_t adcData[2] = { 0 };
char bufferData[64] = "Accel ADXL-345";
float datosAccel[3][256];
float transformedSignal[256];
uint8_t banderaComm = 0;

/* Configuracion de comandos por terminal serial*/
char bufferReception[64];
char userMsg[64];
char cmd[64];
char bufferDate[64];
char bufferTime[64];
unsigned int firstParameter = 10000;
unsigned int secondParameter = 10000;
unsigned int thirdParameter = 10000;

// Definicion de las cabeceras de las funciones
void initSystem(void);
void guardarDato(void);
void parseCommands(char *ptrBufferReception);
void selectMCOparam(uint16_t param);
void selectMCOpresc(uint16_t prescaler);
void limpiarParam(void);

int main(void) {
	// Activamos el coprocesador matematico FPU
	SCB->CPACR |= (0xF << 20);
	//Inicio del sistemaS
	initSystem();
	//Frecuencia del micro a 80MHz
	configPLL(PLL_100);
	// Se configura el systick a 80MHz
	config_SysTick_ms(PLL_100_CLOCK_CONFIGURED);
	delay_ms(15);
	//Imprimir un mensaje de inicio
	writeMsg(&handlerCommTerminal, "Examen - Taller V \n"
			"Accel ADXL-345 \n"
			"Frecuencia del microcontrolador: 100 MHz \n");
	i2c_writeSingleRegister(&handlerAccelerometer, POWER_CTL, 0x08);
	delay_ms(1);
	//Muestreo a 3200Hz
	i2c_writeSingleRegister(&handlerAccelerometer, BW_RATE, 0b1100);
	delay_ms(1);
	while (1) {

		if (tomadedatos) {
			tomadedatos = 0;
			AccelX_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_XOUT_L);
			AccelX_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_XOUT_H);
			AccelX = AccelX_high << 8 | AccelX_low;
			AccelY_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_YOUT_L);
			AccelY_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_YOUT_H);
			AccelY = AccelY_high << 8 | AccelY_low;
			AccelZ_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_ZOUT_L);
			AccelZ_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_ZOUT_H);
			AccelZ = AccelZ_high << 8 | AccelZ_low;

			if (banderaComm) {
				datosAccel[0][counterAccel] = AccelX;
				datosAccel[1][counterAccel] = AccelY;
				datosAccel[2][counterAccel] = AccelZ;
				counterAccel++;
				if (counterAccel > 255) {
					banderaComm = 0;
					counterAccel = 0;
					for (int i = 0; i < 256; i++) {
						sprintf(bufferData, "n=%d x=%4.2f y=%4.2f z=%4.2f\n", i,
								datosAccel[0][i] * 9.8 / 256.0f,
								datosAccel[1][i] * 9.8 / 256.0f,
								datosAccel[2][i] * 9.8 / 256.0f);
						writeMsg(&handlerCommTerminal, bufferData);
					}
					//Inicialización FFT
					statusInitFFT = arm_rfft_fast_init_f32(
							&config_Rfft_fast_f32, fttSize);

					if (statusInitFFT == ARM_MATH_SUCCESS) {
						//Imprimir mensaje de exito
						sprintf(bufferData, "Datos adquiridos \n");
						writeMsg(&handlerCommTerminal, bufferData);
					}
				}
			}
		}

		// El caracter '@' nos indica que es el final de la cadena
		if (rxData != '\0') {
			bufferReception[counterReception] = rxData;
			counterReception++;

			// If the incoming character is a newline, set a flag
			// so the main loop can do something about it
			if (rxData == 10) {
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

	// Se apaga el reloj HSE para utilizar el pin H1
	RCC->CR &= ~(RCC_CR_HSEON);

	// ----------------------------BLINKY SIMPLE ----------------------------------------
	/* Configuracion del LED - PH1 - Blinky Simple */
	handlerBlinkyPin.pGPIOx                             = GPIOH;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinNumber      = PIN_1;
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

	/* Configuracion del TIM3 para un muestreo con una Freq de 1KHz  */
	handlerMuestreo.ptrTIMx                               = TIM3;
	handlerMuestreo.TIMx_Config.TIMx_mode                 = BTIMER_MODE_UP;
	handlerMuestreo.TIMx_Config.TIMx_speed                = BTIMER_SPEED_100Mhz_100us;
	handlerMuestreo.TIMx_Config.TIMx_period               = 50;
	handlerMuestreo.TIMx_Config.TIMx_interruptEnable      = 1;

	/* Cargando la configuracion del TIM3 en los registros */
	BasicTimer_Config(&handlerMuestreo);

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

	// ---------------------------- CONFIGURACION PINES DEL I2C  ----------------------------------------
	/* Pines del acelerometro */
	handlerI2cSCL.pGPIOx                                      = GPIOB;
	handlerI2cSCL.GPIO_PinConfig.GPIO_PinNumber               = PIN_8;
	handlerI2cSCL.GPIO_PinConfig.GPIO_PinMode                 = GPIO_MODE_ALTFN;
	handlerI2cSCL.GPIO_PinConfig.GPIO_PinOPType               = GPIO_OTYPE_OPENDRAIN;
	handlerI2cSCL.GPIO_PinConfig.GPIO_PinSpeed                = GPIO_OSPEED_FAST;
	handlerI2cSCL.GPIO_PinConfig.GPIO_PinPuPdControl          = GPIO_PUPDR_PULLUP;
	handlerI2cSCL.GPIO_PinConfig.GPIO_PinAltFunMode           = AF4;
	GPIO_Config(&handlerI2cSCL);

	handlerI2cSDA.pGPIOx                                      = GPIOB;
	handlerI2cSDA.GPIO_PinConfig.GPIO_PinNumber               = PIN_9;
	handlerI2cSDA.GPIO_PinConfig.GPIO_PinMode                 = GPIO_MODE_ALTFN;
	handlerI2cSDA.GPIO_PinConfig.GPIO_PinOPType               = GPIO_OTYPE_OPENDRAIN;
	handlerI2cSDA.GPIO_PinConfig.GPIO_PinSpeed                = GPIO_OSPEED_FAST;
	handlerI2cSDA.GPIO_PinConfig.GPIO_PinPuPdControl          = GPIO_PUPDR_PULLUP;
	handlerI2cSDA.GPIO_PinConfig.GPIO_PinAltFunMode           = AF4;
	GPIO_Config(&handlerI2cSDA);

	// ---------------------------- CONFIGURACION DEL ACELEROMETRO  ----------------------------------------
	handlerAccelerometer.ptrI2Cx                            = I2C1;
	handlerAccelerometer.modeI2C                            = I2C_MODE_FM;
	handlerAccelerometer.slaveAddress                       = ACCEL_ADDRESS;
	handlerAccelerometer.mainClock							= MAIN_CLOCK_80_MHz_FOR_I2C;
	handlerAccelerometer.maxI2C_FM							= I2C_MAX_RISE_TIME_FM_80MHz;
	handlerAccelerometer.modeI2C_FM							= I2C_MODE_FM_SPEED_400KHz_80MHz;

	i2c_config(&handlerAccelerometer);

	// ---------------------------- CONFIGURACION INICIAL DEL RTC ----------------------------------------
	handlerRTC.seconds                                  = 12;
	handlerRTC.minutes                                  = 34;
	handlerRTC.hour                                     = 6;
	handlerRTC.weekDay                                  = RTC_WEEKDAY_WEDNESDAY;
	handlerRTC.date                                     = 7;
	handlerRTC.month                                    = 6;
	handlerRTC.year                                     = 23;
	config_RTC(&handlerRTC);

	// ---------------------------- CONFIGURACION INICIAL DEL MCO  ----------------------------------------
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

	// Seleccionamos la senal HSI
	RCC->CFGR &= ~RCC_CFGR_MCO1;
	RCC->CFGR &= ~RCC_CFGR_MCO1PRE;

	// ---------------------------- CONFIGURACION DEL PWM  ------------------------------------------------
//	handlerPinPwmChannel1.pGPIOx                                = GPIOB;
//	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinNumber         = PIN_9;
//	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinMode           = GPIO_MODE_ALTFN;
//	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinOPType         = GPIO_OTYPE_PUSHPULL;
//	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinSpeed          = GPIO_OSPEED_FAST;
//	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinPuPdControl    = GPIO_PUPDR_NOTHING;
//	handlerPinPwmChannel1.GPIO_PinConfig.GPIO_PinAltFunMode     = AF2;
//	/* Cargamos la configuracion en los registros del MCU */
//	GPIO_Config(&handlerPinPwmChannel1);

	/* Configuracion del TIM4 para que genere la signal PWM*/
	handlerSignalPwm1.ptrTIMx                = TIM4;
	handlerSignalPwm1.config.channel         = PWM_CHANNEL_4;
	handlerSignalPwm1.config.duttyCicle      = 5;
	handlerSignalPwm1.config.periodo         = 10;
	handlerSignalPwm1.config.prescaler       = 100;
	/* Cargamos la configuracion en los registros del MCU */
	pwm_Config(&handlerSignalPwm1);
	enableOutput(&handlerSignalPwm1);
	startPwmSignal(&handlerSignalPwm1);

	// ---------------------------- CONFIGURACION CANALES ADC ----------------------------------------
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
void usart6Rx_Callback(void) {
	rxData = getRxData();
}

void selectMCOparam(uint16_t param) {
	if (param == 0) {
		// Seleccionamos la senal PLL
		RCC->CFGR &= ~RCC_CFGR_MCO1;
		RCC->CFGR |= RCC_CFGR_MCO1_0;
		RCC->CFGR |= RCC_CFGR_MCO1_1;
	} else if (param == 1) {
		// Seleccionamos la senal HSI
		RCC->CFGR &= ~RCC_CFGR_MCO1;
	} else if (param == 2) {
		// Seleccionamos la senal LSE
		RCC->CFGR &= ~RCC_CFGR_MCO1;
		RCC->CFGR |= RCC_CFGR_MCO1_0;
	}
}

void selectMCOpresc(uint16_t prescaler) {
	if (prescaler == 1) {
		RCC->CFGR &= ~RCC_CFGR_MCO1PRE;
	}
	if (prescaler == 2) {
		// Utilizamos un prescaler para poder ver la senal en el osciloscopio
		RCC->CFGR &= ~RCC_CFGR_MCO1PRE;
		RCC->CFGR |= RCC_CFGR_MCO1PRE_2;
	} else if (prescaler == 3) {
		// Utilizamos un prescaler para poder ver la senal en el osciloscopio
		RCC->CFGR |= RCC_CFGR_MCO1PRE_0;
		RCC->CFGR &= ~RCC_CFGR_MCO1PRE_1;
		RCC->CFGR |= RCC_CFGR_MCO1PRE_2;
	} else if (prescaler == 4) {
		// Utilizamos un prescaler para poder ver la senal en el osciloscopio
		RCC->CFGR &= ~RCC_CFGR_MCO1PRE_0;
		RCC->CFGR |= RCC_CFGR_MCO1PRE_1;
		RCC->CFGR |= RCC_CFGR_MCO1PRE_2;
	} else if (prescaler == 5) {
		// Utilizamos un prescaler para poder ver la senal en el osciloscopio
		RCC->CFGR |= RCC_CFGR_MCO1PRE_0;
		RCC->CFGR |= RCC_CFGR_MCO1PRE_1;
		RCC->CFGR |= RCC_CFGR_MCO1PRE_2;
	}

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
		writeMsg(&handlerCommTerminal, "Help Menu CMDs: \n");
		writeMsg(&handlerCommTerminal, "1)  help     --> Print this menu \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"2)  hsitrim  --> Configurar la sintonizacion \n");
		writeMsg(&handlerCommTerminal, "		Un unico parametro entre 0 y 32 \n");
		writeMsg(&handlerCommTerminal, "		Parametro por defecto = 16 \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"3)  mcoparam --> Escribir un unico valor entre 0,1 o 2 \n");
		writeMsg(&handlerCommTerminal,
				"A los que corresponden: PLL(0), HSI(1), LSE(2)  \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"4)  mcopres  --> Escribir un unico valor entre 0,2,3,4 o 5 \n");
		writeMsg(&handlerCommTerminal, "    Warning !!! \n");
		writeMsg(&handlerCommTerminal,
				"    El PLL como minimo debe tener un prescaler de 2 para poder visualizarlo en el osciloscopio \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"5)  rtcdate --> Configurar la fecha #1 #2 #3 \n");
		writeMsg(&handlerCommTerminal, "    El primer parametro es el dia \n");
		writeMsg(&handlerCommTerminal, "    El segundo parametro es el mes \n");
		writeMsg(&handlerCommTerminal, "    El tercer parametro es el año \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"6)  rtctime  --> Configurar la hora  #1 #2 #3 \n");
		writeMsg(&handlerCommTerminal, "    El primer parametro es la hora \n");
		writeMsg(&handlerCommTerminal,
				"    El segundo parametro son los minutos \n");
		writeMsg(&handlerCommTerminal,
				"    El tercer parametro son los segundos \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"7)  actualdate --> Fecha configurada\n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"8)  actualtime --> Hora configurada \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"9)  adcvel     --> Velocidad de muestreo \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"10)  adcarray  --> Presentacion de los arreglos de dos señales ADC \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"11) acceldata  --> Captura de datos \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal, "12) accelfreq  --> Frecuencias \n");
		writeMsg(&handlerCommTerminal, "\n");
		writeMsg(&handlerCommTerminal,
				"LOS VALORES POR DEFECTO DE LOS TRES NUMEROS ES 10000 \n");
		writeMsg(&handlerCommTerminal,
				"Si se desea hacer una actualizacion se debe escribir explicitamente el numero que se desea \n");
	} else if (strcmp(cmd, "hsitrim") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: hsitrim \n");
		if (firstParameter > 0 && firstParameter < 32) {
			RCC->CR &= ~(RCC_CR_HSITRIM_Msk);
			RCC->CR |= (firstParameter << RCC_CR_HSITRIM_Pos);
			sprintf(bufferData, "Sintonizado a: %u \n", firstParameter);
			writeMsg(&handlerCommTerminal, bufferData);
		} else {
			writeMsg(&handlerCommTerminal, "Valor a sintonizar no valido \n");
		}
		limpiarParam();
	} else if (strcmp(cmd, "mcoparam") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: mcoparam pll(0)-hsi(1)-lse(2) \n");
		if (firstParameter == 0 || firstParameter == 1 || firstParameter == 2) {
			sprintf(bufferData, "Parametro a medir = %u \n", firstParameter);
			writeMsg(&handlerCommTerminal, bufferData);
			selectMCOparam(firstParameter);
		} else {
			sprintf(bufferData, "El parametro a medir es %u \n",
					firstParameter);
			writeMsg(&handlerCommTerminal, bufferData);
			writeMsg(&handlerCommTerminal,
					"Este es un numero o caracter no especificado\n"
							"Solo son validos los numeros 0, 1 o 2 \n");
		}
		limpiarParam();
	} else if (strcmp(cmd, "mcopres") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: mcopres 1-2-3-4-5\n "
				"Warning!! PLL minimum 2 \n");
		if (firstParameter == 1 || firstParameter == 2 || firstParameter == 3
				|| firstParameter == 4 || firstParameter == 5) {
			sprintf(bufferData, "Prescaler = %u \n", firstParameter);
			writeMsg(&handlerCommTerminal, bufferData);
			selectMCOpresc(firstParameter);
		} else {
			sprintf(bufferData, "El prescaler escogido es %u \n",
					firstParameter);
			writeMsg(&handlerCommTerminal, bufferData);
			writeMsg(&handlerCommTerminal,
					"Este es un numero o caracter no especificado\n"
							"Solo son validos los numeros 0, 2, 3, 4 o 5 \n");
		}
		limpiarParam();
	} else if (strcmp(cmd, "rtcdate") == 0) {
		if (firstParameter > 0 && firstParameter < 32 && secondParameter > 0
				&& secondParameter < 13 && thirdParameter >= 0
				&& thirdParameter < 100) {
			writeMsg(&handlerCommTerminal, "CMD: rtcdate = #Dia #Mes #Año\n");
			handlerRTC.date = firstParameter;
			handlerRTC.month = secondParameter;
			handlerRTC.year = thirdParameter;
			config_RTC(&handlerRTC);
			sprintf(bufferData, "Fecha Configurada = %.2u/%.2u/%.2u \n",
					firstParameter, secondParameter, thirdParameter);
			writeMsg(&handlerCommTerminal, bufferData);
		} else {
			writeMsg(&handlerCommTerminal, "Fecha no valida\n");
		}
		limpiarParam();
	} else if (strcmp(cmd, "rtctime") == 0) {
		if (firstParameter >= 0 && firstParameter < 24 && secondParameter >= 0
				&& secondParameter < 60 && thirdParameter >= 0
				&& thirdParameter < 60) {
			handlerRTC.hour = firstParameter;
			handlerRTC.minutes = secondParameter;
			handlerRTC.seconds = thirdParameter;
			config_RTC(&handlerRTC);
			sprintf(bufferData, "Hora Configurada = %.2u:%.2u:%.2u \n",
					firstParameter, secondParameter, thirdParameter);
			writeMsg(&handlerCommTerminal, bufferData);
		} else {
			writeMsg(&handlerCommTerminal, "Hora no valida\n");
		}
		limpiarParam();
	} else if (strcmp(cmd, "actualdate") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: actualdate = Fecha configurada");
		printDate(bufferTime);
		writeMsg(&handlerCommTerminal, bufferTime);
	} else if (strcmp(cmd, "actualtime") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: actualhour = Hora configurada");
		printTime(bufferTime);
		writeMsg(&handlerCommTerminal, bufferTime);
	} else if (strcmp(cmd, "adcvel") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: adcvel #Periodo");
		sprintf(bufferData, "Periodo de la señal PWM = %u \n", firstParameter);
		writeMsg(&handlerCommTerminal, bufferData);
		handlerSignalPwm1.config.periodo = firstParameter;
		pwm_Config(&handlerSignalPwm1);
		limpiarParam();
	} else if (strcmp(cmd, "adcarray") == 0) {
		adcArrayOn = 1;
		writeMsg(&handlerCommTerminal,
				"CMD: adcarray = Arreglos con datos de dos señales ADC \n");
		while (adcArrayOn) {
			__NOP();
		}
		if (adcArrayOn == 0) {
			for (int i = 0; i < 256; i++) {
				sprintf(bufferData, "%u\t%u \n", (unsigned int) datosADC[0][i],
						(unsigned int) datosADC[1][i]);
				writeMsg(&handlerCommTerminal, bufferData);
			}
		}
		limpiarParam();
	} else if (strcmp(cmd, "acceldata") == 0) {
		writeMsg(&handlerCommTerminal,
				"CMD: acceldata = Toma de datos del acelerometro \n");
		banderaComm = 1;
		limpiarParam();
	} else if (strcmp(cmd, "accelfreq") == 0) {
		writeMsg(&handlerCommTerminal,
				"CMD: accelfreq = Frecuencia hallada por FFT \n ");
		stopTime = 0.0;

		int j = 0;
		writeMsg(&handlerCommTerminal, "FFT \n");
		//Calcular la transformada de Fourier
		if (statusInitFFT == ARM_MATH_SUCCESS) {
			arm_rfft_fast_f32(&config_Rfft_fast_f32, datosAccel[2],
					transformedSignal, ifftFlag);
			arm_abs_f32(transformedSignal, datosAccel[2], fttSize);

			uint32_t indexMax = 0;
			float FTT_Max = datosAccel[2][1];
			for (int i = 1; i < fttSize; i++) {
				if (i % 2) {
					if (datosAccel[2][i] > FTT_Max) {
						FTT_Max = datosAccel[2][i];
						indexMax = j;
					}
					sprintf(bufferData, "%u ; %#.6f\n", j,
							2 * datosAccel[2][i]);
					writeMsg(&handlerCommTerminal, bufferData);
					j++;
				}
			}

//			sprintf(bufferData, "index %d ; result %f\n,", (int)indexMax, FTT_Max);
//			writeMsg(&usart1Handler, bufferData);

			float w = (indexMax / (0.005 * (fttSize)));
			sprintf(bufferData, "frecuency w %f Hz \n,", w);
			writeMsg(&handlerCommTerminal, bufferData);

		} else {
			writeMsg(&handlerCommTerminal, "FFT not initialized...");
		}
		limpiarParam();
	} else {
		// Se imprime el mensaje "Wrong CMD" si la escritura no corresponde a los CMD implementados
		writeMsg(&handlerCommTerminal, "Wrong CMD \n");
		limpiarParam();
	}
}

/* Callbacks de las interrupciones */
void usart6x_Callback(void) {
	rxData = getRxData();
}

/* Callbacks de los Timers */
void BasicTimer2_Callback(void) {
	GPIOxTooglePin(&handlerBlinkyPin);
}

void BasicTimer3_Callback(void) {
	muestreo = true;
	tomadedatos = 1;
}

/* Callback del ADC */
void adcComplete_Callback(void) {
	adcData[counterADC] = getADC();
	if (adcArrayOn) {
		datosADC[counterADC][numADC] = adcData[counterADC];
		if (numADC == 255) {
			adcArrayOn = 0;
			numADC = 0;
		}
		counterADC++;
		if (counterADC == 2) {
			counterADC = 0;
			numADC++;
		}
	}
}

/* Funcion para limpiar los parametros */
void limpiarParam(void) {
	firstParameter = 10000;
	secondParameter = 10000;
	secondParameter = 10000;
}


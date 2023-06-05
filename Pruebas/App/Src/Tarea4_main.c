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
GPIO_Handler_t handlerPinMCO = {0};
/* Elementos para hacer la comunicacion serial */
GPIO_Handler_t handlerPinTX = {0};
GPIO_Handler_t handlerPinRX = {0};
USART_Handler_t handlerCommTerminal = {0};

// Handler del Blinky simple
GPIO_Handler_t handlerBlinkyPin = {0};

/* Handler de los timers */
BasicTimer_Handler_t handlerBlinkyTimer = {0};
BasicTimer_Handler_t handlerMuestreo = {0};

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

/* Contadores y banderas */
uint8_t rxData = 0;
uint8_t i2cBuffer ={0};
uint32_t interrupcion=0;
uint8_t bandera=0;
uint8_t counterLastLine;
uint16_t counterReception=0;

/* Arreglos */
char bufferData[64]= "Accel ADXL-345";
float datosAccel[3][2000];
char bufferReception[64];
uint8_t stringComplete = 0;
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
	//Muestreo a 3200Hz
	i2c_writeSingleRegister(&handlerAccelerometer, BW_RATE , 0xF);
	//Reset inicial del acelerometro
	i2c_writeSingleRegister(&handlerAccelerometer, POWER_CTL , 0x2D);
	// Se configura el systick a 80MHz
	config_SysTick_ms(PLL_100_CLOCK_CONFIGURED);
	//Imprimir un mensaje de inicio
	writeMsg(&handlerCommTerminal, "Examen - Taller V \n"
			"Accel ADXL-345 \n"
			"Frecuencia del microcontrolador: 100 MHz \n");

	while(1){
		// Se llama la funcion para el muestreo constante


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

	/* Configuracion del TIM4 para un muestreo con una Freq de 1KHz  */
	handlerMuestreo.ptrTIMx                               = TIM4;
	handlerMuestreo.TIMx_Config.TIMx_mode                 = BTIMER_MODE_UP;
	handlerMuestreo.TIMx_Config.TIMx_speed                = BTIMER_SPEED_100Mhz_100us;
	handlerMuestreo.TIMx_Config.TIMx_period               = 50;
	handlerMuestreo.TIMx_Config.TIMx_interruptEnable      = 1;

	/* Cargando la configuracion del TIM4 en los registros */
	BasicTimer_Config(&handlerMuestreo);

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
	handlerCommTerminal.USART_Config.USART_baudrate     = USART_BAUDRATE_115200;
	handlerCommTerminal.USART_Config.USART_datasize     = USART_DATASIZE_8BIT;
	handlerCommTerminal.USART_Config.USART_parity       = USART_PARITY_NONE;
	handlerCommTerminal.USART_Config.USART_stopbits     = USART_STOPBIT_1;
	handlerCommTerminal.USART_Config.USART_mode         = USART_MODE_RXTX;
	handlerCommTerminal.USART_Config.USART_enableIntRX  = USART_RX_INTERRUP_ENABLE;
	handlerCommTerminal.USART_Config.USART_enableIntTX  = USART_TX_INTERRUP_DISABLE;
	handlerCommTerminal.USART_Config.USART_frequency    = 100;

	USART_Config(&handlerCommTerminal);

	// ---------------------------- CONFIGURACION DEL ACELEROMETRO  ----------------------------------------
	handlerAccelerometer.ptrI2Cx                            = I2C1;
	handlerAccelerometer.modeI2C                            = I2C_MODE_FM;
	handlerAccelerometer.slaveAddress                       = ACCEL_ADDRESS;
	handlerAccelerometer.mainClock							= MAIN_CLOCK_100_MHz_FOR_I2C;
	handlerAccelerometer.maxI2C_FM							= I2C_MAX_RISE_TIME_FM_100MHz;
	handlerAccelerometer.modeI2C_FM							= I2C_MODE_FM_SPEED_400KHz_100MHz;

	i2c_config(&handlerAccelerometer);

	// ---------------------------- CONFIGURACION INICIAL DEL MCO  ----------------------------------------
	// Seleccionamos la senal HSI
	RCC -> CFGR &= ~RCC_CFGR_MCO1;
	RCC -> CFGR &= ~RCC_CFGR_MCO1PRE;


}

/* Funcion para el muestreo inicial por 2 segundos */
void guardarDato(void){
	bandera=1;
	if(interrupcion<2000){
		AccelX_low =  i2c_readSingleRegister(&handlerAccelerometer, ACCEL_XOUT_L);
		AccelX_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_XOUT_H);
		AccelX = AccelX_high << 8 | AccelX_low;
		AccelY_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_YOUT_L);
		AccelY_high = i2c_readSingleRegister(&handlerAccelerometer,ACCEL_YOUT_H);
		AccelY = AccelY_high << 8 | AccelY_low;
		AccelZ_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_ZOUT_L);
		AccelZ_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_ZOUT_H);
		AccelZ = AccelZ_high << 8 | AccelZ_low;
	}
    datosAccel[0][interrupcion] =AccelX;
    datosAccel[1][interrupcion] =AccelY;
    datosAccel[2][interrupcion] =AccelZ;
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
		RCC -> CFGR &= ~RCC_CFGR_MCO1_0;
		RCC -> CFGR |= RCC_CFGR_MCO1_1;
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
		writeMsg(&handlerCommTerminal, "2)  mcoparam -> LSE(2), PLL(0), HSI(1) \n");
		writeMsg(&handlerCommTerminal, "3)  mcopres -> 0,2,3,4,5 \n");
		writeMsg(&handlerCommTerminal, "4)  RTC \n");
		writeMsg(&handlerCommTerminal, "5)  RTC \n");
		writeMsg(&handlerCommTerminal, "6)  RTC \n");
		writeMsg(&handlerCommTerminal, "7)  RTC \n");
		writeMsg(&handlerCommTerminal, "8)  Datos analogos: Velocidad de muestreo \n");
		writeMsg(&handlerCommTerminal, "9)  Datos analogos: Presentacion de los arreglos \n");
		writeMsg(&handlerCommTerminal, "10) Acelerometro: Captura de datos \n");
		writeMsg(&handlerCommTerminal, "11) Acelerometro: Frecuencias \n");

	}
	// El comando dummy sirve para entender como funciona la recepcion de numeros
	//enviados desde la consola
	else if (strcmp(cmd, "dummy") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: dummy \n");
		// Cambiando el formato para presentar el numero por el puerto serial
		sprintf(bufferData, "number A = %u \n", firstParameter);
		writeMsg(&handlerCommTerminal, bufferData);
		sprintf(bufferData, "number B = %u \n", secondParameter);
		writeMsg(&handlerCommTerminal, bufferData);
	}
	// El comando usermsg sirve para entender como funciona la recepcion de strings
	//enviados desde la consola
	else if (strcmp(cmd, "usermsg") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: usermsg \n");
		writeMsg(&handlerCommTerminal, userMsg);
		writeMsg(&handlerCommTerminal, "\n");
	}
	else if (strcmp(cmd, "mcoparam") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: mcoparam pll(0)-hsi(1)-lse(2) \n");
		sprintf(bufferData, " = %u \n", firstParameter);
		writeMsg(&handlerCommTerminal, bufferData);
		selectMCOparam(firstParameter);
	}
	else if (strcmp(cmd, "mcopres") == 0) {
		writeMsg(&handlerCommTerminal, "CMD: mcopres 0-2-3-4-5\n "
				"Warning!! PLL minimum 2 \n");
		sprintf(bufferData, "Prescaler = %u \n", firstParameter);
		writeMsg(&handlerCommTerminal, bufferData);
		selectMCOpresc(firstParameter);
	}
	else {
		// Se imprime el mensaje "Wrong CMD" si la escritura no corresponde a los CMD implementados
		writeMsg(&handlerCommTerminal, "Wrong CMD \n");
	}
}

/* Callbacks de los Timers */
void BasicTimer2_Callback(void){
	GPIOxTooglePin(&handlerBlinkyPin);
	counterLastLine++;
}

void BasicTimer4_Callback(void){
//	guardarDato();
	if (bandera){
		interrupcion++;
		if(interrupcion==2000){
			interrupcion=0;
		}
	}
}

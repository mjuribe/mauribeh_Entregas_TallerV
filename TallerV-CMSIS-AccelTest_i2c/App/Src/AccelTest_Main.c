/**
 * **************************************************************************************************
 * @file     : Maria Jose Uribe Henao
 * @author   : AccelTest_Main.c
 * @brief    : Ejemplo del uso de I2C
 * **************************************************************************************************
 */


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
//#include <stdlib.h>
//#include <string.h>
#include <math.h>
#include <stm32f4xx.h>

#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "ExtiDriver.h"
#include "USARTxDriver.h"
#include "SysTickDriver.h"
#include "I2CDriver.h"
#include "PwmDriver.h"
#include <math.h>
#include "PLLDriver.h"

#define PLL_80_CLOCK_CONFIGURED  3
#define PLL_80  0

/* Definicion de variables */

/* Elemento para hacer la comunicacion serial */
GPIO_Handler_t handlerPinTX ={0};
GPIO_Handler_t handlerPinRX ={0};

// Handler del Blinky simple
GPIO_Handler_t handlerBlinkyPin = {0};
BasicTimer_Handler_t handlerBlinkyTimer = {0};
BasicTimer_Handler_t handlerMuestreo = {0};

USART_Handler_t handlerCommTerminal={0};
//uint8_t usart2DataReceived=0;
uint8_t rxData = 0;

char bufferData[64]= "Accel MPU-6050 testing";

uint8_t systemTicks = 0;
uint8_t systemTicksStart = 0;
uint8_t systemTicksEnd = 0;

/*Configuracion para el I2C */
GPIO_Handler_t handlerI2cSDA = {0};
GPIO_Handler_t handlerI2cSCL = {0};
I2C_Handler_t handlerAccelerometer = {0};
uint8_t i2cBuffer ={0};
uint16_t interrupcion=0;
uint8_t bandera=0;

float datosAccel[2000];
float guardarDato(void);

#define ACCEL_ADDRESS          	 0x1D
#define ACCEL_XOUT_L             50     //DATAX0
#define ACCEL_XOUT_H             51     //DATAX1
#define ACCEL_YOUT_L             52     //DATAYO
#define ACCEL_YOUT_H             53     //DATAY1
#define ACCEL_ZOUT_L             54     //DATAZ0
#define ACCEL_ZOUT_H             55     //DATAZ1

#define BW_RATE                  44     //Data Rate

#define POWER_CTL                45
#define WHO_AM_I                 0      //DEVID

// Definicion de las cabeceras de las funciones
void initSystem(void);

int main (void){
	// Activamos el coprocesador matematico FPU
	SCB->CPACR |= (0xF << 20);

	//Inicio del sistema
	initSystem();
	//
	configPLL(PLL_80);
	//Muestreo a 1600Hz
	i2c_writeSingleRegister(&handlerAccelerometer, BW_RATE , 0xE);

	//Imprimir un mensaje de inicio
	writeMsg(&handlerCommTerminal, bufferData);

	while(1){

		//Hacemos un "eco" con el valor que nos llega por el serial
		if(rxData != '\0'){
			writeChar(&handlerCommTerminal, rxData);

			if(rxData == 'w'){
				sprintf(bufferData, "WHO_AM_I? (r)\n");
				writeMsg(&handlerCommTerminal, bufferData);

				i2cBuffer = i2c_readSingleRegister(&handlerAccelerometer, WHO_AM_I);
				sprintf(bufferData, "dataRead = 0x%x \n", (unsigned int) i2cBuffer);
				writeMsg(&handlerCommTerminal, bufferData);
				rxData = '\0';
			}
			else if (rxData == 'p'){
				sprintf(bufferData, "PWR_MGMT_1 state (r)\n");
				writeMsg(&handlerCommTerminal, bufferData);

				i2cBuffer = i2c_readSingleRegister(&handlerAccelerometer, POWER_CTL);
				sprintf(bufferData, "dataRead = 0x%x \n", (unsigned int) i2cBuffer);
				writeMsg(&handlerCommTerminal, bufferData);
				rxData = '\0';
			}
			else if (rxData == 'r'){
				sprintf(bufferData, "PWR_MGMT_1 reset (w)\n");
				writeMsg(&handlerCommTerminal, bufferData);

				i2c_writeSingleRegister(&handlerAccelerometer, POWER_CTL , 0x2D);
				rxData = '\0';
			}
			else if (rxData == 'x'){
				sprintf(bufferData, "Axis X data (r) \n");
				writeMsg(&handlerCommTerminal, bufferData);

				uint8_t AccelX_low =  i2c_readSingleRegister(&handlerAccelerometer, ACCEL_XOUT_L);
				uint8_t AccelX_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_XOUT_H);
				int16_t AccelX = AccelX_high << 8 | AccelX_low;
				sprintf(bufferData, "AccelX = %.2f \n", (float) (AccelX/256.f)*9.78);
				writeMsg(&handlerCommTerminal, bufferData);
				rxData = '\0';
			}
			else if(rxData == 'y'){
				sprintf(bufferData, "Axis Y data (r)\n");
				writeMsg(&handlerCommTerminal, bufferData);
				uint8_t AccelY_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_YOUT_L);
				uint8_t AccelY_high = i2c_readSingleRegister(&handlerAccelerometer,ACCEL_YOUT_H);
				int16_t AccelY = AccelY_high << 8 | AccelY_low;
				sprintf(bufferData, "AccelY = %.2f \n", (AccelY/256.f)*9.78);
				writeMsg(&handlerCommTerminal, bufferData);
				rxData = '\0';
			}
			else if(rxData == 'z'){
				sprintf(bufferData, "Axis Z data (r)\n");
				writeMsg(&handlerCommTerminal, bufferData);

				uint8_t AccelZ_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_ZOUT_L);
				uint8_t AccelZ_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_ZOUT_H);
				int16_t AccelZ = AccelZ_high << 8 | AccelZ_low;
				sprintf(bufferData, "AccelZ = %.2f \n",  (AccelZ/256.f)*9.78);
				writeMsg(&handlerCommTerminal, bufferData);
				rxData = '\0';
			} else if(rxData == 'm' ){
				bandera=1;
				while(interrupcion<2000){
					uint8_t AccelX_low =  i2c_readSingleRegister(&handlerAccelerometer, ACCEL_XOUT_L);
					uint8_t AccelX_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_XOUT_H);
					int16_t AccelX = AccelX_high << 8 | AccelX_low;
					sprintf(bufferData, "AccelX = %.2f \n", (float) (AccelX/256.f)*9.78);
					uint8_t AccelY_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_YOUT_L);
					uint8_t AccelY_high = i2c_readSingleRegister(&handlerAccelerometer,ACCEL_YOUT_H);
					int16_t AccelY = AccelY_high << 8 | AccelY_low;
					sprintf(bufferData, "AccelY = %.2f \n", (AccelY/256.f)*9.78);
					uint8_t AccelZ_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_ZOUT_L);
					uint8_t AccelZ_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_ZOUT_H);
					int16_t AccelZ = AccelZ_high << 8 | AccelZ_low;
					sprintf(bufferData, "AccelZ = %.2f \n",  (AccelZ/256.f)*9.78);
				}
				interrupcion=0;
				bandera=0;
			}
			else{
				rxData = '\0';
			}
		}

	}
	return(0);


}


void initSystem(void){

	// ----------------------------BLINKY SIMPLE ----------------------------------------
	/* Configuracion del LED2 - PA5 - Blinky Simple */
	handlerBlinkyPin.pGPIOx                             = GPIOA;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinNumber      = PIN_5;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinMode        = GPIO_MODE_OUT;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinOPType      = GPIO_OTYPE_PUSHPULL;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinSpeed       = GPIO_OSPEED_FAST;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;

	//Cargar la configuracion del LED2 en los registros
	GPIO_Config(&handlerBlinkyPin);
	GPIO_WritePin(&handlerBlinkyPin, SET);

	/* Configuracion del TIM2 para que haga un blinky cada 250ms */
	handlerBlinkyTimer.ptrTIMx                               = TIM2;
	handlerBlinkyTimer.TIMx_Config.TIMx_mode                 = BTIMER_MODE_UP;
	handlerBlinkyTimer.TIMx_Config.TIMx_speed                = BTIMER_SPEED_80Mhz_100us;
	handlerBlinkyTimer.TIMx_Config.TIMx_period               = 2500;
	handlerBlinkyTimer.TIMx_Config.TIMx_interruptEnable      = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerBlinkyTimer);

	/* Configuracion del TIM3 para un muestreo con una Freq de 1KHz  */
	handlerMuestreo.ptrTIMx                               = TIM4;
	handlerMuestreo.TIMx_Config.TIMx_mode                 = BTIMER_MODE_UP;
	handlerMuestreo.TIMx_Config.TIMx_speed                = BTIMER_SPEED_80Mhz_100us;
	handlerMuestreo.TIMx_Config.TIMx_period               = 10;
	handlerMuestreo.TIMx_Config.TIMx_interruptEnable      = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerMuestreo);

	/* Configuracion pie I2C */
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

	/* Configuracion de la comunicacion serial*/
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
	handlerCommTerminal.USART_Config.USART_frequency    = 80;

	USART_Config(&handlerCommTerminal);

	handlerAccelerometer.ptrI2Cx                            = I2C1;
	handlerAccelerometer.modeI2C                            = I2C_MODE_FM;
	handlerAccelerometer.slaveAddress                       = ACCEL_ADDRESS;
	handlerAccelerometer.mainClock							= MAIN_CLOCK_80_MHz_FOR_I2C;
	handlerAccelerometer.maxI2C_FM							= I2C_MAX_RISE_TIME_FM_80MHz;
	handlerAccelerometer.modeI2C_FM							= I2C_MODE_FM_SPEED_400KHz_80MHz;

	i2c_config(&handlerAccelerometer);
}


/* Interrupciones */
void usart6Rx_Callback(void){
	//Leemo el valor del registro DR, donde se encuentra almacenado el dato que llega
	// ESto además debe bajar la bandera de la interrupción
	rxData = getRxData();
}

void BasicTimer2_Callback(void){
	GPIOxTooglePin(&handlerBlinkyPin);
	//printMsg++;
//	sendMsg++;
}

void BasicTimer4_Callback(void){
	if (bandera){
		interrupcion++;
	}
	guardarDato();
}

float guardarDato(void){
	uint8_t AccelX_low =  i2c_readSingleRegister(&handlerAccelerometer, ACCEL_XOUT_L);
	uint8_t AccelX_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_XOUT_H);
	int16_t AccelX = AccelX_high << 8 | AccelX_low;
	sprintf(bufferData, "AccelX = %.2f \n", (float) (AccelX/256.f)*9.78);
	uint8_t AccelY_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_YOUT_L);
	uint8_t AccelY_high = i2c_readSingleRegister(&handlerAccelerometer,ACCEL_YOUT_H);
	int16_t AccelY = AccelY_high << 8 | AccelY_low;
	sprintf(bufferData, "AccelY = %.2f \n", (AccelY/256.f)*9.78);
	uint8_t AccelZ_low = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_ZOUT_L);
	uint8_t AccelZ_high = i2c_readSingleRegister(&handlerAccelerometer, ACCEL_ZOUT_H);
	int16_t AccelZ = AccelZ_high << 8 | AccelZ_low;
	sprintf(bufferData, "AccelZ = %.2f \n",  (AccelZ/256.f)*9.78);
	return 0;

}



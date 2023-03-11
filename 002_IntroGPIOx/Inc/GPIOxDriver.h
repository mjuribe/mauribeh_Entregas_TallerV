/*
 * GPIOxDriver.h
 *
 *  Created on: Mar 10, 2023
 *      Author: majo
 */

#ifndef INC_GPIOXDRIVER_H_
#define INC_GPIOXDRIVER_H_

//Incluyendo este archivo estamos incluyendo también el correspondiente al GPIOx
#include "stm32f411xx_hal.h"

typedef struct
{
	uint8_t GPIO_PinNumber;        //PIN con el que deseamos trabajar
	uint8_t GPIO_PinMode;          //Modo de la configuración: entrada, salida, análogo, f.a
	uint8_t GPIO_PinSpeed;         //Velocidad de respuesta del PIN (solo para digital)
	uint8_t GPIO_PinPuPdControl;   //Seleccionamos si deseamos una salida Pull-up, Pull-down o "libre"
	uint8_t GPIO_PinOPType;        //Trabaja de la mano con el anterior, selecciona salida PUPD o OpenDrain
	uint8_t GPIO_PinAltFunMode;    //Selecciona cual es la función alt.que se está configurando

}GPIO_PinConfig_t;

/* Esta es una estructura que contiene dos elementos:
 * -La dirección del puerto que se está utilizando (la referencia al puerto)
 * -La configuración específica del PIN que se está utilizando
 */
typedef struct
{
	GPIOx_RegDef_t    *pGPIOx; /*!< Direccion del puerto al que el PIN corresponde >*/
	GPIO_PinConfig_t  GPIO_PinConfig; /*!< Configuracion del PIN >*/

}GPIO_Handler_t;

/*Definicion de las cabeceras de las funciones del GPIOxDriver */
void GPIO_Config (GPIO_Handler_t *pGPIOHandler);
void GPIO_WritePin(GPIO_Handler_t *pPinHandler, uint8_t newState);
uint32_t GPIO_ReadPin(GPIO_Handler_t *pPinHandler);



#endif /* INC_GPIOXDRIVER_H_ */

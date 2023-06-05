/*
 * PLLDriver.h
 *
 *  Created on: May 20, 2023
 *      Author: majo
 */

#ifndef PLLDRIVER_H_
#define PLLDRIVER_H_

#include "stm32f4xx.h"

#define FREQUENCY_80_MHz	0
#define FREQUENCY_100_MHz	1

#define MCO1_PRESCALER_DIV_2	0b100
#define MCO1_PRESCALER_DIV_3	0b101
#define MCO1_PRESCALER_DIV_4	0b110
#define MCO1_PRESCALER_DIV_5	0b111

#define MCO1_HSI_CHANNEL	0b00
#define MCO1_LSE_CHANNEL	0b01
#define MCO1_HSE_CHANNEL	0b10
#define MCO1_PLL_CHANNEL	0b11

void configPLL(uint8_t frequency);
int getConfigPLL(void);

#endif /* PLLDRIVER_H_ */

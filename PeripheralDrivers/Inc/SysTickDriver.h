/*
 * SysTickDriver.h
 *
 *  Created on: May 1, 2023
 *      Author: mauribeh
 */

#ifndef SYSTICKDRIVER_H_
#define SYSTICKDRIVER_H_

#include <stm32f4xx.h>

#define SYSTICK_LOAD_VALUE_16MHz_1ms     16000   // Numero de ciclos en un milisegundo
#define SYSTICK_LOAD_VALUE_100MHz_1ms    100000  // Numero de ciclos en un milisegundo
#define SYSTICK_LOAD_VALUE_80MHz_1ms     80000   // Numero de ciclos en un milisegundo
#define SYSTICK_LOAD_VALUE_100MHz_50ns     5   // Numero de ciclos en un milisegundo

void config_SysTick_ms(uint8_t systemClock);
uint64_t getTicks_ms(void);
void delay_ms(uint32_t wait_time_ms);
void config_SysTick_50ns(void);
uint64_t getTicks_50ns(void);
void delay_50ns(uint32_t wait_time_100ns);

#endif /* SYSTICKDRIVER_H_ */

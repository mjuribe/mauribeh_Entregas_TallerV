/*
 * RtcDriver.h
 *
 *  Created on: Jun 4, 2023
 *      Author: majo
 */
#ifndef RTCDRIVER_H_
#define RTCDRIVER_H_

#include "stm32f4xx.h"
#include <stdio.h>

#define RTC_WEEKDAY_MONDAY		0b001
#define RTC_WEEKDAY_TUESDAY		0b010
#define RTC_WEEKDAY_WEDNESDAY	0b011
#define RTC_WEEKDAY_THURSDAY	0b100
#define RTC_WEEKDAY_FRIDAY		0b101
#define RTC_WEEKDAY_SATURDAY	0b110
#define RTC_WEEKDAY_SUNDAY		0b111

#define FORMAT_24H 	0
#define FORMAT_12H 	1

#define AM				0
#define PM				1
#define NA				2

typedef struct{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
	uint8_t format;
	uint8_t	am_pm;
}RTC_t;

// Función de configuración del RTC
void config_RTC(RTC_t *pRTC);
// Función para convertir de decimal a BCD
uint8_t decToBCD(int val);
// Función para convertir de BCD a decimal
int BCDToDec(uint8_t val);
uint8_t* getTime(void);
uint8_t* getDate(void);
void printDate(char *bufferDate);
void printTime(char *bufferTime);

#endif /* RTCDRIVER_H_ */





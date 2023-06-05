/*
 * RtcDriver.h
 *
 *  Created on: Jun 4, 2023
 *      Author: majo
 */

#ifndef RTCDRIVER_H_
#define RTCDRIVER_H_
#include "stm32f4xx.h"

typedef struct
{
	 uint8_t RTC_Hours   ;
	 uint8_t RTC_Minutes ;
	 uint8_t RTC_Seconds ;
	 uint8_t RTC_Year ;
	 uint8_t RTC_Month ;
	 uint8_t RTC_Day ;
	 uint32_t RTC_Time ;
	 uint32_t RTC_Date ;
	 uint32_t RTC_TimeFormat;
	 uint32_t RTC_WeekDay;
	 uint32_t RTC_ValueDay;
	 uint32_t RTC_TimeNotation;

}RTC_Config_t;

typedef struct
{
	RTC_TypeDef    *ptrRtcHandler; /*!< Direccion del puerto al que el PIN corresponde >*/
	RTC_Config_t   RTC_Config;

}RTC_Handler_t;

void RTC_Config(RTC_Handler_t *ptrRtcHandler);
uint8_t RTC_BcdToByte(uint16_t BCD_Value);
void *read_date(void);

#endif /* RTCDRIVER_H_ */

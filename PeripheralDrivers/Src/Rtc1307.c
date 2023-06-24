/*
 * Rtc1307.c
 *
 *  Created on: Jun 16, 2023
 *      Author: majo
 */

#include "Rtc1307.h"

// Funcion para inicializar el RTC. Escribimos en el Control Register para desactivar el SQW - Out
void RTC_init(I2C_Handler_t *ptrHandlerI2C){

	RTC_writeByte(ptrHandlerI2C,0x07,0b00000000);
	RTC_writeByte(ptrHandlerI2C,0x00,0b00000000);

}

// Función para definir el tiempo y la fecha
void RTC_SetDateTime(I2C_Handler_t *ptrHandlerI2C, rtc_t *rtc){

	i2c_startTransaction(ptrHandlerI2C);

	i2c_sendSlaveAddressRW(ptrHandlerI2C, ptrHandlerI2C->slaveAddress, I2C_WRITE_DATA);

	uint8_t memAddr = 0x00;

	i2c_sendMemoryAddress(ptrHandlerI2C,memAddr);

	i2c_sendDataByte(ptrHandlerI2C, decToBCD(rtc -> seconds));

	i2c_sendDataByte(ptrHandlerI2C, decToBCD(rtc -> minutes));

	i2c_sendDataByte(ptrHandlerI2C, decToBCD(rtc -> hour));

	i2c_sendDataByte(ptrHandlerI2C, decToBCD(rtc -> weekDay));

	i2c_sendDataByte(ptrHandlerI2C, decToBCD(rtc -> date));

	i2c_sendDataByte(ptrHandlerI2C, decToBCD(rtc -> month));

	i2c_sendDataByte(ptrHandlerI2C, decToBCD(rtc -> year));

	i2c_stopTransaction(ptrHandlerI2C);
}

// Función para leer todos los registros
void RTC_ReadDateTime(I2C_Handler_t *ptrHandlerI2C, getTime_t *ptrGetTime){

	i2c_startTransaction(ptrHandlerI2C);

	i2c_sendSlaveAddressRW(ptrHandlerI2C, ptrHandlerI2C->slaveAddress, I2C_WRITE_DATA);

	uint8_t memAddr = 0x00;

	i2c_sendMemoryAddress(ptrHandlerI2C,memAddr);

	i2c_stopTransaction(ptrHandlerI2C);

	i2c_startTransaction(ptrHandlerI2C);

	i2c_sendSlaveAddressRW(ptrHandlerI2C, ptrHandlerI2C->slaveAddress, I2C_READ_DATA);

	//int GetDateAndTime[7];

	ptrGetTime -> seconds 	= BCDToDec(i2c_readDataByte(ptrHandlerI2C));
	ptrGetTime -> minutes 	= BCDToDec(i2c_readDataByte(ptrHandlerI2C));
	ptrGetTime -> hour 		= BCDToDec(i2c_readDataByte(ptrHandlerI2C));
	ptrGetTime -> weekDay 	= BCDToDec(i2c_readDataByte(ptrHandlerI2C));
	ptrGetTime -> date 		= BCDToDec(i2c_readDataByte(ptrHandlerI2C));
	ptrGetTime -> month 	= BCDToDec(i2c_readDataByte(ptrHandlerI2C));
	ptrGetTime -> year 		= BCDToDec(i2c_readDataByte(ptrHandlerI2C));


//	*GetDateAndTime = i2c_readDataByte(ptrHandlerI2C);
//	GetDateAndTime++;
//	*GetDateAndTime = i2c_readDataByte(ptrHandlerI2C);
//	GetDateAndTime++;
//	*GetDateAndTime = i2c_readDataByte(ptrHandlerI2C);
//	GetDateAndTime++;
//	*GetDateAndTime = i2c_readDataByte(ptrHandlerI2C);
//	GetDateAndTime++;
//	*GetDateAndTime = i2c_readDataByte(ptrHandlerI2C);
//	GetDateAndTime++;
//	*GetDateAndTime = i2c_readDataByte(ptrHandlerI2C);
//	GetDateAndTime++;
//	*GetDateAndTime = i2c_readDataByte(ptrHandlerI2C);




//	GetDateAndTime[0] = BCDToDec(i2c_readDataByte(ptrHandlerI2C));
//
//	GetDateAndTime[1] = BCDToDec(i2c_readDataByte(ptrHandlerI2C));
//
//	GetDateAndTime[2] = BCDToDec(i2c_readDataByte(ptrHandlerI2C));
//
//	GetDateAndTime[3] = BCDToDec(i2c_readDataByte(ptrHandlerI2C));
//
//	GetDateAndTime[4] = BCDToDec(i2c_readDataByte(ptrHandlerI2C));
//
//	GetDateAndTime[5] = BCDToDec(i2c_readDataByte(ptrHandlerI2C));
//
//	GetDateAndTime[6] = BCDToDec(i2c_readDataByte(ptrHandlerI2C));

	i2c_sendNoACK(ptrHandlerI2C);

	i2c_stopTransaction(ptrHandlerI2C);

	//return *GetDateAndTime;
}


// Función para leer todos los registros
void RTC_ReadDateTimeFull(I2C_Handler_t *ptrHandlerI2C, uint8_t *GetDateAndTime){

	GetDateAndTime[0] = BCDToDec(RTC_readByte(ptrHandlerI2C, 0x00));

	GetDateAndTime[1] = BCDToDec(RTC_readByte(ptrHandlerI2C, 0x01));

	GetDateAndTime[2] = BCDToDec(RTC_readByte(ptrHandlerI2C, 0x02));

	GetDateAndTime[3] = BCDToDec(RTC_readByte(ptrHandlerI2C, 0x03));

	GetDateAndTime[4] = BCDToDec(RTC_readByte(ptrHandlerI2C, 0x04));

	GetDateAndTime[5] = BCDToDec(RTC_readByte(ptrHandlerI2C, 0x05));

	GetDateAndTime[6] = BCDToDec(RTC_readByte(ptrHandlerI2C, 0x06));
}

// Funciones para leer un Byte en el RTC
uint8_t RTC_readByte(I2C_Handler_t *ptrHandlerI2C, uint8_t memAddr){

	i2c_startTransaction(ptrHandlerI2C);

	i2c_sendSlaveAddressRW(ptrHandlerI2C,ptrHandlerI2C->slaveAddress, I2C_WRITE_DATA);

	i2c_sendMemoryAddress(ptrHandlerI2C,memAddr);

	i2c_stopTransaction(ptrHandlerI2C);

	i2c_startTransaction(ptrHandlerI2C);

	i2c_sendSlaveAddressRW(ptrHandlerI2C, ptrHandlerI2C->slaveAddress, I2C_READ_DATA);

	uint8_t dataI2C = i2c_readDataByte(ptrHandlerI2C);

	//i2c_sendNoACK(ptrHandlerI2C);

	i2c_stopTransaction(ptrHandlerI2C);

	return BCDToDec(dataI2C);

}

// Funciones para escribir un Byte en el RTC
void RTC_writeByte(I2C_Handler_t *ptrHandlerI2C, uint8_t memAddr, uint8_t dataToWrite){

	i2c_startTransaction(ptrHandlerI2C);

	i2c_sendSlaveAddressRW(ptrHandlerI2C,ptrHandlerI2C->slaveAddress, I2C_WRITE_DATA);

	i2c_sendMemoryAddress(ptrHandlerI2C,memAddr);

	i2c_sendDataByte(ptrHandlerI2C,dataToWrite);

	i2c_stopTransaction(ptrHandlerI2C);
}

// Función para convertir de numeros decimales a código BCD
uint8_t decToBCD(int val){
	return (uint8_t) ((val/10*16) + (val%10));
}

// Función para convertir de código BCD a numeros decimales

int BCDToDec(uint8_t val){
	return (int) ((val/16*10) + (val%16));
}


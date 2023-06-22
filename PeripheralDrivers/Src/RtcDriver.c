#include "RtcDriver.h"

void config_RTC(RTC_t *pRTC) {

	// Activamos la señal de reloj para el PWR
	// El PWR le proporciona energia al RTC de manera eficiente
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	// Desactivamos el modo Backup Protection
	PWR->CR |= PWR_CR_DBP;

	// Activamos el LSE (LOW SPEED EXTERNAL 32KHz)
	RCC->BDCR |= RCC_BDCR_LSEON;

	/* Esperamos hasta que el LSE este listo  */
	while (!(RCC->BDCR & RCC_BDCR_LSERDY)) {
		__NOP();
	}
	// Habilitamos la señal proveniente del LSE (LOW SPEED EXTERNAL 32KHz)
	RCC->BDCR &= ~RCC_BDCR_RTCSEL;
	RCC->BDCR |= RCC_BDCR_RTCSEL_0;

	//  Habilitamos el clock del RTC
	RCC->BDCR |= RCC_BDCR_RTCEN;

	/* Iniciamos rutina de inicialización */
	// Desactivamos el Write Protection register con la clave
	RTC->WPR = 0xCAU;
	RTC->WPR = 0x53U;

	/* Setiamos el bit INIT	en el ISR */
	RTC->ISR |= RTC_ISR_INIT;

	/* Ponemos en 1 el bit de INITF */
	while ((RTC->ISR & RTC_ISR_INITF) == 0) {
		__NOP();
	}

	/* Configuramos el preescaler */
	RTC->PRER |= RTC_PRER_PREDIV_A;
	RTC->PRER |= (0xFF << RTC_PRER_PREDIV_S_Pos);

	// Bypass the shadow registers
	RTC->CR |= RTC_CR_BYPSHAD;

	// Limpiamos registros
	RTC->TR = 0;
	RTC->DR = 0;

	/* Cargamos los valores del calendario (DR - Date Register) y de la hora (TR - Time Register)*/

	// Escogemos el modo de 24 horas
	RTC->CR &= ~(RTC_CR_FMT);
	RTC->TR &= ~(RTC_TR_PM);

	// Escribimos el dia
	RTC->DR |= (decToBCD(pRTC->date)) << RTC_DR_DU_Pos;

	// Escribimos el mes
	RTC->DR |= (decToBCD(pRTC->month)) << RTC_DR_MU_Pos;

	// Escribimos el año
	RTC->DR |= (decToBCD(pRTC->year)) << RTC_DR_YU_Pos;

	// Escribimos el día de la semana
	RTC->DR |= (pRTC->weekDay) << RTC_DR_WDU_Pos;

	// Ponemos formato de la hora
	if(pRTC->format == FORMAT_24H){
		RTC->CR &= ~RTC_CR_FMT;
	}
	else if(pRTC->format == FORMAT_12H){
		RTC->CR |= RTC_CR_FMT;
	}

	// Configuramos si la hora es AM, PM o ninguna
	if (pRTC->am_pm == PM){
		RTC->TR |= RTC_TR_PM;
	}
	else{
		RTC->TR &= ~RTC_TR_PM;
	}

	// Escribimos las horas todo funciones
	RTC->TR |= (decToBCD(pRTC->hour)) << RTC_TR_HU_Pos;

	// Escribimos los minutos
	RTC->TR |= (decToBCD(pRTC->minutes)) << RTC_TR_MNU_Pos;

	// Escribimos los segundos
	RTC->TR |= (decToBCD(pRTC->seconds)) << RTC_TR_SU_Pos;

	/* Salimos del modo de inicialización */
	RTC->ISR &= ~RTC_ISR_INIT;

	/* Activamos nuevamente el Write Protection */
	RTC->WPR = 0xFFU;

	RTC->CR &= ~RTC_CR_BYPSHAD;

}

// Función para convertir de numeros decimales a código BCD
uint8_t decToBCD(int val) {
	uint8_t variable = (uint8_t) ((val / 10 * 16) + (val % 10));
	return variable;
}

// Función para convertir de código BCD a numeros decimales
int BCDToDec(uint8_t val) {
	int variable = (int) ((val / 16 * 10) + (val % 16));
	return variable;
}

uint8_t time[4] = { 0 };
uint8_t date[4] = { 0 };

////Función para leer el tiempo
uint8_t* getTime(void) {
	uint8_t RTC_Hours = 0;
	uint8_t RTC_Minutes = 0;
	uint8_t RTC_Seconds = 0;
	uint8_t RTC_AmPm = 0;

	RTC_Hours = BCDToDec(((RTC->TR) >> RTC_TR_HU_Pos) & 0x3F); // 3F= 111111
	RTC_Minutes = BCDToDec(((RTC->TR) >> RTC_TR_MNU_Pos) & 0x7F); // 7F= 1111111
	RTC_Seconds = BCDToDec((RTC->TR) >> RTC_TR_SU_Pos & 0x7F);
	RTC_AmPm = ((RTC->TR >> RTC_TR_PM_Pos) & RTC_TR_PM_Msk);

	time[0] = RTC_Hours;
	time[1] = RTC_Minutes;
	time[2] = RTC_Seconds;
	time[3] = RTC_AmPm;

	return time;
}

uint8_t* getDate(void) {
//Función para leer la fecha

	uint8_t RTC_Year = 0;
	uint8_t RTC_Month = 0;
	uint8_t RTC_Day = 0;
	uint8_t RTC_Date = 0;

	RTC_Year = BCDToDec(((RTC->DR) >> RTC_DR_YU_Pos) & 0xFF);
	RTC_Month = BCDToDec(((RTC->DR) >> RTC_DR_MU_Pos) & 0x1F);
	RTC_Date = BCDToDec((RTC->DR) >> RTC_DR_DU_Pos & 0x3F);
	RTC_Day = (RTC->DR >> RTC_DR_WDU_Pos) & RTC_DR_WDU_Msk;

	date[0] = RTC_Date;
	date[1] = RTC_Month;
	date[2] = RTC_Year;
	date[3] = RTC_Day;
//
	return date;
}
/* Arreglos fecha y hora RTC */
uint8_t fecha[4];
uint8_t hora[4];

void printDate(char *bufferDate){
	getDate();
	fecha[0]=date[0];
	fecha[1]=date[1];
	fecha[2]=date[2];
	fecha[3]=date[3];
	sprintf(bufferDate, " %.2u/%.2u/%.2u ", fecha[0], fecha[1],fecha[2] );
}

void printTime(char *bufferTime){
	getTime();
	hora[0]=time[0];
	hora[1]=time[1];
	hora[2]=time[2];
	hora[4]=time[4];
	sprintf(bufferTime, " %.2u:%.2u:%.2u\n", hora[0], hora[1],hora[2]);
}

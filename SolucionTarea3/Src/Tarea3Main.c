#include <stdint.h>
#include <stm32f4xx.h>
#include "GPIOxDriver.h"
#include "BasicTimer.h"
#include "ExtiDriver.h"
#include <math.h>

/* Definicion de los elementos del sistema */
// Handler del Blinky simple
GPIO_Handler_t handlerBlinkyPin = {0};

// Handler de los timers
BasicTimer_Handler_t handlerBlinkyTimer = {0};
BasicTimer_Handler_t handlerTimer3 = {0};

// Definicion de handler de los pines de los segmentos de lo leds
GPIO_Handler_t handlerPinC9 = {0}; //a
GPIO_Handler_t handlerPinC8 = {0}; //b
GPIO_Handler_t handlerPinB8 = {0}; //c
GPIO_Handler_t handlerPinC6 = {0}; //d
GPIO_Handler_t handlerPinB9 = {0}; //e
GPIO_Handler_t handlerPinC5 = {0}; //f
GPIO_Handler_t handlerPinA6 = {0}; //g

// Definicion de handler de los pines de control de 1 o 2 del display
GPIO_Handler_t handlerPinC10 = {0}; //1
GPIO_Handler_t handlerPinC12 = {0}; //2

// Definicion de handler de los pines del encoder
GPIO_Handler_t handlerPinC4 = {0}; //Switch
GPIO_Handler_t handlerPinA11 = {0}; //CLK
GPIO_Handler_t handlerPinB12 = {0}; //DT

// Definicion de los contadores
uint32_t counterExtiSwitch=0;
uint32_t counterExtiGiro=0;
uint8_t UnOrDec=0;
int32_t snakeCounter=0;
int32_t counter=0;
uint32_t counter1 =0;
uint32_t counter2 =0;

// Definicion de los handler de los Exti
EXTI_Config_t handlerExtiGiro = {0};
EXTI_Config_t handlerExtiSwitch = {0};

int Digit[10][7] =
   {
     { 0,0,0,0,0,0,1},    // 0
     { 1,0,0,1,1,1,1},    // 1
     { 0,0,1,0,0,1,0},    // 2
     { 0,0,0,0,1,1,0},    // 3
     { 1,0,0,1,1,0,0},    // 4
     { 0,1,0,0,1,0,0},    // 5
     { 0,1,0,0,0,0,0},    // 6
     { 0,0,0,1,1,1,1},    // 7
     { 0,0,0,0,0,0,0},    // 8
     { 0,0,0,0,1,0,0},    // 9
   };

int Culebrita[12][9] =
   {
     { 0,1,1,1,1,1,1,1,0 },    // a
     { 0,1,1,1,1,1,1,0,1 },    // a
     { 1,1,1,1,1,0,1,0,1 },    // f
     { 1,1,1,1,0,1,1,0,1 },    // e
	 { 1,1,1,0,1,1,1,0,1 },    // d
	 { 1,1,1,1,0,1,1,1,0 },    // e
     { 1,1,1,1,1,0,1,1,0 },    // f
     { 1,0,1,1,1,1,1,0,1 },    // b
     { 1,1,0,1,1,1,1,0,1 },    // c
     { 1,1,1,0,1,1,1,1,0 },    // d
     { 1,1,0,1,1,1,1,1,0 },    // c
     { 1,0,1,1,1,1,1,1,0 },    // b

   };


/* Prototipos de las funciones */
void callback_extInt4(void);
void callback_extInt11(void);
void init_Hardware(void);

int main (void){
	// Inicializacion de todos los elementos del sistema */
	init_Hardware();

	while(1){

		switch(counter){
		case(100):
			counter = 0;   // Conteo ascendente
			break;
		case(-1):
			counter = 99;  // Conteo descendente
			break;
		default:
			break;
		}

		switch(snakeCounter){
		case(12):
			snakeCounter = 0;   // Conteo ascendente
			break;
		case(-1):
			snakeCounter = 11;  // Conteo descendente
			break;
		default:
			break;
		}
	}
}



void init_Hardware(void){

	// ----------------------------BLINKY SIMPLE ----------------------------------------
	/* Configuracion del LED2 - PA5 - Blinky Simple */
	handlerBlinkyPin.pGPIOx = GPIOA;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinNumber = PIN_5;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_FAST;
	handlerBlinkyPin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;

	//Cargar la configuracion del LED2 en los registros
	GPIO_Config(&handlerBlinkyPin);
	GPIO_WritePin(&handlerBlinkyPin, SET);

	// ----------------------------PINES PARA LOS SIETE SEGMENTOS ----------------------------------------
	//Definimos el handler para los Pines correspondientes a los siete segmentos
	handlerPinC9.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC9.GPIO_PinConfig.GPIO_PinNumber = PIN_9;                       // Escribimos el Numero del Pin
	handlerPinC9.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC9.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC9.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC9.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC9.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	handlerPinC8.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC8.GPIO_PinConfig.GPIO_PinNumber = PIN_8;                       // Escribimos el Numero del Pin
	handlerPinC8.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC8.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC8.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC8.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC8.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	handlerPinB8.pGPIOx = GPIOB;                                              // Deseamos trabajar con el puerto GPIOB
	handlerPinB8.GPIO_PinConfig.GPIO_PinNumber = PIN_8;                       // Escribimos el Numero del Pin
	handlerPinB8.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinB8.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinB8.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinB8.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinB8.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	handlerPinC6.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC6.GPIO_PinConfig.GPIO_PinNumber = PIN_6;                       // Escribimos el Numero del Pin
	handlerPinC6.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC6.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC6.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC6.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	handlerPinB9.pGPIOx = GPIOB;                                              // Deseamos trabajar con el puerto GPIOB
	handlerPinB9.GPIO_PinConfig.GPIO_PinNumber = PIN_9;                       // Escribimos el Numero del Pin
	handlerPinB9.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinB9.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinB9.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinB9.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinB9.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	handlerPinC5.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC5.GPIO_PinConfig.GPIO_PinNumber = PIN_5;                       // Escribimos el Numero del Pin
	handlerPinC5.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC5.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC5.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC5.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC5.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	handlerPinA6.pGPIOx = GPIOA;                                              // Deseamos trabajar con el puerto GPIOA
	handlerPinA6.GPIO_PinConfig.GPIO_PinNumber = PIN_6;                       // Escribimos el Numero del Pin
	handlerPinA6.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinA6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinA6.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinA6.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinA6.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	// Cargamos la configuracion de los pines de los siete segmentos
	GPIO_Config(&handlerPinC9);
	GPIO_Config(&handlerPinC8);
	GPIO_Config(&handlerPinB8);
	GPIO_Config(&handlerPinC6);
	GPIO_Config(&handlerPinB9);
	GPIO_Config(&handlerPinC5);
	GPIO_Config(&handlerPinA6);

	// ----------------------------PINES PARA LOS TRANSISTORES DEL DISPLAY  ----------------------------------------
	//Definimos el handler para los Pines correspondientes a los transistores
	handlerPinC10.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC10.GPIO_PinConfig.GPIO_PinNumber = PIN_10;                       // Escribimos el Numero del Pin
	handlerPinC10.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC10.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC10.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC10.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC10.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	handlerPinC12.pGPIOx = GPIOC;                                              // Deseamos trabajar con el puerto GPIOC
	handlerPinC12.GPIO_PinConfig.GPIO_PinNumber = PIN_12;                       // Escribimos el Numero del Pin
	handlerPinC12.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;               // Modo del pin de salida
	handlerPinC12.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinC12.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinC12.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinC12.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	// Cargamos la configuracion de los pines conectados a los transistores
	GPIO_Config(&handlerPinC10);
	GPIO_Config(&handlerPinC12);

	// ---------------------------- PINES DEL ENCODER ----------------------------------------
	/* Configurar el pin como una entrada digital */
	handlerPinC4.pGPIOx = GPIOC;
	handlerPinC4.GPIO_PinConfig.GPIO_PinNumber = PIN_4;
	handlerPinC4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	handlerPinC4.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;

	// CLK
	handlerPinA11.pGPIOx = GPIOA;                                              // Deseamos trabajar con el puerto GPIOA
	handlerPinA11.GPIO_PinConfig.GPIO_PinNumber = PIN_11;                      // Escribimos el Numero del Pin
	handlerPinA11.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_IN;                // Modo del pin de salida
	handlerPinA11.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinA11.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinA11.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinA11.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	// DT
	handlerPinB12.pGPIOx = GPIOB;                                              // Deseamos trabajar con el puerto GPIOB
	handlerPinB12.GPIO_PinConfig.GPIO_PinNumber = PIN_12;                      // Escribimos el Numero del Pin
	handlerPinB12.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_IN;                // Modo del pin de salida
	handlerPinB12.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPE_PUSHPULL;         // Tipo push-pull
	handlerPinB12.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPDR_NOTHING;     // No aplica porque es de salida
	handlerPinB12.GPIO_PinConfig.GPIO_PinSpeed= GPIO_OSPEED_MEDIUM;            // Velocidad media
	handlerPinB12.GPIO_PinConfig.GPIO_PinAltFunMode= AF0;                      // Funcion alterna

	// Cargamos la configuracion de los pines del encoder
	GPIO_Config(&handlerPinC4);
	GPIO_Config(&handlerPinA11);
	GPIO_Config(&handlerPinB12);

	// ---------------------------- TIMERS 2 Y 3 ----------------------------------------
	/* Configuracion del TIM2 para que haga un blinky cada 250ms */
	handlerBlinkyTimer.ptrTIMx = TIM2;
	handlerBlinkyTimer.TIMx_Config.TIMx_mode = BTIMER_MODE_UP;
	handlerBlinkyTimer.TIMx_Config.TIMx_speed = BTIMER_SPEED_1ms;
	handlerBlinkyTimer.TIMx_Config.TIMx_period = 250;
	handlerBlinkyTimer.TIMx_Config.TIMx_interruptEnable = 1;

	/* Cargando la configuracion del TIM2 en los registros */
	BasicTimer_Config(&handlerBlinkyTimer);

	/* Configuracion del TIM3 para cada 10ms */
	handlerTimer3.ptrTIMx = TIM3;
	handlerTimer3.TIMx_Config.TIMx_mode = BTIMER_MODE_UP;
	handlerTimer3.TIMx_Config.TIMx_speed = BTIMER_SPEED_1ms;
	handlerTimer3.TIMx_Config.TIMx_period = 10;
	handlerTimer3.TIMx_Config.TIMx_interruptEnable = 1;

	/* Cargando la configuracion del TIM3 en los registros */
	BasicTimer_Config(&handlerTimer3);

	// ---------------------------- INTERRUPCIONES EXTI ----------------------------------------
	/* Configuracion del exti del boton del encoder */
	// Cargando la configuracion en los registros del MCU
	handlerExtiSwitch.pGPIOHandler = &handlerPinC4;
	handlerExtiSwitch.edgeType = EXTERNAL_INTERRUPT_RISING_EDGE;
	extInt_Config(&handlerExtiSwitch);

	handlerExtiGiro.pGPIOHandler = &handlerPinA11;
	handlerExtiGiro.edgeType = EXTERNAL_INTERRUPT_FALLING_EDGE;
	extInt_Config(&handlerExtiGiro);

}// Termina el init_Hardware

/* Funciones de los EXTI */
// Funcion del boton del encoder
void callback_extInt4(void){
	if (counterExtiSwitch){
		counterExtiSwitch=0;
	} else {
		counterExtiSwitch=1;
	}
}

// Funcion del giro del encoder
void callback_extInt11(void){
	counterExtiGiro = GPIO_ReadPin(&handlerPinB12);
	if (!counterExtiSwitch){
	    //CCW para la Culebrita
	    if(!counterExtiGiro){
			if(snakeCounter == 0){
				snakeCounter = 12;
			}
			snakeCounter--;
		}
		//CW para la Culebrita
		else{
			if(snakeCounter == 12){
				snakeCounter = 0;
			}
			snakeCounter++;
		}
	} else {
		//CCW para el contador
		if(!counterExtiGiro){
			if(counter == 0){
				counter++;
			}
			counter--; // Para que se quede en el numero 0
		}
		//CW para el contador
		else{
			if(counter == 99){
				counter--;
			}
			counter++; // Para que se quede en el numero 99
		}
	}
}

// Funciones de los timers
void BasicTimer2_Callback(void){
	GPIOxTooglePin(&handlerBlinkyPin);
}

void BasicTimer3_Callback(void){
	double result = counter/10;
	counter2 = (uint32_t)floor(result);
	counter1 = counter%10;
	if (counterExtiSwitch){
		if (UnOrDec==0){
			GPIO_WritePin(&handlerPinC10, SET);
			GPIO_WritePin(&handlerPinC12, RESET);
			GPIO_WritePin(&handlerPinC9, Digit[counter1][0]); // a
			GPIO_WritePin(&handlerPinC8, Digit[counter1][1]); // b
			GPIO_WritePin(&handlerPinB8, Digit[counter1][2]); // c
			GPIO_WritePin(&handlerPinC6, Digit[counter1][3]); // d
			GPIO_WritePin(&handlerPinB9, Digit[counter1][4]); // e
			GPIO_WritePin(&handlerPinC5, Digit[counter1][5]); // f
			GPIO_WritePin(&handlerPinA6, Digit[counter1][6]); // g
			UnOrDec=1;
		} else {
			GPIO_WritePin(&handlerPinC10, RESET);
			GPIO_WritePin(&handlerPinC12, SET);
			GPIO_WritePin(&handlerPinC9, Digit[counter2][0]); // a
			GPIO_WritePin(&handlerPinC8, Digit[counter2][1]); // b
			GPIO_WritePin(&handlerPinB8, Digit[counter2][2]); // c
			GPIO_WritePin(&handlerPinC6, Digit[counter2][3]); // d
			GPIO_WritePin(&handlerPinB9, Digit[counter2][4]); // e
			GPIO_WritePin(&handlerPinC5, Digit[counter2][5]); // f
			GPIO_WritePin(&handlerPinA6, Digit[counter2][6]); // g
			UnOrDec=0;
		}
	} else {
		GPIO_WritePin(&handlerPinC9,  Culebrita[snakeCounter][0]); // a
		GPIO_WritePin(&handlerPinC8,  Culebrita[snakeCounter][1]); // b
		GPIO_WritePin(&handlerPinB8,  Culebrita[snakeCounter][2]); // c
		GPIO_WritePin(&handlerPinC6,  Culebrita[snakeCounter][3]); // d
		GPIO_WritePin(&handlerPinB9,  Culebrita[snakeCounter][4]); // e
		GPIO_WritePin(&handlerPinC5,  Culebrita[snakeCounter][5]); // f
		GPIO_WritePin(&handlerPinA6,  Culebrita[snakeCounter][6]); // g
		GPIO_WritePin(&handlerPinC10, Culebrita[snakeCounter][7]); // 1
 		GPIO_WritePin(&handlerPinC12, Culebrita[snakeCounter][8]); // 2
	}
}



/*
 * Semana5.c
 *
 *  Created on: Mar 9, 2023
 *      Author: Maria Jose Uribe
 */

#include <stdint.h>
// libreria para variables booleanas
#include <stdbool.h>
// libreria para operaciones matematicas
#include <math.h>

//TAREA: Convertidor de binario a decimal !!!!
// Header funciones
void clearGlobal(void);
uint8_t getMaxChar(void);
uint16_t getMaxValue (uint16_t x, uint16_t y, uint16_t z);
uint32_t getMaxVarValue (uint8_t a, bool b );

#define UNSIGNED 0
#define SIGNED 1
#define CONSTANTE = 100
bool variableBooleana = true;
uint32_t parametro1 = 100;
uint8_t parametro2 = 200;
uint16_t parametro3 = 200;

int main(void){
	clearGlobal();
	parametro1 = getMaxChar();
	uint16_t parametro3 = getMaxValue(100, 200, 50);
	parametro1 = getMaxVarValue (8, 0 );
}

void clearGlobal(void){
	/* Se modifican las variables GLOBALES */
	variableBooleana = false;
	parametro1 = 0;
	parametro2 = 0;
}

uint8_t getMaxChar(void){
	uint8_t maxChar = pow(2,8)-1;
	//El final de una funcion que no es void debe tener un return
	return maxChar;
	//Luego de ejecutarla se debe guardar el valor en alguna variable porque si no se pierde
}

uint16_t getMaxValue (uint16_t x, uint16_t y, uint16_t z){
	if((x>=y) && (y>=z)){
		return x;
	}

}

uint32_t getMaxVarValue (uint8_t a, bool b ){
	uint32_t maxVar= 0;
	if (b==UNSIGNED){
		maxVar = pow(2,a)-1;
	} else {
		maxVar = pow(2,a)/2-1;
	};
	return maxVar;

}

int function (uint8_t int1, uint16_t int2){

}

void function2 (uint8_t int1, uint16_t int2){

}

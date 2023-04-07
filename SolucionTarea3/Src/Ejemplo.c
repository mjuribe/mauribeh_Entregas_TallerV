/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Maria Jose Uribe Henao
 * @brief          : Configuracion basica de un proyecto
 ******************************************************************************
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stm32f4xx.h>

/* Definicion de elementos del programa */
uint32_t counter = 0;
uint32_t auxVariable = 0;

uint32_t *ptr_Counter;

uint8_t byteVariable;
uint8_t *ptr_ByteVariable;


int main (void){

	/* Trabajando con las variables y los punteros */
	counter = 3456789;      // Asignar un valor
	auxVariable = counter;  // 	C es pasado por valor

	ptr_Counter = &counter; // Solo recibe datos de posiciones de memoria, se pasa esta posicion de counter

	*ptr_Counter = 9876543; // Escribimos un dato en la casilla de memoria a donde el puntero apunta

	ptr_Counter++;          // Movemos una (1) posicion de memoria el puntero
	*ptr_Counter = 9876543; // Escribimos un dato en la casilla de memoria a donde el puntero apunta

	byteVariable = 234;
	ptr_ByteVariable = &byteVariable;
	*ptr_ByteVariable = 87;

	//ptr_ByteVariable = &counter;
	auxVariable = (uint32_t)ptr_Counter;

	ptr_ByteVariable = (uint8_t *)auxVariable;
	*ptr_ByteVariable = 2;




	while (1){

	}

	return 0;

}

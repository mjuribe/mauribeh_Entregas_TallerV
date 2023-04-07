/*
 * semana7.c
 *
 *  Created on: Mar 23, 2023
 *      Author: Maria Jose Uribe
 */

//ctrl+shift+c y seleccionando las lineas que queramos crea comentarios
//ctrl+alt multicursor

uint8_t Dato = 0;
uint8_t *ptrDato = &Dato; //posicion de memoria
ptrDato = ptrDato+ 2; //Mover dos posiciones de memoria
uint8_t *pDato2 = (uint8_t*) 0x20000000; //* indica puntero
uint8_t var1 = 100;
uint16_t var2= (uint16_t)var1; //casteo
uint16_t Dato3 = 10;
uint16_t *pDato3 = &Dato3;
//dos numeros hexadecimales suman un byte es decir 8 bits

#include <stdint.h>

int main(void){
	uint8_t dato = 10;
	//uint16_t *pDato = &dato; //Puntero a la posicion de memoria de la variable dato, hay un conflicto de tipos
	uint8_t *pDato = &dato;
	uint32_t addrDato = (uint32_t) pDato; // el numero que corresponde a la memoria
	*pDato = 20; //cambiando el valor de la variable
	pDato ++; // aumentando la posiciond de memoria
	*pDato = 50; // modifica la siguiente posicion de memoria
	uint32_t datoUno = 0xABCD;
	uint32_t *pDatoUno = &datoUno;
	*pDato = 0x1234;

	uint32_t miPrimerArreglo[5] = {12, 15, 0xABC, 0b1111};
	uint32_t variable1 = *miPrimerArreglo;
	miPrimerArreglo ++;

typedef struct{

	uint8_t edad;
	uint16_t estatura;
	uint32_t notas[10];
}Estudiante_t;

Estudiante_t estudiante1 ={0};
Estudiante_t estudiante2 ={0};
Estudiante_t estudiante3 ={0};
Estudiante_t estudiante4 ={0};

Estudiante_t arregloEstudiante[4] = {estudiante1, estudiante2, estudiante3, estudiante4};

estudiante1.edad = 22;
estudiante1.estatura = 173;
*(estudiante1.notas) = 45;
*(estudiante1.notas +1) = 38;

Estudiante_t *pEstudiante1 = &estudiante1;
//NO debemos asignar la posicion de memoria con 0x200... porque se puede reventar el micro
pEstudiante1 -> edad =21;
pEstudiante1->estatura=163;
pEstudiante1->notas= 80;

char miString[] = "Frase completa";
char miString[18] = {'H', 'o', 'l', 'a'};
//Caracter comillas simples, palbras comillas dobles





}


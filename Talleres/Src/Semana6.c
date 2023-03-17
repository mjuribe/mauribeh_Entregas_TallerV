/*
 * Semana6.c
 *
 *  Created on: Mar 16, 2023
 *      Author: majo
 */

#include <stdint.h>

#define SUMA '+'
#define RESTA '-'
#define MULTIPLICACION '*'
#define DIVISION '/'
#define FACTORIAL '!'
#define FIBONACCI 'F'

uint16_t Operaciones(uint8_t tipoOperacion, uint16_t numero1, uint16_t numero2);
uint32_t Operaciones2(uint8_t tipoOperacion, uint16_t numero);

int main(void){
	uint8_t res=0;
    /*
	uint16_t resultado = Operaciones(SUMA, 10,20);
	resultado = Operaciones('*', 12,6);
	resultado = Operaciones(DIVISION, 50,5);
	*/

    /*
	uint8_t contador = 0;
	uint8_t variable1 = 0;

	while (contador < 10){
		variable1 += 10*contador;
		contador++;
	}*/

	res = Operaciones2('F', 5);


}

uint32_t Operaciones2(uint8_t tipoOperacion, uint16_t numero){
	uint8_t contador = 1;
	uint8_t variable1 = 0;
	uint8_t variable2 = 0;
	uint8_t variable3 = 0;

	switch(tipoOperacion){
	case FACTORIAL:{
		while (contador <= numero+1){
			variable1 *= contador;
			contador++;
	}
		return variable1;
		break;
	}
	case FIBONACCI:{
		variable1=1;
		variable2=1;
		while(contador<= numero){
			variable3=variable1+variable2;
			variable1=variable2;
			variable2=variable3;
			contador++;

		}
		return variable3;
		break;
	}

	}

}


// Funcion calcular operacion
uint16_t Operaciones(uint8_t tipoOperacion, uint16_t numero1, uint16_t numero2){

	/*if(tipoOperacion == "SUMA"){
		whatevs
	} else if para cada operacion entonces mejor usar un switch-case
	*/
	switch(tipoOperacion){
	case SUMA:{
		return numero1 + numero2;
		break;
	}
	case RESTA:{
		return numero1 - numero2;
		break;
	}
	case MULTIPLICACION:{
		return numero1 * numero2;
		break;
	}
	case DIVISION:{
		return numero1 / numero2;
		break;
	}
	default:{
		return 0;
		break;
	}
	}
}

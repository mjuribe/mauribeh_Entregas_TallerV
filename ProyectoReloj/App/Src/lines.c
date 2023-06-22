/*
 * lines.c
 *
 *  Created on: Jun 19, 2023
 *      Author: majo
 */

#include "lines.h"

//Primera linea del reloj, ultima de la cinta de leds
void itis(uint8_t color){
	//INtentar enviar lineas completas apagadas, ver si no pone problemas con los tiempos
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 5
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 4
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 3
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 2
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 1
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //s
		azul(); //i
		apagado();
		azul(); //t
		azul(); //i
	}else if(color==1){
		magenta();
		magenta();
		apagado();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		apagado();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		apagado();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		apagado();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		apagado();
		naranja();
		naranja();
	}

}

//Primera linea del reloj, ultima de la cinta de leds
void tenmin(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 5
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 4
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 3
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 2
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 1
	apagado();
	apagado();
	if(color==0){
		azul(); //n
		azul(); //e
		azul(); //t
	}else if(color==1){
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
	}

}

//Segunda linea del reloj
void quarter(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 5
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 4
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 3
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 2
	apagado();
	if(color==0){
		azul(); //q
		azul(); //u
		azul(); //a
		azul(); //r
		azul(); //t
		azul(); //e
		azul(); //r
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
	}

}

//Tercera linea del reloj
void twentymin(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 5
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 4
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 3
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //y
		azul(); //t
		azul(); //n
		azul(); //e
		azul(); //w
		azul(); //t
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

//Tercera linea del reloj
void fivemin(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 5
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 4
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 3
	apagado();
	if(color==0){
		azul(); //e
		azul(); //v
		azul(); //i
		azul(); //f
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

//Cuarta linea del reloj
void half(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 5
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 4
	apagado();
	if(color==0){
		azul(); //h
		azul(); //a
		azul(); //l
		azul(); //f
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

//Cuarta linea del reloj
void to(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 5
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 4
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //t
		azul(); //o
	}else if(color==1){
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
	}
}

//Quinta linea del reloj
void past(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 5
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //t
		azul(); //s
		azul(); //a
		azul(); //p
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

//Quinta linea del reloj
void seven(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 5
	if(color==0){
		azul(); //n
		azul(); //e
		azul(); //v
		azul(); //e
		azul(); //s
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

//Sexta linea del reloj
void one(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	if(color==0){
		azul(); //o
		azul(); //n
		azul(); //e
	}else if(color==1){
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
	}
}

//Sexta linea del reloj
void two(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //t
		azul(); //w
		azul(); //o
	}else if(color==1){
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
	}
}

//Sexta linea del reloj
void three(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 6
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //t
		azul(); //h
		azul(); //r
		azul(); //e
		azul(); //e
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

//Septima linea del reloj
void four(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //r
		azul(); //u
		azul(); //o
		azul(); //f
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
	}
}


//Septima linea del reloj
void five(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //e
		azul(); //v
		azul(); //i
		azul(); //f
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
	}
}
//Septima linea del reloj
void six(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 7
	if(color==0){
		azul(); //x
		azul(); //i
		azul(); //s
	}else if(color==1){
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
	}
}

//Octava linea del reloj
void nine(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	if(color==0){
		azul(); //n
		azul(); //i
		azul(); //n
		azul(); //e
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

//Octava linea del reloj
void twelve(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 9
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 8
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //t
		azul(); //w
		azul(); //e
		azul(); //l
		azul(); //v
		azul(); //e
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

//Novena linea no tiene palabras

//Decima linea del reloj
void eight(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	if(color==0){
		azul(); //e
		azul(); //i
		azul(); //g
		azul(); //t
		azul(); //h
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

//Decima linea del reloj
void eleven(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	//Linea 10
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //e
		azul(); //l
		azul(); //e
		azul(); //v
		azul(); //e
		azul(); //n
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

//Ultima linea del reloj, primera de la cinta de leds
void ten(uint8_t color){
	//Linea 11
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	apagado();
	if(color==0){
		azul(); //n
		azul(); //e
		azul(); //t
	}else if(color==1){
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
	}
}

//Ultima linea del reloj, primera de la cinta de leds
void oclock(uint8_t color){
	//Linea 11
	if(color==0){
		azul(); //k
		azul(); //c
		azul(); //o
		azul(); //l
		azul(); //c
		azul(); //o
	}else if(color==1){
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
		magenta();
	}else if(color==2){
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
		amarillo();
	}else if(color==3){
		verde();
		verde();
		verde();
		verde();
		verde();
		verde();
	}else if(color==4){
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
		blanco();
	}else if(color==5){
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
		naranja();
	}
}

////Primera linea del reloj, ultima de la cinta de leds
//void itis(void){
//	//LUEGO INTENTAR PONER CONDICIONALES PARA LOS COLORES
//	//INtentar enviar lineas completas apagadas, ver si no pone problemas con los tiempos
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 5
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 4
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 3
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 2
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 1
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	azul(); //s
//	azul(); //i
//	apagado();
//	azul(); //t
//	azul(); //i
//}
//
////Primera linea del reloj, ultima de la cinta de leds
//void tenmin(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 5
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 4
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 3
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 2
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 1
//	apagado();
//	apagado();
//	azul(); //n
//	azul(); //e
//	azul(); //t
//}
//
////Segunda linea del reloj
//void quarter(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 5
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 4
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 3
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 2
//	apagado();
//	azul(); //q
//	azul(); //u
//	azul(); //a
//	azul(); //r
//	azul(); //t
//	azul(); //e
//	azul(); //r
//	apagado();
//	apagado();
//	apagado();
//}
//
////Tercera linea del reloj
//void twentymin(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 5
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 4
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 3
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	azul(); //y
//	azul(); //t
//	azul(); //n
//	azul(); //e
//	azul(); //w
//	azul(); //t
//}
//
////Tercera linea del reloj
//void fivemin(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 5
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 4
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 3
//	apagado();
//	azul(); //e
//	azul(); //v
//	azul(); //i
//	azul(); //f
//}
//
////Cuarta linea del reloj
//void half(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 5
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 4
//	apagado();
//	azul(); //h
//	azul(); //a
//	azul(); //l
//	azul(); //f
//}
//
////Cuarta linea del reloj
//void to(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 5
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 4
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	azul(); //t
//	azul(); //o
//	apagado();
//	apagado();
//}
//
////Quinta linea del reloj
//void past(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 5
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	azul(); //t
//	azul(); //s
//	azul(); //a
//	azul(); //p
//	apagado();
//}
//
////Quinta linea del reloj
//void seven(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 5
//	azul(); //n
//	azul(); //e
//	azul(); //v
//	azul(); //e
//	azul(); //s
//}
//
////Sexta linea del reloj
//void one(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	azul(); //o
//	azul(); //n
//	azul(); //e
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//}
//
////Sexta linea del reloj
//void two(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	azul(); //t
//	azul(); //w
//	azul(); //o
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//}
//
////Sexta linea del reloj
//void three(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 6
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	azul(); //t
//	azul(); //h
//	azul(); //r
//	azul(); //e
//	azul(); //e
//}
//
////Septima linea del reloj
//void four(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	azul(); //r
//	azul(); //u
//	azul(); //o
//	azul(); //f
//}
//
//
////Septima linea del reloj
//void five(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	apagado();
//	apagado();
//	apagado();
//	azul(); //e
//	azul(); //v
//	azul(); //i
//	azul(); //f
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//}
////Septima linea del reloj
//void six(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 7
//	azul(); //x
//	azul(); //i
//	azul(); //s
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//}
//
////Octava linea del reloj
//void nine(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	azul(); //n
//	azul(); //i
//	azul(); //n
//	azul(); //e
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//}
//
////Octava linea del reloj
//void twelve(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 9
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 8
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	azul(); //t
//	azul(); //w
//	azul(); //e
//	azul(); //l
//	azul(); //v
//	azul(); //e
//}
//
////Novena linea no tiene palabras
//
////Decima linea del reloj
//void eight(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	azul(); //e
//	azul(); //i
//	azul(); //g
//	azul(); //t
//	azul(); //h
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//}
//
////Decima linea del reloj
//void eleven(void){
//	//Linea 11
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	//Linea 10
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	apagado();
//	azul(); //e
//	azul(); //l
//	azul(); //e
//	azul(); //v
//	azul(); //e
//	azul(); //n
//}

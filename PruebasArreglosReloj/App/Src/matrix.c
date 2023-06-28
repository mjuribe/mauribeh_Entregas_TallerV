/*
 * matrix.c
 *
 *  Created on: Jun 26, 2023
 *      Author: majo
 */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

typedef struct  {
    char key[30];
    int pos[30];
    int value[30];
}Dictionary;

Dictionary dict[] = { {"it", {120},{2} }, {"is", {117},{2}}, {"tenmin", {113},{2}},
		{"quarter", {101},{7}},
		{"twentymin", {94},{6}},{"fivemin", {90},{4} },
		{"half", {79},{4}},{"to", {85}, {2}},
		{"past", {73},{4}},{"seven", {67},{5}},
		{"one", {56},{3}},{"two", {59},{3}},{"three", {62},{5}},
		{"four", {52}, {4}},{"five", {48},{4}},{"six",{45},{3} },
		{"nine", {34},{4}},{"twelve", {39}, {6}},
		{"eight", {12}, {5}},{"eleven", {17}, {6}},
		{"ten", {8},{3}},{"oclock", {1},{ 6}},};

uint8_t matrix[121]={
		0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,
};

void arreglofun(void){
	//char k1= (char)*dict[0].key;
	int p1= (int )*dict[0].pos;
	int v1= (int)*dict[0].value;
	for(uint8_t i=0; i<=v1; i++ ){
		matrix[p1+i]=1;
	}
}

//Dictionary dict[] = { {"it", 120,2 }, {"is", 117,2}, {"tenmin", 113,2},
//		{"quarter", 101,7},
//		{"twentymin", 94,6},{"fivemin", 90,4 },
//		{"half", 79,4},{"to", 85, 2},
//		{"past", 73,4},{"seven", 67,5},
//		{"one", 56,3},{"two", 59,3},{"three", 62,5},
//		{"four", 52, 4},{"five", 48,4},{"six",45,3 },
//		{"nine", 34,4},{"twelve", 39, 6},
//		{"eight", 12, 5},{"eleven", 17, 6},
//		{"ten", 8,3},{"oclock", 1, 6},};


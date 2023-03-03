/*
 * Semana4.c
 *
 *  Created on: Mar 2, 2023
 *      Author: majo
 */
#include <stdint.h>

char     var1 = 0 ;
int      var2 = 0 ;
short    var3 = 0 ;
long     var4 = 0 ;

uint8_t  var5 = 0 ;
int8_t   var6 = 0 ;
int16_t  var7 = 0 ;
uint32_t var8 = 0 ;
int64_t  var9 = 0 ;
// poner 0 es hacer un clear y poner 1 es hacer un set con un OR


int main(void)
{
    uint16_t testShift = 0b000000100110111;
    uint16_t testMask = 0b000000000001111;

    while(1){

        //testShift = testShift >> 1;
        uint16_t resultado = testShift | testMask;

        resultado = testShift & (-testMask);

        resultado = 0;
        //testMask = testMask<<3;
        //testShift = testMask;
        //testShift = testShift & testMask;
    }
}


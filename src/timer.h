#ifndef HALL_H
#define HALL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

typedef struct
{
   uint8_t s;
   uint8_t m;
   uint8_t h;  
}time;

#endif
#ifndef DISPLAY_H
#define DISPLAY_H


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "driver.h"
float time_compute(uint16_t image[]);
void display_image(uint16_t image[], float delay_time);



#endif
#ifndef DISPLAY_H
#define DISPLAY_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "driver.h"
#include "hall.h"


typedef struct
{
    int index;
    int max_index;
    uint8_t overflow;
    int time;
} display_index;

void set_display_index( display_index * INDEX, int max);

void check_index(display_index * INDEX);

void display_image(uint16_t image[], display_index * INDEX);

display_index * get_display_index(); //used for hall functions

#endif
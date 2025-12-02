#ifndef HALL_H
#define HALL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart_interrupt.h"
#include "display_img.h"


void HALL_init();
void INT0_handler();

int get_duration();
uint8_t get_known_position();
uint16_t get_current_angle();

#endif /* HALL_H */
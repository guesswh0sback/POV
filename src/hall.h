#ifndef HALL_H
#define HALL_H

#include "uart_basic.h"
#include "display.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "driver.h"

void HALL_init();
void INT0_handler();

int get_time();
uint8_t get_known_position();


#endif /* HALL_H */
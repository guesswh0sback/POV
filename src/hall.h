#ifndef HALL_H
#define HALL_H


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "driver.h"

void HALL_init();
void TIMER1_init();
float get_total_time();

#endif /* HALL_H */
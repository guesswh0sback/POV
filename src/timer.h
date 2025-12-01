#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "driver.h"
// #include "uart_interrupt.h"
typedef struct
{
   uint8_t s;
   uint8_t m;
   uint8_t h;
} time;

time *get_time();

void init_timer(time * time, int h, int m, int s);
void time_for_ISR(time * time);
void timer1_init_1s(time * time);
void timer_update(time * time);


#endif /* TIMER_H */

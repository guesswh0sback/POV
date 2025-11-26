#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "driver.h"

typedef struct
{
   uint8_t s;
   uint8_t m;
   uint8_t h;
} time;

<<<<<<< HEAD
time *get_time();

#endif /* TIMER_H */
=======
void time_for_ISR(time * time);
void timer1_init_1s(time * time);
void timer_update(time * time);


#endif
>>>>>>> 02b49817bd7cc1afdb317ba0a210d694ba330a2e

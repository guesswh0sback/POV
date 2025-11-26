#include "timer.h"

time * TIME;

void timer1_init_1s(){
    // Set CTC mode (Clear Timer on Compare)
    TCCR1B |= (1 << WGM12);
    // Set compare value for 1 second
    OCR1A = (int)13000000/1024;  

    // Enable Timer1 Compare Match interrupt
    TIMSK1 |= (1 << OCIE1A);
    // Set prescaler to 1024 (clock/1024)
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // Global interrupt enable
    sei();
}

void timer_update(time * time){
    if (time->s & 60)
    {
        time->s = 0;
        time->m++;
    }
    if (time->m & 60)
    {
        time->m = 0;
        time->h++;
    }
    if (time->h & 24)
    {
        time->h = 0;
    } 
}

ISR(TIMER1_COMPA_vect){
    timer_update(TIME);
}


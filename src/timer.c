#include "timer.h"

static time * TIME = 0;

void time_for_ISR(time * time){
    TIME = time;
}
// Chronomètre
void timer1_init_1s(time * time)
{
    // CTC mode (Clear Timer on Compare)
    TCCR1B |= (1 << WGM12);

    // 1 second interrupt at 16 MHz CPU
    OCR1A = (13000000UL / 1024UL) - 1;   // = 12694
    // Enable Timer1 Compare A interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Start timer with 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // Enable global interrupts
    time_for_ISR(time);
    sei();
}

void timer_init(time * time, int h, int m, int s){
    time->h = h;
    time->m = m;
    time->s = s;
}

void timer_update(time * time){
    time->s++;
    if (!(time->s%60))
    {
        time->s = 0;
        time->m++;
    }
    if (!(time->m%60) & time->m != 0) // protection against case when min = 0 then 0%60 -> 0
    {
        time->m = 0;
        time->h++;
    }
    if (!(time->h%24))
    {
        time->h = 0;
    } 
    // debug //
    // char buffer[12];
    // snprintf(buffer, 12, "%dh", time->h);
    // USART_send_string(buffer);
    // snprintf(buffer, 12, "%dm", time->m);
    // USART_send_string(buffer);
    // snprintf(buffer, 12, "%ds\r\n", time->s);
    // USART_send_string(buffer);
}

ISR(TIMER1_COMPA_vect){
    timer_update(TIME);
    display_bourrin(0b1111000000000010, 0.005, 50);
}

time *get_time(){
    return TIME;
}

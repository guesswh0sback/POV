#include "timer.h"

time * TIME; // étoile pour pointeur

// Chronomètre
void timer1_init_1s(){
    // Set CTC mode (Clear Timer on Compare)
    TCCR1B |= (1 << WGM12);
    // Set compare value for 1 second
    OCR1A = (int)13000000/1024;  // C'est ici que se règle la précision. 
    //Il peut y avoir une petite imprécision liée au fait que le quaertz n'est pas parfaitement à 13MHz. 
    //De plus, le résultat est arrondi à l'entier le plus proche.

    // Enable Timer1 Compare Match interrupt
    TIMSK1 |= (1 << OCIE1A);
    // Set prescaler to 1024 (clock/1024)
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // Global interrupt enable
    sei();
}

void timer_update(time * time){
    time->s++;
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

time *get_time(){
    return TIME;
}

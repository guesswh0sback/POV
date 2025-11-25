#include "hall.h"

int time_per_frame = 50; //ms
uint8_t known_position = 0; //flag for 

ISR(INT0_vect)
{
    display_bourrin(0b1000000000000001, 0.005, 50);
    INT0_handler();
}

void HALL_init()
{
    // --- TIMER1 as free-running 16-bit counter ---
    TCCR1A = 0;
    TCCR1B = (1 << CS11);   // prescaler = 8 → tick = 0.5 µs at 16 MHz

    // --- INT0 on rising edge ---
    EICRA = (1 << ISC01) | (1 << ISC00);
    EIMSK = (1 << INT0);

    sei();
}

void INT0_handler(){
    display_index * index = get_display_index(); // function from display
    if(index->index < index->max_index){ // if display did not have the time to parse all the image
        time_per_frame -= (int) time_per_frame/2; // lowers the time per frame
    }
    else if(index->overflow) // if display parsed to rapidly the image
    {
        time_per_frame += (int) time_per_frame/2; // increase the time per frame
    }
    known_position = 1; //if interruption is triggered the position is known    
}

int get_time(){ // return time_per_frame updated by interrupt handler
    return time_per_frame;
}
uint8_t get_known_position(){ // checks if POV is at the known position 
    if (known_position) //if it is
    {
        return known_position--; //return 1 because handler set flag and then resets it to 0
    }
    return 0; //return 0 if it is not 
}
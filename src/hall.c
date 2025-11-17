#include "hall.h"





uint16_t ALL_LEDS =       0b1111111111111111;
uint16_t HALF_LEDS_A =    0b0000000011111111;
uint16_t HALF_LEDS_B =    0b1111111100000000;
uint16_t ONE_OUT_OF_TWO = 0b1010101010101010;
uint16_t JUST_ONE_LED =   0b1000000000000001;
int counter = 0;
int protection = 1;



uint32_t time_diff[100];


void HALL_init(){
    display_bourrin(HALF_LEDS_A, 0.005, 1000);

    DDRD &= ~(1 << PD2); //set PD2 (INT0) as input
    PORTD |= (1 << PD2); //enable pull-up on PD2

    EIMSK |= (1 << INT0); //enable external interrupt INT0
    EICRA |= (1 << ISC01) | (1 << ISC00); //trigger INT0 on rising edge

    display_bourrin(HALF_LEDS_B, 0.005, 1000);
}

void TIMER1_init(){

    display_bourrin(0b1010101010101010, 0.005, 1000);

    TCCR1A = 0; //normal port operation
    TCCR1B |= (1 << WGM12); //CTC mode
    TCCR1B |= (1 << CS12); //prescaler 256 (0bXXX<<CS10)
    OCR1A = 62500; //compare value for 1s at 13MHz with prescaler 256
    TIMSK1 |= (1 << OCIE1A); //enable compare interrupt

    display_bourrin(0b0101010101010101, 0.005, 1000);
    
}

float get_total_time(){
    uint32_t mean_time = 0;
    for (int i = 0; i < 100; i++)
    {
        mean_time += time_diff[i];
    }
    mean_time = mean_time * (256.0 / 13000000.0 / 100.0);

    return ((float)mean_time); //time in seconds
}

ISR(INT0_vect){
    if (protection){
        TCNT1 = 0;  //reset timer
        counter++;
        display_bourrin((1<<(counter%16)), 0.005, 1);
        protection = 0;
    }
    else{
        if (counter <100)
        {
            time_diff[counter] = TCNT1;
        }
        
        protection = 1;
    }
}

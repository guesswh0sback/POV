#include "../src/timer.h"

time TIME;

int main(){
    SPI_init();
    display_bourrin(0b0101010101010101, 0.005, 1000);
    LEDS_off();
    timer1_init_1s(&TIME);
    while (1)
    {
        /* code */
    }
    
    return 0;
}
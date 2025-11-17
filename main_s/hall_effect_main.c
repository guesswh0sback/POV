#include "../src/hall.h"



uint16_t ALL_LEDS_m = 0b1111111111111111;
uint16_t HALF_LEDS_A_m = 0b0000000011111111;
uint16_t HALF_LEDS_B_m = 0b1111111100000000;
uint16_t ONE_OUT_OF_TWO_m = 0b1010101010101010;

int main(void) {
    SPI_init();
    for (int i = 0; i < 10; i++) //display startup pattern
    {
        display_bourrin(HALF_LEDS_A_m, 0.005, 50);
        display_bourrin(HALF_LEDS_B_m, 0.005, 50);
    }
    
    HALL_init();
    //TIMER1_init();

    sei(); // Enable global interrupts

    display_bourrin(ONE_OUT_OF_TWO_m, 0.005, 1000);
    while (1)
    {
        // Main loop can be empty as functionality is interrupt-driven
    }

    return 0;
}
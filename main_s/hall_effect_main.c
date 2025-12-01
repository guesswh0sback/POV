#include "../src/hall.h"

uint16_t ALL_LEDS_m = 0b1111111111111111;
uint16_t HALF_LEDS_A_m = 0b0000000011111111;
uint16_t HALF_LEDS_B_m = 0b1111111100000000;
uint16_t ONE_OUT_OF_TWO_m = 0b1010101010101010;

#define BAUDRATE 38400

ring_buffer rx_buffer;
ring_buffer tx_buffer;


int main(void) {
    SPI_init();
    USART_init(BAUDRATE, &rx_buffer, &tx_buffer);

    for (int i = 0; i < 10; i++) //display startup pattern
    {
        display_bourrin(HALF_LEDS_A_m, 50000);
        display_bourrin(HALF_LEDS_B_m, 50000);
    }
    
    HALL_init();

    display_bourrin(ONE_OUT_OF_TWO_m, 50000);
    LEDS_off();
    while (1)
    {
        // Main loop can be empty as functionality is interrupt-driven
    }
    return 0;
}
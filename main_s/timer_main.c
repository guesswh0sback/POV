#include "../src/timer.h"

// #define BAUDRATE 38400
// ring_buffer rx_buffer;
// ring_buffer tx_buffer;



time TIME;

int main(){
    // USART_init(BAUDRATE, &rx_buffer, &tx_buffer);
    // USART_send_string("UART initialized\n\r");

    SPI_init();
    // USART_send_string("LEDS initialized\n\r");
    timer_init(&TIME, 23, 59, 45);
    timer1_init_1s(&TIME);
    while (1)
    {
        /* code */
    }
    
    return 0;
}
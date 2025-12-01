#include "../src/uart_interrupt.h"
#include "../src/driver.h"
#define BAUDRATE 38400

ring_buffer rx_buffer;
ring_buffer tx_buffer;


int main(void){

    // Setup Bluetooth module
    USART_init(BAUDRATE, &rx_buffer, &tx_buffer);
    SPI_init();
    USART_send_string("INITIALIZING\n\r");
    uint8_t c;
    while(1){
        // Main loop
        // Check continuously for new data
        while (USART_read_byte(&c))
        {
            for (int i = 0; i < 10; i++)
            {
                display_bourrin(0b1010101010101010, 5000);
                display_bourrin(0b0101010101010101, 5000);
            }
            // Print the received byte
            USART_send_byte(c);
            USART_send_string("\n\r");
        }
    }
}

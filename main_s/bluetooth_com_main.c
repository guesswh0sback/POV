#include "../src/uart_interrupt.h"
#include "../src/driver.h"
#define BAUDRATE 38400

ring_buffer rx_buffer;
ring_buffer tx_buffer;


int main(void){

    // Setup Bluetooth module
    USART_init(BAUDRATE, &rx_buffer, &tx_buffer);
    SPI_init();
    while(1){
        // Main loop
        USART_send_string("Waiting for something to happen\n\r");
        for (int i = 0; i < 10; i++)
        {
            display_bourrin(0b1010101010101010, 0.005, 50);
            display_bourrin(0b0101010101010101, 0.005, 50);
        }
        
        // USART_Receive_string(buffer, 6);
        // uart_send_string("i recived : ");
        
        // uart_send_string(buffer);
        
        // uart_send_string("\n\r");
    }
}

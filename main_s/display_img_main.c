#include "../src/display_img.h"
#include "../src/uart_interrupt.h"
uint16_t image[] = {
(uint16_t) 0b1111000000000000,
(uint16_t) 0b0000111100000000,
(uint16_t) 0b0000000011110000,
(uint16_t) 0b0000000000001111
};

#define BAUDRATE 38400
ring_buffer rx_buffer;
ring_buffer tx_buffer;

display_index index_img;
int main(){
    USART_init(BAUDRATE, &rx_buffer, &tx_buffer);
    USART_send_string("UART initialized\n\r");

    SPI_init();
    USART_send_string("LEDS initialized\n\r");
                for (int i = 0; i < 10; i++)
            {
                display_bourrin(0b1010101010101010, 0.005, 50);
                display_bourrin(0b0101010101010101, 0.005, 50);
            }
    HALL_init();
    USART_send_string("HALL initialized\n\r");

    set_display_index(&index_img, 4);
    set_addr_display_index(&index_img);
    display_image(image, &index_img);
    return 0;
}
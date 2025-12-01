#include "../src/display_img.h"
#include "../src/uart_interrupt.h"
uint16_t image[] = {
(uint16_t) 0b1111111100000000,
(uint16_t) 0b0000000011111111,
(uint16_t) 0b1111111100000000,
(uint16_t) 0b0000000011111111
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
    HALL_init();
    USART_send_string("HALL initialized\n\r");

    set_display_index(&index_img, 4);
    set_addr_display_index(&index_img);
    display_image(image, &index_img);
    return 0;
}
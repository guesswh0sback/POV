#include "menu.h"

#define BAUDRATE 38400

ring_buffer rx_buffer;
ring_buffer tx_buffer;

time TIME;

void menu_case(){
    uint8_t cmd;
    USART_read_byte(&cmd);
    if(cmd = 'h'){ // help menu for syntaxe
        USART_send_byte("help menu :\r\n");
        USART_send_string("set time : c/HH/MM/SS\r\n");
        USART_send_string("switch clock : -clk\r\n");
    }
    if(cmd = 's'){ //set time
        uint8_t a;
        uint8_t b;

        uint8_t trash;

        USART_read_byte(&trash);

        USART_read_byte(&a);
        USART_read_byte(&b);
        int hrs = (a - '0')*10 + (b - '0');
        USART_read_byte(&trash);
        
        USART_read_byte(&a);
        USART_read_byte(&b);
        int min = (a - '0')*10 + (b - '0');
        USART_read_byte(&trash);

        USART_read_byte(&a);
        USART_read_byte(&b);
        int sec = (a - '0')*10 + (b - '0');

        timer_init(&TIME, hrs, min, sec);
    }
    if(cmd = 'c'){ //display clocks

    }
}


#include "uart_interrupt.h"

static ring_buffer rx_buffer;
static ring_buffer tx_buffer;


void USART_init(uint32_t baudrate){
    uint16_t ubrr = (unsigned int)(13000000/8/baudrate-1);
    // Set baud rate
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;
    // Enable RX, TX and RX interrupt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    // 8N1 frame format
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    ring_init(&rx_buffer);
    ring_init(&tx_buffer);
    sei(); // enable global interrupts
}


void USART_send_byte(uint8_t data){
    // Try to push into TX buffer
    if (ring_push(&tx_buffer, data)) {
        // Enable Data Register Empty interrupt
        UCSR0B |= (1 << UDRIE0);
    }
}


bool USART_read_byte(uint8_t *data){
    return ring_pop(&rx_buffer, data);
}

ISR(USART_RX_vect){ // interrupt reciver

    uint8_t data = UDR0;          // read UART data
    ring_push(&rx_buffer, data);  // store in RX ring buffer
}

ISR(USART_UDRE_vect){
    uint8_t data;

    if (ring_pop(&tx_buffer, &data)) { // interrupt transmit
        UDR0 = data;  // send next byte
    }
    else {
        // No more data → disable interrupt
        UCSR0B &= ~(1 << UDRIE0);
    }
}
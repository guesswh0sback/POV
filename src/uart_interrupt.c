#include "uart_interrupt.h"

static ring_buffer *rx_buffer = 0;
static ring_buffer *tx_buffer = 0;


void USART_init(uint32_t baud, ring_buffer * rx, ring_buffer * tx)
{

    /* Set baud rate */
    unsigned int ubrr = (unsigned int)(13000000/8/baud-1);
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    // Enable RX, TX and RX interrupt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    /* Disable parity bit */
    UCSR0A &= ~(1<<UPE0);    
    /* Enable x2 speed */
    UCSR0A |= (1<<U2X0); 
    /* Set frame format: 8data, 1stop bit */
    UCSR0C &= ~(1<<USBS0); 
    UCSR0C |= (3<<UCSZ00);
    
    buffer_for_ISR(rx, tx);
    
    ring_buffer_init(rx);
    ring_buffer_init(tx);
    
    sei(); // enable global interrupts
}

void USART_send_string(char * str){
    int i = 0;
    while (str[i] != '\0')
    {
        USART_send_byte(str[i]);
        i++;
    }
}

void USART_send_byte(uint8_t data)
{
    // Try to push into TX buffer
    if (ring_buffer_push(tx_buffer, data)) {
        // Enable Data Register Empty interrupt
        UCSR0B |= (1 << UDRIE0);
    }
}

bool USART_read_byte(uint8_t *data)
{
    return ring_buffer_pop(rx_buffer, data);
}

<<<<<<< HEAD
void buffer_for_ISR(ring_buffer * rx, ring_buffer * tx){
    rx_buffer = rx;
    tx_buffer = tx;
=======
ISR(USART_RX_vect){ // interrupt reciver
    uint8_t data = UDR0;          // read UART data
    ring_buffer_push(&rx_buffer, data);  // store in RX ring buffer
>>>>>>> 627e58edea6117fbfa1b4f49065958dff7119f5e
}

ISR(USART_RX_vect)
{
    uint8_t data = UDR0;          // read USART data
    ring_buffer_push(rx_buffer, data);  // store in RX ring buffer
}

ISR(USART_UDRE_vect)
{
    uint8_t data;

    if (ring_buffer_pop(tx_buffer, &data)) {
        UDR0 = data;  // send next byte
    } else {
        // No more data → disable interrupt
        UCSR0B &= ~(1 << UDRIE0);
    }
}
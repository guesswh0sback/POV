#ifndef UART_INTERRUPT_H
#define UART_INTERRUPT_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ring_buffer.h"


void buffer_for_ISR(ring_buffer * rx, ring_buffer * tx);

void USART_init(uint32_t baud, ring_buffer * rx, ring_buffer * tx);
void USART_send_string(char * str);
void USART_send_byte(uint8_t data);
bool USART_read_byte(uint8_t *data);

#endif
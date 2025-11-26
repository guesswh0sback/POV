#ifndef UART_INTERRUPT_H
#define UART_INTERRUPT_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ring_buffer.h"

void USART_Init(uint32_t baudrate);
void USART_send_byte(uint8_t data);
bool USART_read_byte(uint8_t *data);

#endif
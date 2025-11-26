#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define RING_BUFFER_SIZE 64   // Change to whatever size you need

typedef struct {
    uint8_t buffer[RING_BUFFER_SIZE];
    uint16_t head;   // Write index
    uint16_t tail;   // Read index
    uint16_t count;  // Number of bytes stored
} ring_buffer;

void ring_buffer_init(ring_buffer *ring_buffer);
bool ring_buffer_empty(ring_buffer *ring_buffer);
bool ring_buffer_full(ring_buffer *ring_buffer);

bool ring_buffer_push(ring_buffer *ring_buffer, uint8_t data);
bool ring_buffer_pop(ring_buffer *ring_buffer, uint8_t *data);

#endif

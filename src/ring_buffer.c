#include "ring_buffer.h"



void ring_buffer_init(ring_buffer *ring_buffer) {
    ring_buffer->head = 0;
    ring_buffer->tail = 0;
    ring_buffer->count = 0;
}

bool ring_buffer_empty(ring_buffer *ring_buffer) { // check if there is data to be read
    return ring_buffer->count == 0;
}

bool ring_buffer_full(ring_buffer *ring_buffer) { // check if buffer is full
    return ring_buffer->count == RING_BUFFER_SIZE;
}

bool ring_buffer_push(ring_buffer *ring_buffer, uint8_t data) { // write into the buffer
    if (ring_buffer_full(ring_buffer)) return false;

    ring_buffer->buffer[ring_buffer->head] = data;
    ring_buffer->head = (ring_buffer->head + 1) % RING_BUFFER_SIZE;
    ring_buffer->count++;
    return true;
}

bool ring_buffer_pop(ring_buffer *ring_buffer, uint8_t *data) { // write out of the buffer
    if (ring_buffer_empty(ring_buffer)) return false;

    *data = ring_buffer->buffer[ring_buffer->tail];
    ring_buffer->tail = (ring_buffer->tail + 1) % RING_BUFFER_SIZE;
    ring_buffer->count--;
    return true;
}

int size_of_data(ring_buffer * ring_buffer){
    return (ring_buffer->head - ring_buffer->tail);
}

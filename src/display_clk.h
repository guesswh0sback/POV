#ifndef DISPLAY_CLK_H
#define DISPLAY_CLK_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "uart_basic.h"
#include "driver.h"
#include "hall.h"
#include "timer.h"

typedef enum {
    NEEDLE_MINUTE,
    NEEDLE_HOUR
} needleType;

void display_clk();

uint16_t set_angle(needleType needle, time * current_time);
void display_needle(needleType needle);
void display_outlines();

#endif
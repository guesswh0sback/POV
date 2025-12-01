#ifndef HALL_H
#define HALL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart_basic.h"
#include "display_img.h"
#include "driver.h"

#define ANGLE_EQ(a, b, tol) (abs((int16_t)(a) - (int16_t)(b)) <= (tol))
// Vérifie si deux angles (a et b, en degrés) sont "égaux" à ±tol degrés près.
// Utile pour compenser les approximations et les sauts du rotor POV.

void HALL_init();
void INT0_handler();

int get_revolution_t();
uint8_t get_known_position();
uint16_t get_t_last_zero();

#endif /* HALL_H */
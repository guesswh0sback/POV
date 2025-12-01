#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../src/hall.h"
#include "../src/display_clk.h"
#include "../src/uart_basic.h"   // ou uart_interrupt.h selon ton setup

int main(void) {
    // --- Initialisations ---
    USART_Init(38400);   // initialisation UART pour debug
    HALL_init();         // Hall sensor + Timer1
    sei();               // Enable global interrupts

    char buffer[32];

    while (1) {
        // --- Récupération de l'angle actuel ---
        uint16_t angle = get_current_angle();

        // --- Conversion en chaîne de caractères ---
        sprintf(buffer, "Angle: %u\r\n", angle);

        // --- Envoi via UART ---
        uart_send_string(buffer);

        _delay_ms(50);  // pause pour ne pas spammer le terminal
    }

    return 0;
}

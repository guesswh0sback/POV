#include <avr/io.h>
#include <util/delay.h>

#include "../src/display_clk.h"

void display_clk_startup(void) {
    // Masques de LED pour un effet progressif
    uint16_t pattern[] = {
        0b1000000000000000,
        0b1100000000000000,
        0b1110000000000000,
        0b1111000000000000,
        0b1111100000000000,
        0b1111110000000000,
        0b1111111000000000,
        0b1111111100000000,
        0b1111111110000000,
        0b1111111111000000,
        0b1111111111100000,
        0b1111111111110000,
        0b1111111111111000,
        0b1111111111111100,
        0b1111111111111110,
        0b1111111111111111
    };

    // Affiche chaque étape pour “dessiner” le cadran
    for (int i = 0; i < 16; i++) {
        display_bourrin(pattern[i], 0.005, 50); // brightness 0.005, duration 50ms
    }

    // Effet de balayage pour montrer le mouvement
    uint16_t sweep = 0b1000000000000000;
    for (int i = 0; i < 16; i++) {
        display_bourrin(sweep, 0.005, 50);
        sweep >>= 1; // décale le bit vers la droite
        if (sweep == 0) sweep = 0b1000000000000000; // recommence le sweep
    }

    // On peut finir en allumant toutes les LEDS quelques instants
    display_bourrin(0xFFFF, 0.005, 200);
}

int main(void) {
    // --- Initialisations matérielles ---
    SPI_init();
    USART_Init(38400);   // si nécessaire pour debug
    HALL_init();         // capteur Hall pour connaître la position rotor
    sei();               // Enable global interrupts

    // Startup display clock pattern
    display_clk_startup();

    // --- Boucle principale ---
    while (1) {
        display_clk();    // appelle ton affichage POV en continu
    }
    return(0);
}
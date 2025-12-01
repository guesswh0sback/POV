#include "hall.h"

/* --- Variables globales --- */
int revolution_t = 50;           // Durée d'un tour complet en ms (ajustée dynamiquement)
volatile uint8_t known_position = 0;  // Flag pour indiquer passage devant l'aimant
volatile uint16_t t_last_zero = 0;    // Moment exact du dernier passage à l'aimant (Timer1)

/* --- ISR pour l'interruption INT0 (capteur Hall) --- */
ISR(INT0_vect)
{
    // Mettre à jour le moment du passage à l'aimant
    t_last_zero = TCNT1;       // TCNT1 = compteur Timer1 16-bit
    known_position = 1;        // Signaler à display_clk que l'on est passé devant l'aimant

    // Ajuster le revolution_t si nécessaire
    display_index * index = get_display_index();

    if(index->index < index->max_index){
        revolution_t -= revolution_t / 2;  // ralentir le frame si trop rapide
    } else if(index->overflow){
        revolution_t += revolution_t / 2;  // accélérer le frame si trop lent
    }
}

/* --- Initialisation du capteur Hall --- */
void HALL_init()
{
    // --- TIMER1 free-running 16-bit ---
    TCCR1A = 0;
    TCCR1B = (1 << CS11); // prescaler = 8 → tick = 8/13MHz ≈ 0.615µs

    // --- INT0 sur front montant ---
    EICRA = (1 << ISC01) | (1 << ISC00);
    EIMSK = (1 << INT0);

    sei(); // Activer les interruptions globales
}

/* --- Retourne la durée actuelle d'un tour complet --- */
int get_revolution_t()
{
    return revolution_t;
}

uint16_t get_t_last_zero()
{
    return t_last_zero;
}

/* --- Retourne si on vient de passer devant l'aimant --- */
uint8_t get_known_position()
{
    if (known_position){
        return known_position--;
    }
    return 0;
}
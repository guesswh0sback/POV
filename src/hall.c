#include "hall.h"

/* --- Variables globales --- */
int time_per_frame = 50;           // Durée d'un tour complet en ms (ajustée dynamiquement)
volatile uint8_t known_position = 0;  // Flag pour indiquer passage devant l'aimant
volatile uint16_t t_last_zero = 0;    // Moment exact du dernier passage à l'aimant (Timer1)
static uint16_t current_angle_real = 0; // Angle réel calculé depuis le passage à l'aimant

/* --- ISR pour l'interruption INT0 (capteur Hall) --- */
ISR(INT0_vect)
{
    // Mettre à jour le moment du passage à l'aimant
    t_last_zero = TCNT1;       // TCNT1 = compteur Timer1 16-bit
    current_angle_real = 0;    // Angle réel remis à 0
    known_position = 1;        // Signaler à display_clk que l'on est passé devant l'aimant

    // Ajuster le time_per_frame si nécessaire
    display_index * index = get_display_index();
    if(index->index < index->max_index){
        time_per_frame -= time_per_frame / 2;  // ralentir le frame si trop rapide
    } else if(index->overflow){
        time_per_frame += time_per_frame / 2;  // accélérer le frame si trop lent
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
int get_duration()
{
    return time_per_frame;
}

/* --- Retourne si on vient de passer devant l'aimant --- */
uint8_t get_known_position()
{
    if (known_position){
        known_position = 0; // reset pour la prochaine lecture
        return 1;
    }
    return 0;
}

/* --- Calcul de l'angle réel du rotor en degrés --- */
uint16_t get_current_angle()
{
    // Si on vient de passer devant l'aimant, on est à l'angle 0°
    if (get_known_position()){
        current_angle_real = 0;
        return 0;
    }

    // --- Conversion de la durée du tour complet en ticks ---
    // 1 tick = 0.615 µs → 1 ms ≈ 1626 ticks
    uint32_t ticks_per_frame = (uint32_t)time_per_frame * 1626UL;

    // Temps par degré en ticks
    uint32_t ticks_per_degree = ticks_per_frame / 360UL;

    // Temps écoulé depuis le dernier passage à l'aimant
    uint16_t now = TCNT1;
    uint32_t ticks_elapsed = (uint32_t)now - (uint32_t)t_last_zero;

    // Calcul de l'angle réel
    current_angle_real = (uint16_t)(ticks_elapsed / ticks_per_degree);
    if(current_angle_real >= 360) current_angle_real %= 360;

    return current_angle_real;
}
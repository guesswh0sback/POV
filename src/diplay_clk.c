// #include "display_clk.h"
// #include "driver.h"
// #include "hall.h"
// #include "timer.h"

// /* Pointer to the current time (retrieved from timer module). */
// static time *current_time = NULL;

// uint16_t set_angle(needleType needle, time * current_time) {
//     // Convert time value to angle en considérant que 0 est en haut
//     // On tourne dans le sens horaire (lol on va montrer l'heure à l'envers sinon)
    
//     uint16_t angle;   // le classique, efficace, prolétaire

//     switch (needle) {
//         case NEEDLE_MINUTE:
//             angle = current_time->m/ 6; // 360 degrees / 60 minutes = 6 degrees per minute
//             break;
//         case NEEDLE_HOUR:
//             angle = current_time->h*30; // 360 degrees / 12 hours = 30 degrees per hour
//             angle += current_time->m / 2; // chaque minute ajoute 0.5 degree
//             break;
//         default:
//             // Handle invalid needle type if necessary
//             break;
//     }
//     return angle;
// }

// void display_needle(needleType needle,uint16_t angle, uint16_t frame_duration) {
//     // Affiche l'aiguille à l'angle spécifié

//     // Masque pour l'aiguille
//     uint16_t led_ind = 1 <<

//     // Si l'aiguille est l'heure, elle est longue de 5 leds
//     // Sinon elle est longue de 12 leds

//     switch (needle)
//     {
//     case NEEDLE_HOUR:
//         for (int i = 0; i < 5; i++) {
//             display_bourrin(led_ind, 0.001, frame_duration);
//             led_ind <<= 1; // déplace le masque d'une position vers la gauche
//         }
//         break;
    
//     default:
//         break;
//     }
// }

// void display_clk() {
//     /* update pointer each time in case the timer was initialized later */
//     current_time = get_time();
    
//     if (!current_time) return; /* nothing to display yet */

//     uint16_t minute_angle = set_angle(NEEDLE_MINUTE, current_time);
//     uint16_t hour_angle = set_angle(NEEDLE_HOUR, current_time);

//     int frame_duration = get_duration(); // get duration from hall sensor module
//     // Calculer combien de temps correspond à un degré
//     float time_per_degree = (float)frame_duration / 360.0f;




// }
// #include "display_clk.h"

// // --- Constantes pour les LEDs ---
// static const uint16_t DIAL_MASK     = 0b1000000000000000; // Anneau principal
// static const uint16_t LANDMARK_MASK = 0b0100000000000000; // Repère toutes les heures (30°)
// static const uint16_t WIDEMARK_MASK = 0b0010000000000000; // Repère toutes les 3h (90°)
// static const uint16_t NEEDLE_HOUR_MASK   = 0b0000000000011111; // Aiguille des heures (5 LEDs)
// static const uint16_t NEEDLE_MINUTE_MASK = 0b0000111111111111; // Aiguille des minutes (12 LEDs)

// /* Pointer to the current time (retrieved from timer module). */
// static time *current_time = NULL;

// // --- Masque pour une aiguille ---
// uint16_t get_needle_mask(needleType needle) {
//     return (needle == NEEDLE_HOUR) ? NEEDLE_HOUR_MASK : NEEDLE_MINUTE_MASK;
// }

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

// // --- Masque final du cadran en fonction de l'angle courant ---
// uint16_t compute_final_mask(uint16_t current_angle, uint16_t minute_angle, uint16_t hour_angle) {
//     uint16_t mask = DIAL_MASK; // toujours afficher le cadran

//     // Landmarks : tout sauf aux multiples de 30°
//     if (!ANGLE_EQ(current_angle % 360, 0, 1) &&
//         !ANGLE_EQ(current_angle % 30, 0, 1)) {
//         mask |= LANDMARK_MASK;
//     }

//     // Widemarks : uniquement aux multiples de 90°
//     if (ANGLE_EQ(current_angle % 90, 0, 1)) {
//         mask |= WIDEMARK_MASK;
//     }

//     // Aiguilles
//     if (ANGLE_EQ(current_angle, minute_angle, 2)) {
//         mask |= get_needle_mask(NEEDLE_MINUTE);
//     }
//     if (ANGLE_EQ(current_angle, hour_angle, 2)) {
//         mask |= get_needle_mask(NEEDLE_HOUR);
//     }
//     return mask;
// }

// // --- Fonction principale d'affichage POV ---
// void display_clk() {
//     static uint16_t fake_angle = 0;
//     uint16_t current_angle;

//     // Angle réel si l'interruption Hall a été déclenchée, sinon angle "fake"
//     if (get_known_position()) {
//         current_angle = get_current_angle();
//     } else {
//         current_angle = fake_angle;
//         fake_angle = (fake_angle + 1) % 360;
//     }

//     // Mise à jour du temps
//     current_time = get_time();
//     //if (!current_time) return; // rien à afficher pour l'instant

//     uint16_t minute_angle = set_angle(NEEDLE_MINUTE, current_time);
//     uint16_t hour_angle   = set_angle(NEEDLE_HOUR, current_time);

//     // Calcul du masque final pour cet angle
//     uint16_t final_mask = compute_final_mask(current_angle, minute_angle, hour_angle);

//     // Affichage unique
//     display_bourrin(final_mask, 0, 1); // Là j'ai mis à zéro le temps qu'il se recharge
// }
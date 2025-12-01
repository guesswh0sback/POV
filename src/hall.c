#include "hall.h"

uint8_t buffer[12];
/* --- Variables globales --- */
int time_per_frame = 7500;           // Durée d'un tour complet en us (ajustée dynamiquement)
volatile uint8_t known_position = 0;  // Flag pour indiquer passage devant l'aimant
/* --- ISR pour l'interruption INT0 (capteur Hall) --- */


ISR(INT0_vect)
{
    display_bourrin(0b1111111111111111, 10);
    LEDS_off();
    //INT0_handler();
}

/* --- Initialisation du capteur Hall --- */
void HALL_init()
{   
    // --- INT0 sur front montant ---
    EICRA = (1 << ISC01) | (1 << ISC00);
    EIMSK = (1 << INT0);

    sei(); // Activer les interruptions globales
}



void INT0_handler(){

    display_index * index = get_display_index(); // function from display
    if(index->index < index->max_index & !index->overflow){ // if display did not have the time to parse all the image
        // USART_send_string("inf trigd\r\n"); //debug
        time_per_frame -= (int) time_per_frame*0.01; // lowers the time per frame
    }
    else if(index->overflow){ // if display parsed to rapidly the image
        // USART_send_string("sup trigd\r\n"); //debug
        time_per_frame += (int) time_per_frame*0.01; // increase the time per frame
    }  
    known_position = 1; //if interruption is triggered the position is known    
}

int get_duration(){ // return time_per_frame updated by interrupt handler
/* --- Retourne la durée actuelle d'un tour complet --- */
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

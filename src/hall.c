#include "hall.h"

uint8_t buffer[16];
/* --- Variables globales --- */
int time_for_one_turn = 7500;           // Durée d'un tour complet en us (ajustée dynamiquement)
volatile uint8_t known_position = 0;  // Flag pour indiquer passage devant l'aimant
/* --- ISR pour l'interruption INT0 (capteur Hall) --- */


ISR(INT0_vect)
{
    //test detection hall simple//
    // display_bourrin(0b1111111111111111, 10);
    // LEDS_off();
    // fin test detection hall simple//
    INT0_handler();
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

    if(index->overflow){ // if display parsed to rapidly the image
        time_for_one_turn += (int) time_for_one_turn*0.002; // increase the time per frame
        // USART_send_string("trigd_over\r\n");
    }  

    else if(index->index < index->max_index-1){ // if display did not have the time to parse all the image
        time_for_one_turn -= (int) time_for_one_turn*0.001; // lowers the time per frame
        // USART_send_string("trigd_undr\r\n");
    }
    known_position = 1; //if interruption is triggered the position is known   
}

int get_duration(){ // return time_for_one_turn updated by interrupt handler
/* --- Retourne la durée actuelle d'un tour complet --- */
    return time_for_one_turn;
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

#include "display.h"

float time_compute(uint16_t image[]){
    float total_time = get_total_time();
    return (total_time / (sizeof(image)));
}


void display_image(uint16_t image[], float delay_time){
        for (int i =0; i<sizeof(image)-1; i++){
            display_bourrin(image[i], delay_time, 0.005);
    }
}

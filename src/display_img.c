#include "display_img.h"

uint8_t buffer[12];

display_index * DISPLAY_INDEX = 0;
void set_addr_display_index(display_index * INDEX){
    DISPLAY_INDEX = INDEX;
}

void set_display_index(display_index * INDEX, int max){
    INDEX->index = 0; // reset index to the begining
    INDEX->max_index = max; // set max
    INDEX->overflow = 0; // reset overflow flag
    INDEX->time = get_duration(); // use hall function do set a new time per frame
}

void check_INDEX(display_index * INDEX){
    if (INDEX->index ==  INDEX->max_index) //handles overflow
    {
        INDEX->overflow = 1; // set overflow flag
        INDEX->index = INDEX->max_index -1; // cap index to avoid going out og the image
    }
    if (get_known_position()) // back to a position where the image can begin anew
    {
        set_display_index(INDEX, INDEX->max_index);
    }
}

void display_image(uint16_t *image, display_index * INDEX){
    while (1) // equivalent to a while true because of check_index
    {
        check_INDEX(INDEX);
        snprintf(buffer, 12, "tpf:%d\n\r", INDEX->time);
        USART_send_string(buffer);
        display_bourrin(image[INDEX->index], (int)(INDEX->time/INDEX->max_index)); // display current frame
        for (int i = 0; i < INDEX->time; i++)
        {
            _delay_us(1);
        }
        
        INDEX->index ++;
        }  
}

display_index * get_display_index(){ // used for hall functions
    return DISPLAY_INDEX;
}

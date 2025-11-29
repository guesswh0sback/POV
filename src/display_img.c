#include "display_img.h"

display_index * DISPLAY_INDEX;


void set_display_index(display_index * INDEX, int max){
    INDEX->index = 0; // reset index to the begining
    INDEX->max_index = max; // set max
    INDEX->overflow = 0; // reset overflow flag
    //INDEX->time = get_time(); // use hall function do set a new time per frame
}

void check_INDEX(display_index * INDEX){
    if (INDEX->max_index<INDEX->index) //handles overflow
    {
        INDEX->overflow = 1; // set overflow flag
        INDEX->index = INDEX->max_index; // cap index to avoid going out og the image
    }
    if (get_known_position) // back to a position where the image can begin anew
    {
        set_display_index(INDEX, INDEX->max_index);
    }
    
    
}

void display_image(uint16_t image[], display_index * INDEX){
    while (!INDEX->overflow) // equivalent to a while true because of check_index
    {
        check_INDEX(INDEX);
        display_bourrin(image[INDEX->index], 0.0005, INDEX->time); // display current frame
        INDEX->index ++;
    }  
}

display_index * get_display_index(){ // used for hall functions
    return DISPLAY_INDEX;
}

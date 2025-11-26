#include <avr/io.h>
#include <util/delay.h>

#include "../src/display_clk.h"

int main(void) {
        SPI_init();
    while (1)
    {  
        display_clk();
    }
    return(0);
}
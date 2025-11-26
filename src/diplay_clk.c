#include "display_clk.h"
#include "driver.h"
#include "hall.h"

typedef enum {
    NEEDLE_MINUTE,
    NEEDLE_HOUR
} needleType;

void display_clk(needleType needle, int angle) {
    switch (needle) {
        case NEEDLE_HOUR:
            break;
        case NEEDLE_MINUTE:
            break;
        default:
            // Handle invalid needle type if necessary
            break;
    }
    
}
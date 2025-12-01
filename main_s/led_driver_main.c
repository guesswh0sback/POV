#include <avr/io.h>
#include <util/delay.h>

#include "../src/driver.h"

uint16_t A = 0b1000000000000000;
uint16_t B = 0b0100000000000000;
uint16_t C = 0b0010000000000000;
uint16_t D = 0b0001000000000000;
uint16_t E = 0b0000100000000000;
uint16_t F = 0b0000010000000000;
uint16_t G = 0b0000001000000000;
uint16_t H = 0b0000000100000000;
uint16_t I = 0b0000000010000000;
uint16_t J = 0b0000000001000000;
uint16_t K = 0b0000000000100000;
uint16_t L = 0b0000000000010000;
uint16_t M = 0b0000000000001000;
uint16_t N = 0b0000000000000100;
uint16_t O = 0b0000000000000010;
uint16_t P = 0b0000000000000001;


int main(void) {
        SPI_init();
    while (1)
    {  
        display_bourrin(A, 10000);
        display_bourrin(B, 10000);
        display_bourrin(C, 10000);
        display_bourrin(D, 10000);
        display_bourrin(E, 10000);
        display_bourrin(F, 10000);
        display_bourrin(G, 10000);
        display_bourrin(H, 10000);
        display_bourrin(I, 10000);
        display_bourrin(J, 10000);
        display_bourrin(K, 10000);
        display_bourrin(L, 10000);
        display_bourrin(M, 10000);
        display_bourrin(N, 10000);
        display_bourrin(O, 10000);
        display_bourrin(P, 10000);

    }

    return(0);
    
}

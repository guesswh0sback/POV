#include "../src/uart_basic.h"
#include "../src/driver.h"
#define BAUDRATE 38400

int main(void){

    // Setup Bluetooth module
    USART_Init(BAUDRATE);
    SPI_init();
    while(1){
        // Main loop
        uart_send_string("Hello World\n\r");
        display_bourrin(0xFFFF, 0.01, 100);
        _delay_ms(1000);

    }
}
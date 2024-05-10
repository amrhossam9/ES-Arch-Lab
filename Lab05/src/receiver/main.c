#include <avr/io.h>
#include <util/delay.h>
#include "STD/STD_MATH.h"
#include "STD/STD_TYPES.h"
#include "DIO/DIO_INTERFACE.h"
#include "LCD/LCD_INTERFACE.h"

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void UART_Init(unsigned int ubrr) {
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    UCSRB = (1 << RXEN) | (1 << TXEN);   // Enable receiver and transmitter
    UCSRC = (1 << URSEL) | (3 << UCSZ0); // Set frame format: 8data, 1stop bit
}

unsigned char UART_Receive() {
    while (!(UCSRA & (1 << RXC))); // Wait for data to be received
    return UDR;                     // Get and return received data from buffer
}



int main() {
    UART_Init(MYUBRR); // Initialize UART       // Initialize LCD
    LCD_init();
    while (1) {
      //LCD_clear();
        char received_data = UART_Receive(); // Receive data through UART
        LCD_moveCursor(0,0);
        LCD_sendData(received_data);   // Display received data on LCD
    }

    return 0;
}

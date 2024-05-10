#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 160000-00UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

volatile char x = 0x41; // Global variable

void UART_Init(unsigned int ubrr) {
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    UCSRB = (1 << RXEN) | (1 << TXEN);   // Enable receiver and transmitter
    UCSRC = (1 << URSEL) | (3 << UCSZ0); // Set frame format: 8data, 1stop bit
}

void UART_Transmit(unsigned char data) {
    while (!(UCSRA & (1 << UDRE))); // Wait for empty transmit buffer
    UDR = data;                      // Put data into buffer, sends the data
}

ISR(INT0_vect) {
    x++; // Increment x
    if (x == 0x7a) {
        x = 0x41; // Reset x if it reaches 0x7a
    }
    UART_Transmit(x);
}

void INT0_Init() {
    DDRD &= ~(1 << PD2); // Set INT0/PD2 pin as input
    PORTD |= (1 << PD2); // Enable internal pull-up resistor
    GICR |= (1 << INT0); // Enable external interrupt INT0
    MCUCR |= (1 << ISC01) | (1 << ISC00); // Trigger INT0 on rising edge
}

int main() {
    UART_Init(MYUBRR); // Initialize UART
    INT0_Init();       // Initialize INT0

    sei(); // Enable global interrupts

    while (1) {
        // Main program loop
    }

    return 0;
}

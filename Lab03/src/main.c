#include <avr/io.h>
#include <avr/interrupt.h>
#include "STD/STD_TYPES.h"
#include "STD/STD_MATH.h"
#include "DIO/DIO_INTERFACE.h"
#include "LCD/LCD_INTERFACE.h"
#include <stdio.h>
#include <util/delay.h>

volatile uint16_t adc_value; // Global variable to store ADC value

// Interrupt Service Routine for external interrupt INT0
ISR(INT0_vect) {
    // Start ADC conversion
    ADCSRA |= (1 << ADSC);   
    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));  
    // Read ADC value
    adc_value = ADC;
    // Clear LCD screen
    LCD_clear();
    // Display ADC value on the first line of LCD screen
    char adc_string[6];
    sprintf(adc_string, "%u", adc_value);
    LCD_sendStringCursor(0, 0, adc_string);
    // Wait for 2 seconds
    _delay_ms(2000);
}

int main() {
    // Configure PD2 (INT0) as input
    setPinDirection(PORTD, PIN2, Input);
    // Enable internal pull-up resistor for PD2
    setPinValue(PORTD, PIN2, PinHigh);
    // Configure INT0 for rising edge triggering
    MCUCR |= (1 << ISC00) | (1 << ISC01);
    // Enable INT0 external interrupt
    GICR |= (1 << INT0);
    // Enable global interrupts
    sei();
    // Configure ADC
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC and set ADC prescaler to 128
    ADMUX |= (1 << REFS0); // Select AVCC as reference voltage
    // Initialize LCD
    LCD_init();
    // Set up main loop
    char *Word = "Hello!";
    for (;;) {
        // Moves "hello" 5 positions from left to right
        for(uint8_t i = 0; i < 5; i++){
            LCD_sendStringCursor(0, i, Word);
            _delay_ms(1000);
            LCD_clear();
        }
        // Moves "hello" 5 positions from right to left
        for(uint8_t i = 5; i > 0; i--){
            LCD_sendStringCursor(0, i, Word);
            _delay_ms(1000);
            LCD_clear();
        }
    }

    return 0;
}

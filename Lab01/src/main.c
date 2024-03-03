#include "STD/STD_TYPES.h"
#include "STD/STD_MATH.h"
#include "DIO/DIO_INTERFACE.h"
#include <stdio.h>
#include <util/delay.h>

int SEVEN_SEGMENT[10] = {126,12,182,158,204,218,250,14,254,222};

int main() {
    // Set PC6 and PC7 direction to output for seven-segment display
    setPinDirection(Port_C, 6, Output);
    setPinDirection(Port_C, 7, Output);
    // Enable seven-segment display
    setPinValue(Port_C, 6, PinHigh);
    setPinValue(Port_C, 7, PinHigh);
    // Set PD2 and PD3 direction to input for buttons
    setPinDirection(Port_D, 2, Input);
    setPinDirection(Port_D, 3, Input);
    // Set PortA direction to output for seven-segment output
    setPortDirection(Port_A, Output);
    // Store the index of the digit
    uint8 currentDigit = 0, secondaryDigit = 0;
    // Indicates pressed state to avoid debouncing
    uint8 pressed[2] = {0};

    for(;;){
        if (!(getPinValue(Port_D, 2))) {
            _delay_ms(30);
            if (!(getPinValue(Port_D, 2))) {
              if(!pressed[0]) {
                if(currentDigit != 9) {
                  currentDigit++;
                }
                else if(secondaryDigit != 9) {
                  secondaryDigit++;
                  currentDigit = 0;
                }
                pressed[0] = 1;
              }
            }
            else {
                pressed[0] = 0;
            }
        }
        
        if (!(getPinValue(Port_D, 3))) {
            _delay_ms(30);
            if (!(getPinValue(Port_D, 3))) {
              if(!pressed[1]){
                if(currentDigit != 0) {
                  currentDigit--;
                }
                else if(secondaryDigit != 0) {
                  currentDigit = 9;
                  secondaryDigit--;
                }
                pressed[1] = 1;
              }
            }
            else {
                pressed[1] = 0;
            }
        }

        if (!(getPinValue(Port_D, 4))){
            _delay_ms(30);
            if (!(getPinValue(Port_D, 4))) {
              if(!pressed[1]){
                currentDigit = 0; secondaryDigit = 0;
                pressed[1] = 1;
              }
            }
            else {
                pressed[1] = 0;
            }
        }

        // Set PC6 to high and PC7 to low
        setPinValue(Port_C, 6, PinHigh);
        setPinValue(Port_C, 7, PinLow);
        // Update PORTA using sevenSeg[currentDigit]
        setPortValue(Port_A, SEVEN_SEGMENT[currentDigit]);
        // Delay for 1000 microseconds
        _delay_us(1000);
        // Set PC6 to low and PC7 to high
        setPinValue(Port_C, 6, PinLow);
        setPinValue(Port_C, 7, PinHigh);
        // Update PORTA using sevenSeg[secondaryDigit]
        setPortValue(Port_A, SEVEN_SEGMENT[secondaryDigit]);
        // Delay for 1000 microseconds
        _delay_us(1000);

    }

    return 0;
}

#include "./STD/STD_TYPES.h"
#include "./STD/STD_MATH.h"
#include "./DIO/DIO_INTERFACE.h"
#include "DHT11_INTERFACE.h"
#include <util/delay.h>

uint8 c = 0;
// Function to send start pulse to DHT11 sensor
void Request() {
    setPinDirection(Port_C, DHT11_PIN, Output);
    setPinValue(Port_C, DHT11_PIN, PinLow); // Set pin to low
    _delay_ms(20); // Wait for 20ms
    setPinValue(Port_C, DHT11_PIN, PinHigh); // Set pin to high
}

// Function to receive response from DHT11 sensor
void Response() {
    setPinDirection(Port_C, DHT11_PIN, Input);
    while (readPinValue(Port_C, DHT11_PIN)); // Wait for sensor to respond
    while (!readPinValue(Port_C, DHT11_PIN)); // Wait for sensor to finish response
    while (readPinValue(Port_C, DHT11_PIN)); // Wait for sensor to finish response
}

// Function to receive data from DHT11 sensor
uint8 Receive_data() {
    for (int q = 0; q < 8; q++) {
        while (!readPinValue(Port_C, DHT11_PIN)); // Wait for bit reception
        _delay_us(30);
        if (readPinValue(Port_C, DHT11_PIN)) // Check if received bit is high
            c = (c << 1) | (0x01); // Logic high
        else
            c = (c << 1); // Logic low
        while (readPinValue(Port_C, DHT11_PIN)); // Wait for bit reception to finish
    }
    return c;
}

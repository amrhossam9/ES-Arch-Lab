#include "STD/STD_TYPES.h"
#include "STD/STD_MATH.h"
#include "DIO/DIO_INTERFACE.h"
#include "ADC/adc.h"
#include "UART/UART_INTERFACE.h"
#include "SERVO/SERVO_INTERFACE.h"
#include "DHT11/DHT11_INTERFACE.h"
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#define FLAME_CHANNEL 0
#define GAS_CHANNEL 1
#define LDR_CHANNEL 2
#define MOISTURE_CHANNEL 3
#define DHT11_PIN 2



// Global variables
uint8 I_RH, A_RH, I_Temp, A_Temp, CheckSum;
int temp;
int humi;

// Function to read flame sensor
int FLAME() {
    int val = ADC_readChannel(FLAME_CHANNEL);
    setPinDirection(Port_C, Pin5, Output);
    if (val < 900) {
        setPinValue(Port_C, Pin5, PinHigh);
        SERVO_setDegree(180);
        return 1;
    } else {
        setPinValue(Port_C, Pin5, PinLow);
        SERVO_setDegree(0);
        return 0;
    }
    return val;
}

// Function to read light sensor (LDR)
int LDR() {
    int val = ADC_readChannel(LDR_CHANNEL);
    float perc = ((val * 1.0) / 1023 * 1.0) * 100 * 1.0;
    return (int)perc;
}

// Function to read gas sensor
int GAS() {
    int val = ADC_readChannel(GAS_CHANNEL);
    setPinDirection(Port_C, Pin5, Output);
    if (val > 500) {
        setPinValue(Port_C, Pin5, PinHigh);
        return 1;
    } else {
        setPinValue(Port_C, Pin5, PinLow);
        return 0;
    }
    return val;
}

// Function to read moisture sensor
int MOISTURE() {
    int val = ADC_readChannel(MOISTURE_CHANNEL);
    float perc = 100 - (val * 100.00) / 1023.00;
    return (int)perc;
}

// Function to read temperature and humidity from DHT11 sensor
void TEMP() {
    Request();               // Send start pulse
    Response();              // Receive response
    I_RH = Receive_data();   // Store first eight bits in I_RH
    A_RH = Receive_data();   // Store next eight bits in A_RH
    I_Temp = Receive_data(); // Store next eight bits in I_Temp
    A_Temp = Receive_data(); // Store next eight bits in A_Temp
    CheckSum = Receive_data(); // Store next eight bits in CheckSum
    if ((I_RH + A_RH + I_Temp + A_Temp) != CheckSum) {
        temp = 0;
        humi = 0;
    } else {
        humi = (int)I_RH;
        temp = (int)I_Temp;
    }
}



int main(void) {
    char at[100];
    ADC_init();
    UART_init(103);
    SERVO_init();
    for (;;) {
        int flame = FLAME();
        TEMP();
        int moisture = MOISTURE();
        int gas = GAS();
        int ldr = LDR();

        sprintf(at, "*%d,%d,%d,%d,%d,%d#", temp, humi, flame, moisture, gas, ldr);
        for (int i = 0; i < sizeof(at); i++) {
            UART_sendData(at[i]);
            _delay_ms(5);
        }
    }

    return 0;
}


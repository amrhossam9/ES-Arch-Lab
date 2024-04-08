#include "./STD/STD_TYPES.h"
#include "./STD/STD_MATH.h"
#include "DIO_PRIVATE.h"
#include "DIO_INTERFACE.h"

void setPinDirection(uint8 Port, uint8 Pin, uint8 Direction){
    volatile uint8 *ddr_reg;

    switch (Port) {
        case Port_A:
            ddr_reg = &DDRA;
            break;
        case Port_B:
            ddr_reg = &DDRB;
            break;
        case Port_C:
            ddr_reg = &DDRC;
            break;
        case Port_D:
            ddr_reg = &DDRD;
            break;
        default:
            return;
    }

    if (Direction == Input) {
        CLEAR_BIT(*ddr_reg, Pin);
    } else {
        SET_BIT(*ddr_reg, Pin);
    }
}

void setPinValue(uint8 Port, uint8 Pin, uint8 Value){
    volatile uint8 *port_reg;

    switch (Port) {
        case Port_A:
            port_reg = &PORTA;
            break;
        case Port_B:
            port_reg = &PORTB;
            break;
        case Port_C:
            port_reg = &PORTC;
            break;
        case Port_D:
            port_reg = &PORTD;
            break;
        default:
            return;
    }

    if (Value == PinHigh) {
        SET_BIT(*port_reg, Pin);
    } else {
        CLEAR_BIT(*port_reg, Pin);
    }
}

void getPinValue(uint8 Port, uint8 Pin, uint8 *Value){
    volatile uint8 *pin_reg;

    switch (Port) {
        case Port_A:
            pin_reg = &PINA;
            break;
        case Port_B:
            pin_reg = &PINB;
            break;
        case Port_C:
            pin_reg = &PINC;
            break;
        case Port_D:
            pin_reg = &PIND;
            break;
        default:
            return;
    }

    *Value = GET_BIT(*pin_reg, Pin);
}


void setPortDirection(uint8 Port, uint8 Direction){
    volatile uint8 *ddr_reg;

    switch (Port) {
        case Port_A:
            ddr_reg = &DDRA;
            break;
        case Port_B:
            ddr_reg = &DDRB;
            break;
        case Port_C:
            ddr_reg = &DDRC;
            break;
        case Port_D:
            ddr_reg = &DDRD;
            break;
        default:
            return;
    }

    if (Direction == Input) {
        *ddr_reg = 0x00;
    } else {
        *ddr_reg = 0xff;
    }
}


void setPortValue(uint8 Port, uint8 Value){

    switch (Port) {
        case Port_A:
            PORTA = Value;
            break;
        case Port_B:
            PORTB = Value;
            break;
        case Port_C:
            PORTC = Value;
            break;
        case Port_D:
            PORTD = Value;
            break;
        default:
            return;
    }

}



void getPortValue(uint8 Port, uint8 *Value){
    volatile uint8 *pin_reg;

    switch (Port) {
        case Port_A:
            pin_reg = &PINA;
            break;
        case Port_B:
            pin_reg = &PINB;
            break;
        case Port_C:
            pin_reg = &PINC;
            break;
        case Port_D:
            pin_reg = &PIND;
            break;
        default:
            return;
    }

    *Value = *pin_reg;
}
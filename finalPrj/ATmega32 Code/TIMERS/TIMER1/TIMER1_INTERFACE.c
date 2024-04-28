#include "../../STD/STD_TYPES.h"
#include "../../STD/STD_MATH.h"
#include "../../DIO/DIO_INTERFACE.h"
#include "TIMER1_PRIVATE.h"
#include "TIMER1_INTERFACE.h"
#include <stddef.h>

void TIMER1_init(et_TIMER1MODE mode, et_TIMER1PRESCALER prescaler) {
    // Set the mode in TCCR1A and TCCR1B registers based on the 'mode' argument
    switch (mode) {
        case TIMER1_NORMAL_MODE:
            CLEAR_BIT(TCCR1A, TCCR1A_WGM10);
            CLEAR_BIT(TCCR1A, TCCR1A_WGM11);
            CLEAR_BIT(TCCR1B, TCCR1B_WGM12);
            CLEAR_BIT(TCCR1B, TCCR1B_WGM13);
            break;

        case TIMER1_CTC_MODE:
            // Configure for CTC mode, you need to set the WGM12 bit in TCCR1B
            CLEAR_BIT(TCCR1A, TCCR1A_WGM10);
            CLEAR_BIT(TCCR1A, TCCR1A_WGM11);
            SET_BIT(TCCR1B, TCCR1B_WGM12);
            CLEAR_BIT(TCCR1B, TCCR1B_WGM13);
            break;

        case TIMER1_FASTPWM_MODE:
            // Configure for Fast PWM mode, set both WGM11 and WGM12 bits in TCCR1A and WGM13 bit in TCCR1B
            CLEAR_BIT(TCCR1A, TCCR1A_WGM10);
            SET_BIT(TCCR1A, TCCR1A_WGM11);
            SET_BIT(TCCR1B, TCCR1B_WGM12);
            SET_BIT(TCCR1B, TCCR1B_WGM13);
            break;
    }

    // Set the prescaler in TCCR1B register based on the 'prescaler' argument
    TCCR1B |= prescaler;
}

void TIMER1_setPWMMode(ed_TIMER1PWM pwmMode) {
    // Configure PWM mode based on the 'pwmMode' argument
    switch (pwmMode) {
        case TIMER1_inverted:
            SET_BIT(TCCR1A, TCCR1A_COM1A1);
            SET_BIT(TCCR1A, TCCR1A_COM1A0);
            SET_BIT(TCCR1A, TCCR1A_COM1B1);
            SET_BIT(TCCR1A, TCCR1A_COM1B0);
            break;
        case TIMER1_non_inverted:
            SET_BIT(TCCR1A, TCCR1A_COM1A1);
            CLEAR_BIT(TCCR1A, TCCR1A_COM1A0);
            SET_BIT(TCCR1A, TCCR1A_COM1B1);
            CLEAR_BIT(TCCR1A, TCCR1A_COM1B0);
            break;
    }
}

void TIMER1_setValue(uint16 value){
    TCNT1 = value;
}
uint16 TIMER1_readValue(){
    return TCNT1;
}

void TIMER1_setCompareValue(uint16 value){

    OCR1A = value;
}
void TIMER1_DUTYCYCLE(uint8 dutyCycle)
{
    uint16 compVal = (uint16)(((uint32)(dutyCycle * 65535)) / 100);
    TIMER1_setCompareValue(compVal);
}

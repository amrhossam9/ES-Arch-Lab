#include "../STD/STD_TYPES.h"
#include "../STD/STD_MATH.h"
#include "../DIO/DIO_INTERFACE.h"
#include "../TIMERS/TIMER1/TIMER1_INTERFACE.h"
#include "../TIMERS/TIMER1/TIMER1_PRIVATE.h"

void SERVO_init() {
    // Configure TIMER1 for Fast PWM mode with non-inverted PWM
    TIMER1_init(TIMER1_FASTPWM_MODE, TIMER1_CLK_64_PRESCALER);
    TIMER1_setPWMMode(TIMER1_non_inverted);
    // Set ICR1 for 50Hz frequency (20ms period)
    ICR1 = 4999;
    
    // Set PWM Pins (OC1A and OC1B) as output
	setPinDirection(Port_D, Pin4, Output);
	setPinDirection(Port_D, Pin5, Output);
}

void SERVO_setDegree(int d) {
    // Set the PWM value to OCR1A
    TIMER1_setCompareValue(160 + ((22 * d) / 9));
}




#ifndef TIMER1_PRIVATE_H
#define TIMER1_PRIVATE_H

#define TCCR1A      *((volatile uint8*) 0x4F)
#define TCCR1B      *((volatile uint8*) 0x4E)

#define TCNT1L      *((volatile uint8*) 0x4C)
#define TCNT1H      *((volatile uint8*) 0x4D)

#define OCR1A       *((volatile uint16*) 0x4A)
#define OCR1B       *((volatile uint16*) 0x48)

#define ICR1        *((volatile uint16*) 0x46)

#define TCCR1       *((volatile uint8*) 0x45)
#define TCNT1       *((volatile uint16*) 0x44)

#define OCR2        *((volatile uint8*) 0x43)

#define TIMSK       *((volatile uint8*) 0x59)

/* MODE */
#define TCCR1A_WGM10 0
#define TCCR1A_WGM11 1

#define TCCR1B_WGM12 3
#define TCCR1B_WGM13 4

/* PRESCALER */
#define TCCR1B_CS10 0
#define TCCR1B_CS11 1
#define TCCR1B_CS12 2

/* PWM OCR1A and OCR1B OUTPUT */
#define TCCR1A_COM1A1 7
#define TCCR1A_COM1A0 6
#define TCCR1A_COM1B1 5
#define TCCR1A_COM1B0 4

/* INTERRUPT PINS */
#define TIMSK_OCIE0 1
#define TIMSK_TOIE0 0

#endif /* TIMER1_PRIVATE_H */

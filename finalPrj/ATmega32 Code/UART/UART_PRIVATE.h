#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H


#define UDR         *((volatile uint8*) 0x2C)
#define UCSRA       *((volatile uint8*) 0x2B)
#define UCSRB       *((volatile uint8*) 0x2A)
#define UCSRC       *((volatile uint8*) 0x40)
#define UBRRL       *((volatile uint8*) 0x29)
#define UBRRH       *((volatile uint8*) 0x40)


#define MPCM        0
#define U2X         1
#define PE          2
#define DOR         3
#define FE          4
#define UDRE        5
#define TXC         6
#define RXC         7


#define UDRIE       5
#define TXCIE       6
#define RXCIE       7

#define UCSZ0       1
#define UCSZ1       2
#define URSEL       7

#define RXEN        4
#define TXEN        3




#endif /*UART_PRIVATE_H*/

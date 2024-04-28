#include "../STD/STD_TYPES.h"
#include "../STD/STD_MATH.h"
#include "../DIO/DIO_INTERFACE.h"
#include "UART_PRIVATE.h"
#include "UART_INTERFACE.h"
#include <stddef.h>

static UART_Callback UARTCallback = NULL;

void UART_init(uint32 UBR_value){

    //uint16 UBR_value = (F_CPU/ (16*(baudRate))) -1;
	UBRRH = (uint8)(UBR_value>>8);
	UBRRL = (uint8)UBR_value;
    UCSRB |= (1<<RXEN) | (1<<TXEN) | (1<<RXCIE) | (1<<TXCIE);
    
    UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);

}

void UART_sendData(uint8 data){
    while(!GET_BIT(UCSRA, UDRE));
    UDR = data;
}

uint8 UART_receiveData(){
    while (!GET_BIT(UCSRA, RXC));
    return UDR;
}

void UART_setCallBack(UART_Callback callback){
    UARTCallback = callback;
}

void __vector_13(void) __attribute__((signal, used));
void __vector_13(void) {
    if (UARTCallback != NULL) {
        UARTCallback(UDR);
    }
}

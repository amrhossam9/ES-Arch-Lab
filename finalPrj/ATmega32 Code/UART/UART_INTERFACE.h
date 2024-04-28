#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H




typedef void (*UART_Callback)(uint8);


void UART_init(uint32 UBR_value);
void UART_sendData(uint8 data);
uint8 UART_receiveData();
void UART_setCallBack(UART_Callback callback);

#endif /* UART_INTERFACE_H */


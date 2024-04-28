#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H


typedef enum{
    Port_A,
    Port_B,
    Port_C,
    Port_D
}et_Port;

typedef enum{
    Pin0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7
}et_Pin;

typedef enum{
    Input,
    Output
}et_Direction;

typedef enum{
    PinLow,
    PinHigh
}et_Status;


void setPinDirection(uint8 Port, uint8 Pin, uint8 Direction);


void setPinValue(uint8 Port, uint8 Pin, uint8 Value);


void getPinValue(uint8 Port, uint8 Pin, uint8 *Value);


void setPortDirection(uint8 Port, uint8 Direction);


void setPortValue(uint8 Port, uint8 Value);


void getPortValue(uint8 Port, uint8 *Value);


uint8 readPinValue(uint8 Port, uint8 Pin);
#endif /*DIO_INTERFACE_H*/
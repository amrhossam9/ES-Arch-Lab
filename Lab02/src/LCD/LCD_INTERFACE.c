#include "./STD/STD_TYPES.h"
#include "./STD/STD_MATH.h"
#include "./DIO/DIO_INTERFACE.h"
#include "LCD_CONFIG.h"
#include "LCD_INTERFACE.h"
#include <stdio.h>
#include <util/delay.h>

uint8 col, row;


void LCD_init(){

    /*Configure RS and E as OUTPUT*/
    setPinDirection(LCD_RS_PORT, LCD_RS_PIN, Output);
    setPinDirection(LCD_E_PORT, LCD_E_PIN, Output);
    _delay_ms(20);
    col = 0;
    row = 0;
    #if(LCD_MODE == 8)

    /*Configure DATA_PORT as OUTPUT*/
    setPortDirection(LCD_DATA_PORT, Output);
    /*LCD ON DELAY*/
    _delay_ms(20);
    /*Configure EIGHT BIT MODE - 2Lines - 5X8*/
    LCD_sendCommand(LCD_EIGHT_BIT_MODE_TWO_LINES);
    /*Enable - No cursor*/
    LCD_sendCommand(LCD_CURSOR_OFF);
    /*Clear*/
    LCD_sendCommand(LCD_CLEAR);

    #elif(LCD_MODE == 4)

    /*Configure DATA_PINS as OUTPUT*/
    setPinDirection(LCD_DATA_PORT, LCD_DATA_PIN0, Output);
    setPinDirection(LCD_DATA_PORT, LCD_DATA_PIN1, Output);
    setPinDirection(LCD_DATA_PORT, LCD_DATA_PIN2, Output);
    setPinDirection(LCD_DATA_PORT, LCD_DATA_PIN3, Output);
    /*LCD ON DELAY*/
    _delay_ms(20);
    /*Configure FOUR BIT MODE*/
    LCD_sendCommand(LCD_FOUR_BIT_MODE_S1);
    LCD_sendCommand(LCD_FOUR_BIT_MODE_S2);
    /*Configure FOUR BIT MODE - 2Lines - 5X8*/
    LCD_sendCommand(LCD_FOUR_BIT_MODE_TWO_LINES);
    /*Enable - No cursor*/
    LCD_sendCommand(LCD_CURSOR_OFF);
    /*Clear*/
    LCD_sendCommand(LCD_CLEAR);

    #endif

}

void LCD_sendCommand(uint8 CMD){

    /*RS LOW TO SEND COMMAND*/
    setPinValue(LCD_RS_PORT, LCD_RS_PIN, PinLow);
    _delay_ms(1);

    #if(LCD_MODE == 8)

    /*ENABLE PULSE*/
    setPinValue(LCD_E_PORT, LCD_E_PIN, PinHigh);
    _delay_ms(1);
    
    /*SET DATA_PORT VALUE TO THE CMD*/
    setPortValue(LCD_DATA_PORT, CMD);
    _delay_ms(1);

    setPinValue(LCD_E_PORT, LCD_E_PIN, PinLow);
    _delay_ms(1);

    #elif(LCD_MODE == 4)

    /*ENABLE PULSE*/
    setPinValue(LCD_E_PORT, LCD_E_PIN, PinHigh);
    _delay_ms(1);

    /*SET the FOUR MSBs of CMD*/
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, GET_BIT(CMD, 4));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, GET_BIT(CMD, 5));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, GET_BIT(CMD, 6));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, GET_BIT(CMD, 7));
    _delay_ms(1);

    setPinValue(LCD_E_PORT, LCD_E_PIN, PinLow);
    _delay_ms(1);

    /*ENABLE PULSE*/
    setPinValue(LCD_E_PORT, LCD_E_PIN, PinHigh);
    _delay_ms(1);

    /*SET the FOUR LSBs of CMD*/
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, GET_BIT(CMD, 0));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, GET_BIT(CMD, 1));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, GET_BIT(CMD, 2));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, GET_BIT(CMD, 3));
    _delay_ms(1);

    setPinValue(LCD_E_PORT, LCD_E_PIN, PinLow);
    _delay_ms(1);

    #endif

}


void LCD_sendData(uint8 Data){

    /*RS LOW TO SEND DATA*/
    setPinValue(LCD_RS_PORT, LCD_RS_PIN, PinHigh);
    _delay_ms(1);

    #if(LCD_MODE == 8)

    /*ENABLE PULSE*/
    setPinValue(LCD_E_PORT, LCD_E_PIN, PinHigh);
    _delay_ms(1);
    
    /*SET DATA_PORT VALUE TO THE DATA*/
    setPortValue(LCD_DATA_PORT, Data);
    _delay_ms(1);

    setPinValue(LCD_E_PORT, LCD_E_PIN, PinLow);
    _delay_ms(1);

    #elif(LCD_MODE == 4)

    /*ENABLE PULSE*/
    setPinValue(LCD_E_PORT, LCD_E_PIN, PinHigh);
    _delay_ms(1);

    /*SET the FOUR MSBs of DATA*/
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, GET_BIT(Data, 4));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, GET_BIT(Data, 5));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, GET_BIT(Data, 6));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, GET_BIT(Data, 7));
    _delay_ms(1);

    setPinValue(LCD_E_PORT, LCD_E_PIN, PinLow);
    _delay_ms(1);

    /*ENABLE PULSE*/
    setPinValue(LCD_E_PORT, LCD_E_PIN, PinHigh);
    _delay_ms(1);

    /*SET the FOUR LSBs of DATA*/
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN0, GET_BIT(Data, 0));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN1, GET_BIT(Data, 1));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN2, GET_BIT(Data, 2));
    setPinValue(LCD_DATA_PORT, LCD_DATA_PIN3, GET_BIT(Data, 3));
    _delay_ms(1);

    setPinValue(LCD_E_PORT, LCD_E_PIN, PinLow);
    _delay_ms(1);

    #endif

}

void LCD_sendDataWithAutoLineWrap(uint8 Data) {
    /*Check if the cursor is at the end of the current row*/
    if (col >= 16) {
        /*Move to the next row*/
        LCD_moveCursor(row ^ 1, 0);
        col = 0;
        row ^= 1;
    }
    /*Send the data to the current cursor position*/
    LCD_sendData(Data);
    col++;
}
void LCD_sendString(char* str){

    /*Print CHARACTERS until end of String*/
    for (uint8 i = 0; str[i] != '\0'; i++){
        LCD_sendData(str[i]);
    }

}

void LCD_sendStringWithAutoLineWrap(char* str){

    /*Print CHARACTERS until end of String*/
    for (uint8 i = 0; str[i] != '\0'; i++){
        LCD_sendDataWithAutoLineWrap(str[i]);
    }

}

void LCD_sendInt(int Data){
    
    /*Array to represent the int as String*/
    char integer[16];
    /*Convert*/
    sprintf(integer, "%d", Data);
    /*Send the String*/
    LCD_sendString(integer);

}

void LCD_moveCursor(uint8 row, uint8 col){

    /*Calculate the Position*/
    uint8 pos = (row == 0) ? (0x00 + col) : (row == 1) ? (0x40 + col) : 0x00; 
    /*Set the cursor Command*/
    LCD_sendCommand(pos|LCD_FORCE_START_LOCATION);

}

void LCD_sendStringCursor(uint8 row, uint8 col, char* str){

    /*Move Cursor*/
    LCD_moveCursor(row, col);
    /*Send String*/
    LCD_sendString(str);

}

void LCD_clear(){

    /*Send Clear Command*/
    LCD_sendCommand(LCD_CLEAR);

}

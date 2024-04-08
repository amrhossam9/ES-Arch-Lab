#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H




void LCD_init();

void LCD_sendCommand(uint8 CMD);

void LCD_sendData(uint8 Data);

void LCD_sendDataWithAutoLineWrap(uint8 Data);

void LCD_sendString(char* str);

void LCD_sendStringWithAutoLineWrap(char* str);

void LCD_sendInt(int Data);

void LCD_moveCursor(uint8 row, uint8 col);

void LCD_sendStringCursor(uint8 row, uint8 col, char* str);


void LCD_clear();



#endif /*LCD_INTERFACE_H*/
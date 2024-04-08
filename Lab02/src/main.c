#include "STD/STD_TYPES.h"
#include "STD/STD_MATH.h"
#include "DIO/DIO_INTERFACE.h"
#include "LCD/LCD_INTERFACE.h"
#include <stdio.h>
#include <util/delay.h>

int main(){
  LCD_init();
  char *Word = "Hello";
  for(;;){
    // Moves "hello" 5 positions from left to right
    for(uint8 i = 0; i < 5; i++){
      LCD_sendStringCursor(0, i, Word);
      _delay_ms(1000);
      LCD_clear();
    }
    // Moves "hello" 5 positions from right to left
    for(uint8 i = 5; i > 0; i--){
      LCD_sendStringCursor(0, i, Word);
      _delay_ms(1000);
      LCD_clear();
    }
  }
}
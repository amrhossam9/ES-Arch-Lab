/*
 * main1.c
 *
 *  Created on: Apr 29, 2024
 *      Author: abdul
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "spi.h"
#include "lcd.h"

//#define SPI_DEFAULT_DATA_VALUE 0xFF
int main(){
		SPI_initSlave();
	uint8 data_received=0;
	LCD_init();
	data_received = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
	 LCD_intgerToString(data_received);
	while(1){

		data_received = SPI_sendReceiveByte(SPI_DEFAULT_DATA_VALUE);
			LCD_moveCursor(0,0);
			LCD_clearScreen();
         LCD_intgerToString(data_received);
//           _delay_ms(10);
		}
	}



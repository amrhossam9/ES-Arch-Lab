#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "spi.h"

uint8 x=0x41;
ISR(INT0_vect)
{
	x++;
	if (x<=0x7a) {
		   SPI_sendReceiveByte(x);

	     }
	else{
		 x= 0x41;
	     }


}



void INT0_Init(void)
{
	DDRD  &= (~(1<<PD2));
	MCUCR |= (1<<ISC00) | (1<<ISC01);
	GICR  |= (1<<INT0);
	SREG  |= (1<<7);
}
int main(){
	SPI_initMaster();
	INT0_Init();
	 SPI_sendReceiveByte(x);

	while(1){



}
}

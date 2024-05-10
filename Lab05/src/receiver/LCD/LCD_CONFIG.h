#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H


#define LCD_MODE 4

#define LCD_RS_PORT                Port_A
#define LCD_RS_PIN                 Pin1
#define LCD_E_PORT                 Port_A
#define LCD_E_PIN                  Pin2

#if(LCD_MODE == 8)

#define LCD_DATA_PORT              Port_B

#elif(LCD_MODE == 4)

#define LCD_DATA_PORT              Port_A
#define LCD_DATA_PIN0			   Pin3
#define LCD_DATA_PIN1			   Pin4
#define LCD_DATA_PIN2			   Pin5
#define LCD_DATA_PIN3			   Pin6

#endif


#define LCD_CLEAR               		     0x01
#define LCD_HOME                 		     0x02
#define LCD_EIGHT_BIT_MODE_TWO_LINES  		 0x38
#define LCD_FOUR_BIT_MODE_S1                 0x33
#define LCD_FOUR_BIT_MODE_S2                 0x32
#define LCD_FOUR_BIT_MODE_TWO_LINES    		 0x28
#define LCD_CURSOR_OFF                 		 0x0C
#define LCD_CURSOR_ON                  		 0x0E
#define LCD_FORCE_START_LOCATION             0x80


#endif /*LCD_CONFIG_H*/
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#ifndef F_CPU
	#define F_CPU 1000000UL
#endif

struct LCD_Config LCD;
int main(){
    
    DDRD=255;
    //PORTA = 255;
    int i = 0;
    //DDRC = 255;
    LCD.LCD_DATA_PORT = &PORTD;
    LCD.LCD_DDR_PORT = &DDRD;
    LCD.LCD_E_POS = PD3;
    LCD.LCD_RS_POS = PD2;
    LCD.LCD_RW_POS = PD0;
    
    InitLCD(LCD, LS_BLINK);
    _delay_ms(80);
    LCDClear(LCD);
    _delay_ms(80);
    LCDGotoXY(LCD, 3,0);            
    LCDWriteString(LCD,"Slightgen");
    _delay_ms(80);
    LCDGotoXY(LCD, 0,1); 
    LCDMessage(LCD, 0,1,"SULCATA");
    _delay_ms(80);

    LCDClear(LCD);
    _delay_ms(10);

    while(1)
    {
        //_delay_ms(300);
        for(i=0;i<16;i++)
        {
            LCDGotoXY(LCD, i,0);            
            LCDWriteString(LCD, "SLIGHTGEN");
            LCDGotoXY(LCD, i,1);
            LCDWriteString(LCD, " SULCATA ");            
            _delay_ms(200);
            LCDClear(LCD);
            _delay_ms(10);
        }
    }
    return 0;
}

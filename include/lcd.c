#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "lcd.h"

void SET_E(struct LCD_Config config){
    (*config.LCD_DATA_PORT |=(1 << config.LCD_E_POS));
}

void SET_RS(struct LCD_Config config){
    (*config.LCD_DATA_PORT |= (1 << config.LCD_RS_POS));
}

void SET_RW(struct LCD_Config config){
    (*config.LCD_DATA_PORT |= (1 << config.LCD_RW_POS));
}

void CLEAR_E(struct LCD_Config config){
    (*config.LCD_DATA_PORT  &=(~(1<<config.LCD_E_POS)));
}
void CLEAR_RS(struct LCD_Config config){
    (*config.LCD_DATA_PORT &=(~(1<<config.LCD_RS_POS)));
}

void CLEAR_RW(struct LCD_Config config){
    (*config.LCD_DATA_PORT &=(~(1<<config.LCD_RW_POS)));
}

void LCDBusyLoop(void){
    _delay_us(200);
}

void LCDByte(struct LCD_Config config, uint8_t c,uint8_t isdata){
    uint8_t hn,ln;			//Nibbles
    uint8_t nibble;
    
    ln=c<<4;
    hn=(c & 0xF0);
    
    if(isdata==0)
        CLEAR_RS(config);
    else
        SET_RS(config);
    _delay_us(0.500);		//tAS
    SET_E(config);
    nibble=(*config.LCD_DATA_PORT & 0X0F)|(hn);
    *config.LCD_DATA_PORT=nibble;
    _delay_us(1);			//tEH
    CLEAR_E(config);
    _delay_us(1);
    SET_E(config);
    nibble=(*config.LCD_DATA_PORT & 0X0F)|(ln);
    *config.LCD_DATA_PORT=nibble;
    _delay_us(1);			//tEH
    CLEAR_E(config);
    _delay_us(1);			//tEL
    LCDBusyLoop();
}


void InitLCD(struct LCD_Config config, uint8_t style)
{
    _delay_ms(30);
    *config.LCD_DDR_PORT|=(0xF0);
    *config.LCD_DDR_PORT|=(1<<config.LCD_E_POS);
    *config.LCD_DDR_PORT|=(1<<config.LCD_RS_POS);
    *config.LCD_DDR_PORT|=(1<<config.LCD_RW_POS);
    *config.LCD_DATA_PORT &= 0X0F;
    CLEAR_E(config);
    CLEAR_RW(config);
    CLEAR_RS(config);
    //Set 4-bit mode
    _delay_us(0.3);	//tAS
    SET_E(config);
    *config.LCD_DATA_PORT|=(0b00100000); //[B] To transfer 0b00100000 i was using LCD_DATA_PORT|=0b00100000
    _delay_us(1);
    CLEAR_E(config);
    _delay_us(1);
    LCDBusyLoop();                                    //[B] Forgot this delay
    //Now the LCD is in 4-bit mode
    LCDCmd(config, 0b00001100|style);	//Display On
    LCDCmd(config, 0b00101000);	
    return ;
}


void LCDGotoXY(struct LCD_Config config, uint8_t x,uint8_t y)
{

    switch(y)
    {
        case 0  : x = 0x80 + x;
            break;
        case 1  : x = 0xc0 + x;
            break;
        case 2  : x = 0x94 + x;
            break;
        case 3  : x = 0xD4 + x;
            break;
    }
    LCDCmd(config, x);
}

void LCDWriteString(struct LCD_Config config, const char *msg)
{
    while(*msg!='\0'){
        LCDData(config, *msg);
        msg++;
    }
}

void LCDWriteInt(struct LCD_Config config, int val,unsigned int field_length)
{
	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	if(val<0) 
	{
	LCDData(config, '-');
	val=val*(-1);
	}	
	else
	LCDData(config, '+');
	while(val)
	{
	str[i]=val%10;
	val=val/10;
	i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	
	for(i=j;i<5;i++)
	{
	     LCDData(config, 48+str[i]);
	}
}


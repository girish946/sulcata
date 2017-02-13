#ifndef _LCD_H
#define _LCD_H

struct LCD_Config{
    uint8_t * LCD_DATA_PORT;
    uint8_t * LCD_DDR_PORT;
    int LCD_E_POS;
    int LCD_RS_POS;
    int LCD_RW_POS;
};

#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010

#define LCDCmd(config,c) (LCDByte(config, c,0))
#define LCDData(config, d) (LCDByte(config, d,1))

#define LCDMessage(config, x, y, msg) {\
 LCDGotoXY(config, x, y);\
 LCDWriteString(config, msg);\
}

#define LCDvar(config, x, y, val, fl) {\
 LCDGotoXY(config, x, y);\
 LCDWriteInt(config, val, fl);\
}

#define LCDClear(config) LCDCmd(config, 0b00000001)
#define LCDHome(config) LCDCmd(config, 0b00000010);

void SET_E(struct LCD_Config config);
void SET_RS(struct LCD_Config config);
void SET_RW(struct LCD_Config config);
void CLEAR_E(struct LCD_Config config);
void CLEAR_RS(struct LCD_Config config);
void CLEAR_RW(struct LCD_Config config);
void InitLCD(struct LCD_Config config, uint8_t style);
void LCDByte(struct LCD_Config config, uint8_t c,uint8_t isdata);
void LCDBusyLoop(void);
void LCDWriteString(struct LCD_Config config, const char *msg);

#endif

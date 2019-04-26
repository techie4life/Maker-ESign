/********************************
 * i2c_lcd.h
 *
 *  Created on: October 11, 2018
 *  Author: Hunter Hedges
 *
 ********************************/

#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#define CHAR_WIDTH              5   // Chars are 5 bits wide
#define CHAR_HEIGHT             8   // Chars are 8 bits high

//Commands
#define LCD_CLEARDISPLAY        0x51
#define LCD_RETURNHOME          0x46
#define LCD_ON                  0x41
#define LCD_OFF                 0x42
#define SET_CURSOR              0x45
#define CURSOR_HOME             0x46
#define CURSOR_LEFT             0x49
#define CUROSR_RIGHT            0x4A
#define BACKSPACE               0x4E
#define SET_CONTRAST            0x52
#define SET_BRIGHTNESS          0x53
#define LOAD_CUSTOM_CHAR        0x54
#define LCD_LEFT                0x55
#define LCD_RIGHT               0x56
#define CHANGE_I2C_ADDR         0x62
#define DISPLAY_I2C             0x72





/********************************
 * User Functions
 ********************************/
int LCD_init(uint8_t slaveAddress);
void LCD_clear(void);
void LCD_home(void);
void LCD_displayOn(void);
void LCD_displayOff(void);
int LCD_setCursorPosition(uint8_t row, uint8_t col);
void LCD_cursorOn(void);
void LCD_cursorOff(void);
void LCD_blinkOn(void);
void LCD_blinkOff(void);
void LCD_shiftDisplayLeft(void);
void LCD_shiftDisplayRight(void);
void LCD_textLeftToRight(void);
void LCD_textRightToLeft(void);
void LCD_autoscrollOn(void);
void LCD_autoscrollOff(void);
void LCD_backlightOn(void);
void LCD_backlightOff(void);
int LCD_isBacklightOn(void);
int LCD_createChar(uint8_t memAddress, uint8_t charMap[]);
void LCD_writeChar(uint8_t value);
void LCD_writeString(uint8_t * charBuffer, uint8_t numChars);

#endif /* I2C_LCD_H_ */

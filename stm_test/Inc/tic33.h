#ifndef TIC33_H
#define TIC33_H

#include "main.h"

#define   SClk    SetDclk;SetDclk;ClrDclk;ClrDclk;               // Строб данных
#define   SLoad   SetLoad;SetLoad;ClrLoad;ClrLoad;           // Строб загрузки

void LCD_WriteNumber(int32_t number, int8_t point_position, uint8_t symbol);
void LCD_WriteCharTIC33(uint8_t ch,uint8_t point);
void LCD_WriteTIC33(uint8_t ch);
void LCD_string_TIC33(char * buf);
void LCD_string_TD0905(char * buf);
//void LCD_Write_test(uint8_t __xdata *bcd);
void LCD_WriteBCD(uint8_t *bcd);
void LCD_WriteHex(uint32_t num);
void LCD_Setup();
void LCD_Clear(void);

#endif

#include "tic33.h"

#include <string.h>
#include "main.h"
void LCD_Setup()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Pin = LCD_LOAD_Pin;
    HAL_GPIO_Init(LCD_LOAD_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = LCD_DIN_Pin;
    HAL_GPIO_Init(LCD_DIN_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = LCD_LCLK_Pin;
    HAL_GPIO_Init(LCD_LCLK_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = LCD_DCLK_Pin;
    HAL_GPIO_Init(LCD_DCLK_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = LCD_PWR_Pin;
    HAL_GPIO_Init(LCD_PWR_GPIO_Port, &GPIO_InitStruct);

    SetPWR;
}

// TIC33
// dot = 1
// 0...9,-,deg,Space
// Segment bits:
//    _7_
//  6|_2_|1
//  5|_4_|3 .0
//
//     ___128
//  64|_4_|2
//  32|_16|8 .1
#define   minus   10
#define   degress 11
#define   space   12
#define   m1      13
#define   m2      14
#define   m3      15
#define   P_char  16
const uint8_t DigitTIC33[]  = {2+8+16+32+64+128,2+8,128+2+4+32+16,2+8+128+4+16,64+4+2+8,128+64+4+8+16,128+64+4+8+16+32,128+2+8,2+4+8+16+32+64+128,2+4+8+16+64+128,4,2+4+64+128,0, /*H*/2+4+8+32+64, /*Ï*/2+8+32+64+128, /*O*/2+8+16+32+64+128, /*P*/32+64+2+4+128};
const uint8_t DigitHexTIC33[]  = {
    2+8+16+32+64+128,//0
    2+8,//1
    128+2+4+32+16,//2
    2+8+128+4+16,//3
    64+4+2+8,//4
    128+64+4+8+16,//5
    128+64+4+8+16+32,//6
    128+2+8,//7
    2+4+8+16+32+64+128,//8
    2+4+8+16+64+128,//9
    2+4+8+32+64+128,//a
    4+8+16+32+64,//b
    16+32+64+128,//c
    2+4+8+16+32,//d
    4+16+32+64+128,//e
    4+32+64+128,//f
};

//      0a128
//  5f64   1b2
//      6g4
//  4e32   2c8
//      3d16    8,1

//	0b00111111, /* 0 */
//	0b00000110, /* 1 */
//	0b01011011, /* 2 */
//	0b01001111, /* 3 */
//	0b01100110, /* 4 */
//	0b01101101, /* 5 */
//	0b01111101, /* 6 */
//	0b00000111, /* 7 */
//	0b01111111, /* 8 */
//	0b01101111, /* 9 */

const uint8_t SevenSegmentASCII[128] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    
	0x00, /* (space) */
	0x86, /* ! */
	0x22, /* " */
	0x7E, /* # */
	0x6D, /* $ */
	0xD2, /* % */
	0x46, /* & */
	0x20, /* ' */
	0x29, /* ( */
	0x0B, /* ) */
	0x21, /* * */
	0x70, /* + */
	0x10, /* , */
	0x40, /* - */
	0x80, /* . */
	0x52, /* / */
	0x3F, /* 0 */
	0x06, /* 1 */
	0x5B, /* 2 */
	0x4F, /* 3 */
	0x66, /* 4 */
	0x6D, /* 5 */
	0x7D, /* 6 */
	0x07, /* 7 */
	0x7F, /* 8 */
	0x6F, /* 9 */
	0x09, /* : */
	0x0D, /* ; */
	0x61, /* < */
	0x48, /* = */
	0x43, /* > */
	0xD3, /* ? */
	0x5F, /* @ */
	0x77, /* A */
	0x7C, /* B */
	0x39, /* C */
	0x5E, /* D */
	0x79, /* E */
	0x71, /* F */
	0x3D, /* G */
	0x76, /* H */
	0x30, /* I */
	0x1E, /* J */
	0x75, /* K */
	0x38, /* L */
	0x15, /* M */
	0x37, /* N */
	0x3F, /* O */
	0x73, /* P */
	0x6B, /* Q */
	0x33, /* R */
	0x6D, /* S */
	0x78, /* T */
	0x3E, /* U */
	0x3E, /* V */
	0x2A, /* W */
	0x76, /* X */
	0x6E, /* Y */
	0x5B, /* Z */
	0x39, /* [ */
	0x64, /* \ */
	0x0F, /* ] */
	0x37, /* ^ */
	0x08, /* _ */
	0x02, /* ` */
	0x5F, /* a */
	0x7C, /* b */
	0x58, /* c */
	0x5E, /* d */
	0x7B, /* e */
	0x71, /* f */
	0x6F, /* g */
	0x74, /* h */
	0x10, /* i */
	0x0C, /* j */
	0x75, /* k */
	0x30, /* l */
	0x14, /* m */
	0x54, /* n */
	0x5C, /* o */
	0x73, /* p */
	0x67, /* q */
	0x50, /* r */
	0x6D, /* s */
	0x78, /* t */
	0x1C, /* u */
	0x1C, /* v */
	0x14, /* w */
	0x76, /* x */
	0x6E, /* y */
	0x5B, /* z */
	0x46, /* { */
	0x30, /* | */
	0x70, /* } */
	0x01, /* ~ */
	0x00, /* (del) */
};

void LCD_ASCII_TIC33(uint8_t ch)
{
    uint8_t code = SevenSegmentASCII[ch & 0x7F];
    uint8_t code_t33 = 0;
//      0a128
//  5f64   1b2
//      6g4
//  4e32   2c8
//      3d16    8,1
    if (code & (1 << 0)) code_t33 |= 128;
    if (code & (1 << 1)) code_t33 |= 2;
    if (code & (1 << 2)) code_t33 |= 8;
    if (code & (1 << 3)) code_t33 |= 16;
    if (code & (1 << 4)) code_t33 |= 32;
    if (code & (1 << 5)) code_t33 |= 64;
    if (code & (1 << 6)) code_t33 |= 4;
//    if (code & (1 << 7)) code_t33 |= 1;
    if (ch & 0x80) code_t33 |= 1;

    for (uint8_t i=8; i; i--) {
        if (code_t33 & 0x80) {
            SetDin;
            SetDin;
        } else {
            ClrDin;
            ClrDin;
        }
        code_t33 <<= 1;
        SClk;
    }
}

void LCD_ASCII_TD0905(uint8_t ch)
{
    uint8_t code = SevenSegmentASCII[ch & 0x7F];
    uint8_t code_t33 = 0;
//      0a1
//  5f2   1b
//      6g32
//  4e4   2c16
//      3d8    8,
//    code_t33 = code;
    if (code & (1 << 0)) code_t33 |= 1;
    if (code & (1 << 1)) code_t33 |= 64;
    if (code & (1 << 2)) code_t33 |= 16;
    if (code & (1 << 3)) code_t33 |= 8;
    if (code & (1 << 4)) code_t33 |= 4;
    if (code & (1 << 5)) code_t33 |= 2;
    if (code & (1 << 6)) code_t33 |= 32;
//    if (code & (1 << 7)) code_t33 |= 128;
    if (ch & 0x80) code_t33 |= 128;
    
    for (uint8_t i=8; i; i--) {
        if (code_t33 & 0x80) {
            SetDin;
            SetDin;
        } else {
            ClrDin;
            ClrDin;
        }
        code_t33 <<= 1;
        SClk;
    }
}

void LCD_WriteCharTIC33(uint8_t ch,uint8_t point)
{
    uint8_t i;
    ch=DigitTIC33[ch];
    if(point) ch |= 1;
    // Output
    for(i=8; i; i--)
    {
        if(ch & 128)
        {
            SetDin;
            SetDin;
        }
        else
        {
            ClrDin;
            ClrDin;
        }

        ch=ch<<1;
        SClk;
    }
}

void LCD_WriteHexCharTIC33(uint8_t ch,uint8_t point)
{
    uint8_t i;
    ch=DigitHexTIC33[ch];
    if(point) ch |= 1;
    // Output
    for(i=8; i; i--)
    {
        if(ch & 128)
        {
            SetDin;
            SetDin;
        }
        else
        {
            ClrDin;
            ClrDin;
        }

        ch=ch<<1;
        SClk;
    }
}

void LCD_WriteTIC33(uint8_t ch)
{
    uint8_t i;
    // Output
    for(i=8; i; i--)
    {
        if(ch & 128)
        {
            SetDin;
            SetDin;
        }
        else
        {
            ClrDin;
            ClrDin;
        }

        ch=ch<<1;
        SClk;
    }
}

const uint32_t divs[]={
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000};

void LCD_string_TIC33(char * buf)
{
//    uint8_t i = 0;
//    uint8_t len = 0;
//    for (i=0; i < 30; i++) {
//        if (!buf[i]) break;
//        if (buf[i] != ',' && buf[i] != '.') len++;
//    }
//    i = len;
//    while (i < 9) {
//        i++;
//        LCD_ASCII_TIC33(0);
//    }
//    
//    for (uint8_t i = 0; i < 30; i++) {
//        uint8_t ch = buf[i];
//        if (!ch) break;
//        if (buf[i+1] == ',' || buf[i+1] == '.') {
//            ch |= 0x80;
//            i++;
//        }
//        LCD_ASCII_TIC33(ch);
//    }
//    SLoad;
    uint8_t i = 0;
    uint8_t len = 0;
    for (i=0; i < 30; i++) {
        if (!buf[i]) break;
        if (buf[i] != ',' && buf[i] != '.') len++;
    }
    i = len;
    while (i < 9) {
        i++;
        LCD_ASCII_TIC33(0);
    }
    
    for (uint8_t i = 0; i < 30; i++) {
        uint8_t ch = buf[i];
        if (!ch) break;
        if (buf[i+1] == ',' || buf[i+1] == '.') {
            ch |= 0x80;
            i++;
        }
        LCD_ASCII_TIC33(ch);
    }
    SLoad;
}

void LCD_string_TD0905(char * buf)
{
//    uint8_t i = 0;
//    uint8_t len = 0;
//    for (i=0; i < 30; i++) {
//        if (!buf[i]) break;
//        if (buf[i] != ',' && buf[i] != '.') len++;
//    }
//    i = len;
//    while (i < 9) {
//        i++;
//        LCD_ASCII_TIC33(0);
//    }
//    
//    for (uint8_t i = 0; i < 30; i++) {
//        uint8_t ch = buf[i];
//        if (!ch) break;
//        if (buf[i+1] == ',' || buf[i+1] == '.') {
//            ch |= 0x80;
//            i++;
//        }
//        LCD_ASCII_TIC33(ch);
//    }
//    SLoad;
    uint8_t len = strlen(buf);
    if (len > 30) len = 30;
    uint8_t flag_ch = 0;
    uint8_t i = 0;
    while (len--) {
        uint8_t ch = buf[len];
        if (ch == ',' || ch == '.') {
            flag_ch = 0x80;
            continue;
        }            
        if (flag_ch) {
            ch |= 0x80;
        }
        LCD_ASCII_TD0905(ch);
        i++;
        flag_ch = 0;
    }
//    uint8_t i = 0;
//    uint8_t len = 0;
//    for (i=0; i < 30; i++) {
//        if (!buf[i]) break;
//        if (buf[i] != ',' && buf[i] != '.') len++;
//    }
//    i = len;
    while (i < 9) {
        i++;
        LCD_ASCII_TD0905(0);
    }
//    
//    for (uint8_t i = 0; i < 30; i++) {
//        uint8_t ch = buf[i];
//        if (!ch) break;
//        if (buf[i+1] == ',' || buf[i+1] == '.') {
//            ch |= 0x80;
//            i++;
//        }
//        LCD_ASCII_TD0905(ch);
//    }
    SLoad;
}

void LCD_WriteNumber(int32_t number, int8_t point_position, uint8_t symbol)
{
//    LCD_DIR |= 0x31;
    uint32_t div, digits=0;
    uint8_t i;

    if (number < 0)
        number = -number;

    for (div = 1; div <= number; div *= 10) digits++;

    // Clear buffer
    for(i=(9-digits); i>0;i--)
    {
//        LCD_WriteCharTIC33(space,0);
        LCD_WriteCharTIC33(0,0);
    }

    if(symbol == 'H')
    {
        LCD_WriteCharTIC33(13, 0);
        LCD_WriteCharTIC33(12, 0);
    }
    else if (symbol == 'P')
    {
        LCD_WriteCharTIC33(14, 0);
        LCD_WriteCharTIC33(15, 0);
    }

    //if (number < 0) LCD_WriteCharTIC33(minus,0);

    if (number < 10)
    {
        LCD_WriteCharTIC33(number, 0);
    }
    else
    {
        do
        {
            //div /= 10;
            digits--;
            LCD_WriteCharTIC33(number / divs[digits], (digits == point_position)? 1 : 0);
            //LCD_WriteCharTIC33(number / div, (div == 1000 || div == (uint32_t)1000000)? 1 : 0);
            number %= divs[digits];
        }
        while(digits);
    }
    SLoad;
}

void LCD_WriteHex(uint32_t num)
{
//    LCD_DIR |= 0x31;

    LCD_WriteCharTIC33(13, 1);
    LCD_WriteCharTIC33(12, 0);
    LCD_WriteCharTIC33(12, 0);

    //LCD_WriteHexCharTIC33((num >> 28) & 0xF, 0);
    //LCD_WriteHexCharTIC33((num >> 24) & 0xF, 0);
    LCD_WriteHexCharTIC33((num >> 20) & 0xF, 0);
    LCD_WriteHexCharTIC33((num >> 16) & 0xF, 0);
    LCD_WriteHexCharTIC33((num >> 12) & 0xF, 0);
    LCD_WriteHexCharTIC33((num >>  8) & 0xF, 0);
    LCD_WriteHexCharTIC33((num >>  4) & 0xF, 0);
    LCD_WriteHexCharTIC33( num        & 0xF, 0);



    SLoad;
}

void LCD_Write_test(uint8_t *bcd)
{
//    LCD_DIR |= 0x31;

    LCD_WriteCharTIC33(bcd[4]&0xF, 1);
    LCD_WriteCharTIC33(bcd[3]>> 4, 1);
    LCD_WriteCharTIC33(bcd[3]&0xF, 1);
    LCD_WriteCharTIC33(bcd[2]>> 4, 1);
    LCD_WriteCharTIC33(bcd[2]&0xF, 1);
    LCD_WriteCharTIC33(bcd[1]>> 4, 1);
    LCD_WriteCharTIC33(bcd[1]&0xF, 1);
    LCD_WriteCharTIC33(bcd[0]>> 4, 1);
    LCD_WriteCharTIC33(bcd[0]&0xF, 1);

    SLoad;
}


void LCD_WriteBCD(uint8_t *bcd)
{
//    LCD_DIR |= 0x31;

    LCD_WriteCharTIC33(13, 1);
    LCD_WriteCharTIC33(12, 0);

    LCD_WriteCharTIC33(bcd[3]&0xF, 0);
    LCD_WriteCharTIC33(bcd[2]>> 4, 0);
    LCD_WriteCharTIC33(bcd[2]&0xF, 0);
    LCD_WriteCharTIC33(bcd[1]>> 4, 0);
    LCD_WriteCharTIC33(bcd[1]&0xF, 0);
    LCD_WriteCharTIC33(bcd[0]>> 4, 0);
    LCD_WriteCharTIC33(bcd[0]&0xF, 0);

    SLoad;
}

void LCD_Clear(void)
{
//    LCD_DIR |= 0x31;
    LCD_WriteCharTIC33(space,0);
    LCD_WriteCharTIC33(space,0);
    LCD_WriteCharTIC33(space,0);
    LCD_WriteCharTIC33(space,0);
    LCD_WriteCharTIC33(space,0);
    LCD_WriteCharTIC33(space,0);
    LCD_WriteCharTIC33(space,0);
    LCD_WriteCharTIC33(space,0);
    LCD_WriteCharTIC33(space,0);
    SLoad;
}

#include "helpers.h"


// Handles arrow manipulation
typedef struct _arrow {
    UBYTE arrow[3]; 
    UBYTE x;
    UBYTE y;
} Arrow;
Arrow arrow = {{0x1f, 0x0e, 0x04}, 36, 16};
// Draws the arrow on the screen based on its choice
void draw_arrow() 
{
    int i, j;
    for(i = 0; i < 3; i++) 
    {
        UBYTE col = arrow.arrow[i];
        for(j = 0; j < 5; j++) 
        {
            if (col & 1)
                pixon(arrow.x + i, arrow.y + j);
            else
                pixoff(arrow.x + i, arrow.y + j);
            
            col = col >> 1;
        } 
    }
}

void arrow_up() {
    arrow.y = 16;
}

void arrow_down() {
    arrow.y = 24;
}

// 0 is play, 1 is score
BYTE arrow_state() 
{
    if(arrow.y == 16) {
        return 0x0;
    }
    return 0x1;
}

/*
    FRAMES OF THE SPLASH SCREEN
*/

UBYTE splash_f1[] = {
0x00,0x82,0xE0,0xF8,0xF8,0x1C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x1C,0xFC,0xF8,0xF0,0x00,0x02,0xFC,0xFC,0xFC,0x00,0x0A,0xFC,0xFC,0xFC,0x00,0x01,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFC,0xFC,0xFC,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x00,0x01,0xF0,0xFC,0xFC,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFC,0xFC,0xF8,0x00,0x03,0xFC,0xFC,0xFC,0x00,0x0A,0xFC,0xFC,0xFC,0x00,0x02,0xF8,0xFC,0xFC,0x1C,0x3C,0x78,0xF0,0xE0,0xC0,0x80,0x00,0x04,0xFC,0xFC,0xFC,0x00,0x17,0x0F,0x3F,0x7F,0x70,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x70,0x7F,0x3F,0x1F,0x00,0x02,0x0F,0x3F,0x7F,0x70,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x70,0x7F,0x3F,0x1F,0x00,0x07,0x7F,0x7F,0x7F,0x00,0x07,0x3F,0x7F,0x7F,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x07,0x1F,0x7D,0x7D,0x00,0x03,0x0F,0x3F,0x7F,0x70,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x70,0x7F,0x3F,0x1F,0x00,0x02,0x3F,0x7F,0x7F,0x00,0x04,0x01,0x03,0x0F,0x1E,0x3C,0x78,0x70,0x7F,0x7F,0x7F,0x00,0x03,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00,0x02,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00,0x82};

UBYTE splash_f2[] = {
0x00,0x82,0xB0,0xBC,0xBC,0x0E,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x0E,0xBE,0xBC,0xB8,0x00,0x02,0xBE,0xBE,0xBE,0x00,0x0A,0xFC,0xFC,0xFC,0x00,0x01,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFC,0xFC,0x00,0x01,0x7E,0x06,0x06,0x06,0x06,0x06,0x06,0x00,0x01,0x78,0x7E,0x7E,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x7E,0x7E,0x7C,0x00,0x02,0xFC,0xFC,0xFC,0x00,0x0B,0xFE,0xFE,0xFE,0x00,0x02,0xFC,0xFE,0xFE,0x0E,0x1E,0x3C,0x78,0xF0,0xE0,0xC0,0x00,0x04,0xFE,0xFE,0xFE,0x00,0x15,0x10,0x77,0xF7,0xE7,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xF0,0x77,0x37,0x07,0x00,0x01,0x10,0x77,0xF7,0xE7,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xF0,0x77,0x37,0x07,0x00,0x07,0x7F,0x7F,0x7F,0x00,0x07,0x3F,0x7F,0x7F,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x07,0x1F,0x7D,0x7D,0x00,0x03,0x0F,0x3F,0x7F,0x70,0x60,0x60,0x00,0x01,0xC0,0xC0,0xC0,0xC0,0xC0,0xD0,0xDC,0xDD,0x5D,0x01,0x00,0x01,0x1C,0x5D,0xDD,0xC1,0x00,0x05,0x0D,0x1D,0x1D,0x58,0xD0,0xDC,0xDD,0xDD,0xC1,0x00,0x02,0x04,0x05,0x05,0x05,0x05,0x05,0x05,0x01,0x00,0x01,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00,0x82};

UBYTE splash_f3[] = {
0x00,0x0B,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x04,0xF0,0xF0,0xE0,0x00,0x17,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x02,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x16,0xC0,0xE0,0xE0,0xE0,0xE0,0xC0,0x80,0x00,0x07,0xE0,0xE0,0xE0,0x00,0x15,0xC0,0xC0,0xD8,0x1E,0x1E,0x07,0x03,0x03,0x03,0x01,0x01,0x01,0x01,0x01,0x03,0x87,0x87,0x80,0x00,0x02,0x80,0x81,0x81,0x00,0x09,0xFF,0xFF,0xFF,0x00,0x02,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFC,0xFC,0x00,0x01,0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x01,0x1E,0x1F,0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x1F,0x1F,0x1F,0x00,0x02,0xFC,0xFC,0xFC,0x00,0x0B,0xFE,0xFE,0xFE,0x00,0x02,0x1F,0x1F,0x1F,0x00,0x01,0x01,0x03,0x07,0x0F,0x1E,0x1C,0x10,0x00,0x03,0x1F,0x1F,0x1F,0x00,0x03,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x01,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x03,0x03,0x13,0x73,0xF0,0xE0,0xC0,0x80,0x80,0x80,0x80,0x00,0x04,0x80,0x87,0x87,0x07,0x00,0x02,0x07,0x07,0x07,0x00,0x09,0x01,0x01,0x01,0x00,0x08,0xF0,0xF0,0x70,0x00,0x06,0x7E,0xFE,0xFE,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x00,0x01,0x06,0x06,0x07,0x1F,0x7D,0x7D,0x00,0x03,0x0F,0x3F,0x7F,0x70,0x60,0x60,0x00,0x01,0xC0,0xC0,0xC0,0xC0,0xC0,0xD0,0xDC,0xDD,0x5D,0x01,0x00,0x01,0x1C,0x5C,0xDC,0xC0,0x00,0x05,0x0C,0x1C,0x1C,0x58,0xD0,0xDC,0xDC,0xDC,0xC0,0x00,0x02,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x02,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x08,0x01,0x01,0x01,0x01,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x01,0x00,0x02,0x01,0x07,0x0F,0x0E,0x1C,0x18,0x18,0x18,0x30,0x30,0x30,0x30,0x38,0x38,0x18,0x00,0x09,0x03,0x03,0x00,0x52};

UBYTE splash_f4[] = {
0xF0,0x38,0x18,0x18,0x18,0x08,0x0C,0x0C,0x0C,0x0C,0x1C,0x3C,0x38,0x00,0x03,0x07,0x0F,0x0F,0x00,0x09,0xF8,0xF8,0xF8,0x00,0x02,0x60,0x60,0x00,0x0C,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x02,0x80,0x80,0x80,0x80,0x00,0x01,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFC,0xFC,0xF8,0x00,0x16,0x7F,0x7F,0x7F,0x03,0x07,0x0F,0x00,0x02,0x78,0xF0,0xE0,0xC0,0x00,0x04,0xFE,0xFE,0xFE,0x00,0x11,0xC0,0xC0,0xC0,0x00,0x0C,0x80,0x80,0x80,0x00,0x02,0x80,0x80,0x80,0x00,0x09,0xE0,0xE0,0xE0,0x00,0x04,0x0C,0x0C,0x0C,0x0C,0xFC,0xFC,0x00,0x01,0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x01,0x1E,0x1F,0x1F,0x01,0x01,0x00,0x0C,0xFC,0xFC,0xFC,0x00,0x0B,0x1E,0x9E,0x9E,0x80,0x00,0x0D,0x01,0x01,0x01,0x00,0x03,0x01,0x01,0x01,0x00,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x01,0x02,0x02,0x02,0x02,0x02,0x00,0x01,0x03,0x03,0x03,0x00,0x0C,0x07,0x07,0x07,0x00,0x02,0x07,0x07,0x07,0x00,0x09,0x01,0x01,0x01,0x00,0x08,0xF0,0xF0,0x70,0x00,0x06,0x06,0x06,0x06,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x01,0x06,0x06,0x07,0x07,0x05,0x05,0x00,0x03,0x07,0x07,0x07,0x00,0x0B,0x10,0x17,0xB7,0x07,0x00,0x26,0x07,0x0F,0x0E,0x1C,0x18,0x18,0x18,0x18,0x30,0x30,0x30,0x30,0x38,0x38,0x18,0x00,0x02,0x10,0x70,0xF0,0xE0,0xC0,0x80,0x80,0x80,0x00,0x04,0x80,0x80,0x80,0x00,0x0C,0x03,0x03,0x00,0x06,0x0F,0x1F,0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x04,0x03,0x0F,0x0F,0x00,0x06,0x01,0x07,0x0F,0x0E,0x0C,0x0C,0x00,0x01,0x18,0x18,0x18,0x18,0x18,0x1A,0x1B,0x1B,0x00,0x02,0x07,0x17,0x37,0x30,0x00,0x05,0x03,0x07,0x07,0x16,0x34,0x37,0x37,0x37,0x30,0x00,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x01};

UBYTE splash_f5[] = {
0x00,0x07,0x01,0x03,0x03,0x00,0x0B,0x0F,0x0F,0x0F,0x00,0x02,0x0C,0x0C,0x00,0x05,0x80,0x80,0x80,0x80,0x80,0x1E,0x00,0x02,0x08,0x00,0x01,0x3F,0x03,0x03,0x03,0x00,0x04,0x03,0x03,0x03,0x00,0x01,0x3C,0x3F,0x3F,0x03,0x03,0x00,0x08,0x01,0x01,0x01,0x00,0x01,0xF8,0xF8,0xF8,0x00,0x0E,0x80,0x80,0x80,0x00,0x01,0x01,0x00,0x02,0x1F,0x01,0x01,0x00,0x01,0x07,0x07,0x00,0x03,0x01,0x00,0x01,0x07,0x03,0x07,0x07,0x04,0x01,0x01,0x00,0x01,0x07,0x07,0x01,0x00,0x02,0x03,0x00,0x03,0x02,0x02,0x02,0x02,0xC0,0x00,0x0C,0x80,0x80,0x00,0x03,0x80,0x80,0x00,0x06,0x04,0x04,0x04,0xC0,0xC0,0xC0,0x00,0x01,0x01,0x01,0x01,0x01,0x07,0x00,0x02,0xC0,0x80,0x00,0x2F,0x07,0x07,0x07,0x00,0x24,0x03,0x00,0x0C,0x07,0x07,0x00,0x03,0x07,0x07,0x00,0x09,0x01,0x01,0x01,0x00,0x23,0x80,0x00,0x01,0xC0,0xC0,0xE0,0xE0,0xA0,0xA0,0x00,0x03,0xF0,0xF0,0xF0,0x00,0x0C,0xF0,0xF0,0xF0,0x00,0x25,0x30,0x38,0x38,0x18,0x00,0x01,0xE0,0xD0,0xF0,0xF0,0x00,0x06,0x80,0x00,0x04,0x80,0x80,0x80,0x00,0x04,0xF8,0xF8,0x38,0x00,0x06,0x03,0x03,0x03,0x02,0x82,0x82,0x00,0x04,0x82,0x82,0x00,0x1C,0xE0,0xE0,0xC0,0x80,0x80,0x00,0x06,0x42,0x62,0x76,0x00,0x02,0xE0,0xE0,0xE0,0x03,0x07,0x07,0x16,0x00,0x03,0x40,0x70,0x70,0x70,0x00,0x03,0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x01};

UBYTE splash_f6[] = {
0x00,0x04,0x0C,0x0C,0x0C,0x00,0x02,0x0C,0x0F,0x03,0x03,0x00,0x08,0x1C,0x00,0x02,0x08,0x00,0x01,0x1C,0x82,0x80,0x80,0x80,0x80,0x03,0x03,0x03,0x00,0x02,0x20,0x00,0x09,0x06,0x00,0x02,0x30,0x38,0x3E,0x1E,0x06,0x00,0x01,0x08,0x0E,0x0E,0x06,0x06,0x00,0x07,0x01,0x01,0x01,0x00,0x01,0x18,0x00,0x04,0x18,0x18,0xE0,0x80,0x80,0x00,0x02,0x60,0x60,0x00,0x0A,0x80,0x81,0x80,0x00,0x01,0x1F,0x01,0x01,0x00,0x01,0x07,0x07,0x00,0x03,0x01,0x00,0x01,0x07,0x03,0x07,0x07,0x04,0x01,0x01,0x00,0x01,0x07,0x07,0x01,0x00,0x02,0x03,0x00,0x03,0xC0,0x00,0x0C,0x80,0x80,0x00,0x03,0x80,0x80,0x00,0x06,0x04,0x05,0x05,0xC1,0xC1,0xC3,0x00,0x05,0x04,0x00,0x02,0xC0,0x80,0x00,0x36,0x07,0x07,0x07,0x00,0x06,0x40,0x40,0x00,0x19,0x07,0x07,0x00,0x03,0x07,0x07,0x00,0x09,0x01,0x01,0x01,0x00,0x08,0x0C,0x0C,0x0C,0x08,0x08,0x08,0x00,0x04,0x08,0x08,0x00,0x27,0x80,0x00,0x01,0x80,0x90,0x10,0x10,0x10,0x04,0x04,0x04,0x14,0x13,0x01,0x00,0x01,0x0C,0x0C,0x04,0x40,0x00,0x02,0x0A,0x0A,0x2A,0x60,0x70,0x50,0x10,0x02,0x60,0x00,0x03,0x05,0x05,0x05,0x00,0x0B,0x1C,0x1A,0x1E,0x1E,0x00,0x06,0x10,0x00,0x04,0x10,0x10,0x10,0x00,0x04,0x1F,0x1F,0x07,0x00,0x0A,0x02,0x02,0x00,0x04,0x02,0x02,0x00,0x2C,0x07,0x07,0x06,0x04,0x04,0x00,0x08,0x40,0x60,0x60,0x00,0x01,0x38,0x38,0x38,0x00,0x06,0x13,0x18,0x03,0x03,0x03,0x02,0x00,0x01,0x02,0x02,0x02,0x00,0x05};

UBYTE splash_f7[] = {
0x00,0x04,0x0C,0x0C,0x0C,0x00,0x01,0x01,0x0C,0x0F,0x03,0x0F,0x00,0x08,0x1C,0x00,0x02,0x08,0x00,0x01,0x1C,0x82,0x80,0x80,0x80,0x80,0x03,0x03,0x03,0x00,0x02,0x20,0x00,0x08,0x03,0x00,0x04,0x03,0x73,0x73,0x70,0x04,0x07,0x00,0x02,0x38,0x18,0x18,0x00,0x06,0x01,0x01,0x01,0x00,0x01,0x18,0x00,0x04,0x18,0x18,0xE0,0x80,0x80,0x00,0x02,0x60,0x60,0x00,0x0A,0x80,0x81,0x80,0x00,0x01,0x1F,0x01,0x01,0x00,0x01,0x07,0x07,0x00,0x03,0x01,0x00,0x01,0x07,0x03,0x07,0x07,0x04,0x01,0x01,0x00,0x01,0x07,0x07,0x01,0x00,0x02,0x03,0x00,0x09,0x1C,0x00,0x02,0xC0,0x1C,0x1C,0x00,0x02,0x0F,0x0F,0x0F,0x00,0x02,0x02,0x02,0x04,0x04,0x0C,0x00,0x02,0x04,0x05,0x0D,0x09,0x0B,0xFB,0xFB,0x38,0x00,0x03,0x04,0x00,0x01,0x20,0x23,0x03,0x03,0x00,0x02,0x20,0x20,0x00,0x25,0x40,0x40,0x40,0x40,0xC0,0xC0,0x80,0x80,0x00,0x04,0x87,0x87,0xC7,0x00,0x04,0x40,0x40,0x00,0x01,0x80,0xD8,0x1A,0x5A,0x12,0x00,0x02,0x20,0x20,0x20,0x00,0x04,0x50,0x50,0x50,0x00,0x0E,0x01,0x00,0x1A,0x08,0x00,0x02,0x08,0x08,0x00,0x04,0x08,0x08,0x00,0x27,0x01,0x00,0x01,0x01,0x71,0x01,0x03,0x00,0x01,0x02,0x03,0x01,0x01,0x05,0x06,0x00,0x02,0x80,0x00,0x01,0x01,0x81,0x00,0x01,0x03,0x03,0x00,0x08,0x43,0x63,0x63,0x72,0x00,0x04,0x10,0x10,0x10,0x00,0x66,0x01,0x00,0x02,0x03,0x00,0x17};

UBYTE splash_f8[] = {
0x00,0x08,0x01,0x00,0x01,0x03,0x03,0x03,0x06,0x06,0x06,0x00,0x02,0x06,0x06,0x38,0x1E,0x00,0x01,0x80,0x38,0xF8,0x7C,0x7A,0x40,0x58,0xD8,0x98,0xBB,0xBB,0xB3,0x80,0x00,0x01,0x60,0x60,0x40,0x00,0x02,0x30,0x30,0x30,0x00,0x01,0x13,0x10,0x00,0x03,0x03,0x3F,0x3F,0x3C,0x00,0x01,0x03,0x00,0x01,0x06,0x06,0x06,0x00,0x07,0x05,0x01,0x01,0x00,0x01,0x08,0x04,0x04,0x78,0x60,0x68,0x48,0xC0,0xFC,0x98,0x80,0x04,0x04,0x04,0x00,0x01,0x84,0x84,0x44,0x00,0x02,0x60,0x00,0x04,0x81,0xC0,0x50,0x5F,0x91,0xD1,0x10,0x57,0x97,0x00,0x02,0x20,0x21,0xA0,0x87,0x83,0x07,0x07,0x54,0x51,0x51,0x00,0x01,0x07,0x07,0x01,0x00,0x02,0x03,0x00,0x1A,0x03,0x00,0x09,0x03,0x03,0x03,0x00,0x06,0x04,0x04,0x04,0x00,0x04,0x04,0x04,0x00,0x1A,0x01,0x00,0x01,0x01,0x71,0x01,0x03,0x03,0x02,0x03,0x07,0x01,0x05,0x00,0x08,0x01,0x01,0x01,0x00,0x01,0x01,0x03,0x03,0x03,0x03,0x00,0x05,0x01,0x01,0x01,0x00,0xFF,0x0E};

UBYTE splash_f9[] = {
0x00,0x0B,0x04,0x00,0x01,0x0C,0x0C,0x0C,0x18,0x18,0x1E,0x06,0x38,0x1E,0x00,0x05,0x02,0xC8,0x4C,0xCC,0x8C,0x8F,0x8F,0x8F,0xC8,0x00,0x01,0x40,0xCC,0xC0,0x00,0x02,0x30,0x30,0x3C,0x3C,0x13,0x14,0x04,0x04,0xFC,0xFF,0x3F,0x3F,0x3C,0xFC,0x47,0x44,0x46,0x46,0x00,0x05,0xFC,0x80,0x00,0x01,0x05,0x01,0x01,0xDC,0xDC,0x04,0xDC,0x5C,0x00,0x01,0x78,0x68,0xC0,0xFC,0xFC,0x80,0x04,0x24,0x24,0x20,0x84,0x84,0x64,0x20,0x20,0x00,0x05,0x81,0x80,0x10,0x1F,0x91,0xD1,0x52,0x57,0x9F,0x06,0x0E,0x0E,0x28,0xA2,0xA2,0x80,0x0E,0x0E,0x42,0x40,0x40,0x00,0x06,0x03,0x00,0x1A,0x03,0x00,0x04,0x01,0x01,0x01,0x01,0x01,0x03,0x03,0x03,0x00,0x02,0x01,0x01,0x01,0x01,0x05,0x05,0x00,0x05,0x04,0x05,0x01,0x00,0x03,0x01,0x00,0x09,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x02,0x01,0x00,0x02,0x01,0x00,0x01,0x01,0x71,0x01,0x03,0x03,0x02,0x03,0x07,0x01,0x05,0x00,0x08,0x01,0x01,0x01,0x00,0x01,0x01,0x03,0x03,0x03,0x03,0x00,0x05,0x01,0x01,0x01,0x00,0xFF,0x0E};

UBYTE splash_f10[] = {
0x00,0x16,0x08,0x00,0x01,0x18,0x00,0x03,0x80,0x00,0x01,0xF0,0xB8,0xA8,0x28,0x2C,0x6C,0x3C,0xF0,0x40,0x40,0xF8,0x00,0x01,0x20,0x20,0x60,0x60,0xF8,0xF8,0x08,0x0C,0x1C,0xCE,0xFE,0xFA,0x18,0xCC,0x4E,0xFC,0x8A,0xC8,0x88,0x88,0x88,0xF8,0x30,0xF0,0x80,0xF8,0x01,0x01,0x01,0x40,0x08,0xFC,0xFC,0x4C,0xF8,0x38,0x30,0x60,0xCC,0x8C,0x80,0xFC,0x20,0xB0,0xE0,0xCC,0xCC,0x7C,0x0C,0xE4,0xC8,0x44,0x80,0xC0,0x40,0x40,0x40,0x00,0x02,0x08,0x00,0x36,0x01,0x03,0x03,0x03,0x02,0x02,0x03,0x02,0x02,0x03,0x01,0x01,0x03,0x03,0x06,0x02,0x02,0x02,0x03,0x01,0x00,0x01,0x04,0x04,0x01,0x03,0x03,0x00,0x01,0x01,0x00,0x01,0x03,0x00,0x05,0x03,0x03,0x01,0x00,0x01,0x03,0x03,0x03,0x02,0x02,0x02,0x03,0x01,0x00,0x01,0x03,0x00,0x03,0x02,0x01,0x03,0x03,0x00,0x01,0x01,0x01,0x00,0x01,0x04,0x01,0x01,0x01,0x00,0x01,0x02,0x00,0x03,0x01,0x01,0x01,0x01,0x01,0x00,0xFF,0x1A};

UBYTE splash_f11[] = {
0x00,0x1A,0x08,0x00,0x01,0x18,0x00,0x01,0xF8,0x0C,0x04,0x24,0x2C,0x2C,0x2C,0xF8,0x20,0x00,0x01,0xFC,0x80,0x20,0x80,0x80,0x80,0xFC,0xFC,0x20,0x14,0x54,0x1C,0xFC,0xFC,0x44,0x14,0x1C,0xFC,0x4C,0x44,0x44,0x44,0x44,0xFC,0x98,0xC0,0x00,0x01,0xFC,0x84,0x04,0x04,0x00,0x01,0x20,0xFC,0xFC,0x0C,0xFC,0x6C,0x78,0x70,0x78,0xD8,0xF8,0xFC,0x48,0x10,0x28,0x20,0x20,0x00,0x02,0x20,0x20,0x20,0x10,0x00,0x3F,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x05,0x01,0x01,0x00,0x03,0x01,0x00,0x05,0x01,0x01,0x00,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x02,0x01,0x00,0x05,0x01,0x01,0x00,0xFF,0x2C};

UBYTE splash_f12[] = {
0x00,0x1E,0xFC,0x86,0x82,0x82,0x82,0x82,0x86,0xFC,0x00,0x02,0xFE,0x80,0x80,0x80,0x80,0x80,0x80,0xFE,0x00,0x01,0x02,0x02,0x02,0xFE,0x02,0x02,0x02,0x00,0x01,0xFE,0x22,0x22,0x22,0x22,0x22,0x52,0x8C,0x00,0x02,0xFE,0x80,0x80,0x80,0x80,0x80,0x80,0xFE,0x00,0x01,0xFE,0x06,0x0C,0x18,0x30,0x60,0xC0,0xFE,0x00,0x02,0x10,0x10,0x10,0x00,0x02,0x10,0x10,0x10,0x00,0x40,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x02,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x00,0x05,0x05,0x00,0x04,0x05,0x00,0x06,0x05,0x00,0x02,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x04,0x00,0x01,0x05,0x00,0x05,0x05,0x05,0x00,0x58,0x1F,0x05,0x05,0x05,0x05,0x07,0x00,0x01,0x1F,0x10,0x10,0x10,0x00,0x02,0x18,0x0E,0x09,0x09,0x0E,0x18,0x00,0x02,0x01,0x02,0x1C,0x02,0x01,0x00,0x63,0x17,0x15,0x15,0x15,0x15,0x1C,0x00,0x01,0x1F,0x11,0x11,0x11,0x11,0x11,0x00,0x01,0x1F,0x11,0x11,0x11,0x11,0x1F,0x00,0x01,0x1F,0x05,0x05,0x05,0x0D,0x1B,0x00,0x01,0x1F,0x15,0x15,0x15,0x15,0x00,0x36};

UBYTE *frames[] = {splash_f1, splash_f2, splash_f3, splash_f4, splash_f5, splash_f6, splash_f7, splash_f8, splash_f9, splash_f10, splash_f11, splash_f12};
int frame_sizes[] = {204, 211, 308, 316, 247, 258, 241, 172, 183, 166, 125, 184};
// Plays through the animations frame by frame
void init_splash() 
{
    const int DELAY = 167; // Animation should take 2000ms. Gives 2000/12 ~= 167 ms per frame
    int frame_num, i, j, zeroes, timer = TICKS;
    for(frame_num = 0; frame_num < 12; frame_num++) {
        for (i = 0, j = 0; i < frame_sizes[frame_num]; i++)
        {
            if (frames[frame_num][i] == 0x00)
            {
                zeroes = frames[frame_num][++i];
                if (zeroes == 0xFF)
                    zeroes += frames[frame_num][++i] + 1;
                for (; zeroes > 0; zeroes--)
                    display_buffer[j++] = 0x00;
                continue;
            }
            display_buffer[j++] = frames[frame_num][i];
        }

        while (TICKS - timer < DELAY);

        timer = TICKS;
    }
}

// Draws the main menu screen (Puts in buffer only)
void draw_menu() 
{
    int i, j, zeroes;
    for (i = 0, j = 0; i < frame_sizes[11]; i++)
    {
        if (frames[11][i] == 0x00)
        {
            zeroes = frames[11][++i];
            if (zeroes == 0xFF)
                zeroes += frames[11][++i] + 1;
            for (; zeroes > 0; zeroes--)
                display_buffer[j++] = 0x00;
            continue;
        }
        display_buffer[j++] = frames[11][i];
    }
}

#include "helpers.h"

UBYTE font[3][130] = {
                {
                0x3e, 0x09, 0x09, 0x09, 0x3e, // A
                0x3f, 0x25, 0x25, 0x25, 0x1a, // B
                0x3f, 0x21, 0x21, 0x21, 0x21, // C
                0x3f, 0x21, 0x21, 0x21, 0x1e, // D
                0x3f, 0x25, 0x25, 0x25, 0x21, // E
                0x3f, 0x05, 0x05, 0x05, 0x01, // F
                0x3f, 0x21, 0x21, 0x29, 0x39, // G
                0x3f, 0x04, 0x04, 0x04, 0x3f, // H
                0x00, 0x21, 0x3f, 0x21, 0x00, // I
                0x31, 0x21, 0x21, 0x21, 0x3f, // J
                0x3f, 0x04, 0x0a, 0x11, 0x20, // K
                0x3f, 0x20, 0x20, 0x20, 0x00, // L
                0x3f, 0x01, 0x07, 0x01, 0x3f, // M
                0x3f, 0x02, 0x04, 0x08, 0x3f, // N
                0x3f, 0x21, 0x21, 0x21, 0x3f, // O
                0x3f, 0x05, 0x05, 0x05, 0x07, // P
                0x3f, 0x21, 0x21, 0x31, 0x3f, // Q
                0x3f, 0x05, 0x0d, 0x15, 0x27, // R
                0x27, 0x25, 0x25, 0x25, 0x3d, // S
                0x01, 0x01, 0x3f, 0x01, 0x01, // T
                0x1f, 0x20, 0x20, 0x20, 0x1f, // U
                0x07, 0x18, 0x20, 0x18, 0x07, // V
                0x3f, 0x20, 0x38, 0x20, 0x3f, // W
                0x21, 0x12, 0x0c, 0x12, 0x21, // X
                0x01, 0x02, 0x3c, 0x02, 0x01, // Y
                0x31, 0x29, 0x25, 0x23, 0x21  // Z
                },
                {
                0x3f, 0x23, 0x25, 0x29, 0x3f, // 0
                0x00, 0x22, 0x3f, 0x20, 0x00, // 1
                0x3d, 0x25, 0x25, 0x25, 0x27, // 2
                0x21, 0x21, 0x25, 0x25, 0x3f, // 3
                0x0c, 0x0a, 0x09, 0x3f, 0x08, // 4
                0x27, 0x25, 0x25, 0x25, 0x3d, // 5
                0x3f, 0x25, 0x25, 0x25, 0x3d, // 6
                0x01, 0x01, 0x01, 0x01, 0x3f, // 7
                0x3f, 0x25, 0x25, 0x25, 0x3f, // 8
                0x27, 0x25, 0x25, 0x25, 0x3f,  // 9
                0x08, 0x08, 0x08, 0x08, 0x08  // -   
                },
                {0x0, 0x0, 0x0, 0x0, 0x0}
                };
/**
 * Prints the given string on the screen at a given position.
 * 
 * @param word Our word (or phrase) to print out
 * @param pos Our vec2 containing x and y position
 */
v2 prints(char *word, v2 pos) 
{
    int index, type, wordNum = 0, x = pos._1, y = pos._2;
    char letter;

    while(word[wordNum] != '\0') 
    {
        letter = word[wordNum++];
        if(letter >= 'A' && letter <= 'Z') // uppercase
        {
            type = 0;
            index = (letter - 'A')*5;
        }
        else if(letter >= '0' && letter <= '9') // number
        {
            type = 1;
            index = (letter - '0')*5;
        } 
        else if(letter == ' ') // space
        {
            type = 2;
            index = 0;
        }
        else if(letter == '-') // minus
        {
            type = 1;
            index = 50;
        }
        else 
        {
            // Char was not recognized
            return;
        }
        int i, j;
        for(i = 0; i < 5; i++) 
        {
            UBYTE col = font[type][index++];
            for(j = 0; j < 8; j++)
            {
                if (col & 1)
                    pixon(x + i, y + j);
                else
                    pixoff(x + i, y + j);
                
                col = col >> 1;
            } 
        }
        x += LETTER_WIDTH + 1; // Width of letter + space of 1 pixel
        if(x + LETTER_WIDTH >= 127) 
        {
            y += LETTER_HEIGHT+1; // Height of letter + space of 1 pixel
            x = 0;
        }
    }
    pos._1 = x;
    pos._2 = y;
    return pos;
}

/**
 * Prints out an integer on our screen at a given position
 *
 * @param num Our integer to print out
 * @param pos Our vec2 containing x and y position
 */
v2 printn(int num, v2 pos) 
{
    char num_array[12]; // Integer is max 10 digits + 1 negative (-) sign

    int i, digit, sign=0, index=10;
    for(i = 0; i < 12; i++) {
        num_array[i] = '\0';
    }
    
    // Check if integer is negative or not
    if(num < 0) 
    {
        sign = 1;
        num *= -1;
    } 
    // special case for 0
    if(num==0) 
    {
        num_array[index--] = '0';
    }
    // Turn integer into char array
    while(num != 0) 
    {
        digit = num % 10;
        num_array[index--] = digit + '0'; // Store digit as char
        num /= 10;
    }
    // insert negative sign if num < 0
    if(sign) 
    {
        num_array[index--] = '-';
    }
    // Take splice of num_array with values in them
    char subset[12-index];
    for(i = 0; i < 12-index; i++) 
    {
        subset[i] = num_array[index+i+1];
    }
    return prints(subset, pos);
}

v2 printsn(char *word, int num, v2 pos) 
{
    pos = prints(word, pos);
    pos._1 += LETTER_WIDTH+1;
    pos = printn(num, pos);
    return pos;
}

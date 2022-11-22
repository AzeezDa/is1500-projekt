#include "helpers.h"

// a-z, A-Z, 0-9
// TODO: Add special characters
BYTE font[8] = {0x5, 0x6, 0x7, 0x8,
                0x1, 0x2, 0x3, 0x4};

void prints(char *word, v2 pos) 
{
    int i = 0, index;
    while(word[i] != '\0') 
    {
        index = (word[i++] - 'A') << 2;

        int x = pos._1, y = pos._2;
        int i, j;
        for(i = index; i < index+4; i++) 
        {
            UBYTE col = font[i];
            for(j = 0; j < 8; j++)
            {
                if (col & 1)
                    pixon(x + i, y + j);
                else
                    pixoff(x  + i, y + j);
                
                col = col >> 1;
            } 
        }
    }
}
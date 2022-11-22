#include <helpers.h>

// a-z, A-Z, 0-9
BYTE font[62] = {0x0};

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
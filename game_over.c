#include "helpers.h"

#define GAMEOVER_X 38.0f

typedef struct _underscore
{
    UBYTE line[5];
    UBYTE y;
} Underscore;
Underscore underscore = {{0x01, 0x01, 0x01, 0x01, 0x01}, LETTER_HEIGHT*4+2};
char name[6] = {'A', ' ', 'A', ' ', 'A', '\0'};

void draw_underscore()
{
    int i, j;
    for (i = 0; i < LETTER_WIDTH; i++)
    {
        UBYTE col = underscore.line[i];
        for (j = 0; j < LETTER_HEIGHT; j++)
        {
            if (col & 1)
                pixon(UNDERSCORE_STATE + i, underscore.y + j);
            else
                pixoff(UNDERSCORE_STATE + i, underscore.y  + j);

            col = col >> 1;
        }
    }
}

void death_transition() 
{
    UBYTE pix;
    int i, j;
    for(i = 0; i < OLED_BUF_SIZE; i++) 
    {
        for(j = 0; j < 8; j++)
        {
            pix |= ((UFRAND > 0.5 ? 0x1 : 0x0) << j);
        }
        display_buffer[i] = pix;
        pix = 0;
    }
}

void display_game_over() 
{
    int score = 100; // JUST AN EXAMPLE
    v2 pos = {GAMEOVER_X, 0.0};
    prints("GAME OVER", pos);
    pos._1 = 0.0;
    pos._2 = LETTER_HEIGHT+3;
    printsn("SCORE", score, pos);
    pos._2 += LETTER_HEIGHT+3;
    pos = prints("YOUR NAME ", pos);
    prints(name, pos);
    draw_underscore();
}

void next_letter(int sign)
{
    if(UNDERSCORE_STATE == FIRST) 
    {
        name[0] += sign;
        if(name[0] > 'Z') 
        {
            name[0] = 'A';
        }
        else if (name[0] <= 'A') 
        {
            name[0] = 'Z';
        }
    } 
    else if(UNDERSCORE_STATE == SECOND) 
    {
        name[2] += sign;
        if(name[2] > 'Z') 
        {
            name[2] = 'A';
        }
        else if (name[2] <= 'A') 
        {
            name[2] = 'Z';
        }
    } 
    else 
    {
        name[4] += sign;
        if(name[4] > 'Z') 
        {
            name[4] = 'A';
        }
        else if (name[4] <= 'A') 
        {
            name[4] = 'Z';
        }
    }   
}

void reset_name() 
{
    int i;
    for(i = 0; i < 3; i++) {
        name[i*2] = 'A';
    }
}
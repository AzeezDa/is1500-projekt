#include "helpers.h"

// Given a x, y coordinate, set that pixel ON on the board
void pixon(const BYTE x, const BYTE y)
{
    // Determine which row the bit is (there are 8 bits in each row so we divide by 8)
    BYTE row = y >> 3; 

    // Multiply row by 128 (<< 7) to push it in the correct place Y position in the buffer (now at (0,Y)). Add X to push it to the correct column (X,Y)
    BYTE buf_coord = (row << 7) + x;

    // We want to know which bit of that byte we want to modify, so we get the last three bits (0-7) which tell us the bit offset aka modulo 8
    row = y & 7;

    // We push a one with that many steps forward in that byte in the buffer and or it to make it 1 at the specific bit
    display_buffer[buf_coord] |= 1 << row;
}

// Given a x, y coordinate, set that pixel OFF on the board
void pixoff(const BYTE x, const BYTE y)
{
    // Determine which row the bit is (there are 8 bits in each row so we divide by 8)
    BYTE row = y >> 3; 

    // Multiply row by 128 (<< 7) to push it in the correct place Y position in the buffer (now at (0,Y)). Add X to push it to the correct column (X,Y)
    BYTE buf_coord = (row << 7) + x;

    // We want to know which bit of that byte we want to modify, so we get the last three bits (0-7) which tell us the bit offset aka modulo 8
    row = y & 7;

    // We push a one with that many steps forward in that byte in the buffer and and it with the inverse of that byte to make it 0 at the specific bit
    display_buffer[buf_coord] &= ~(1 << row);
}
/**
 * Drawing a line using Bresenham's algorithm 
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void line_low(const BYTE x0, const BYTE y0, const BYTE x1, const BYTE y1, BYTE dx, BYTE dy) 
{
    BYTE yi = 1;
    if(dy < 0) 
    {
        BYTE yi = -1;
        dy = -dy;
    }
    BYTE D = (2 * dy) - dx;
    BYTE y = y0;

    BYTE x;
    for(x = x0; x <= x1; x++) 
    {
        // plot(x, y)
        BYTE row = y >> 3; 
        BYTE buf_coord = (row << 7) + x;
        row = y & 7;
        display_buffer[buf_coord] |= 1 << row;

        if(D > 0) 
        {
            y += yi;
            D += 2 * (dy - dx);
        }
        else 
        {
            D += 2 * dy;
        }
    }
}

void line_high(const BYTE x0, const BYTE y0, const BYTE x1, const BYTE y1, BYTE dx, const BYTE dy) 
{
    BYTE xi = 1;
    if(dx < 0) 
    {
        xi = -1;
        dx = -dx;
    }
    BYTE D = (2 * dx) - dy;
    BYTE x = x0;

    BYTE y;
    for(y = y0; y <= y1; y++) 
    {
        // plot(x, y)
        BYTE row = y >> 3; 
        BYTE buf_coord = (row << 7) + x;
        row = y & 7;
        display_buffer[buf_coord] |= 1 << row;
 
        if(D > 0) 
        {
            x += xi;
            D += 2 * (dx - dy);
        }
        else 
        {
            D += 2*dx;
        }
    }

}
/**
 * Draws a line between the poBYTEs (x0, y0) and (x1, y1) using Bresenham's line algorithm .
 */
void draw_line(const BYTE x0, const BYTE y0, const BYTE x1, const BYTE y1) 
{
    BYTE dx = x1 - x0;
    BYTE dy = y1 - y0;
    BYTE sub_y = dy > 0 ? dy : -dy;
    BYTE sub_x = dx > 0 ? dx : -dx;
    if(sub_y < sub_x) 
    {
        if(x0 > x1) 
        {
            line_low(x1, y1, x0, y0, dx, dy);
        }
        else 
        {
            line_low(x0, y0, x1, y1, dx, dy);
        }
    } 
    else 
    {
        if(y0 > y1) 
        {
            line_high(x1, y1, x0, y0, dx, dy);
        } 
        else 
        {
            line_high(x0, y0, x1, y1, dx, dy);
        }
    }
}
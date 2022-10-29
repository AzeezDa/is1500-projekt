#include "helpers.h"

// Given a x, y coordinate, set that pixel ON on the board
void pixon(const BYTE x, const BYTE y)
{
    // Determine which row the bit is (there are 8 bits in each row so we divide by 8)
    BYTE row = y >> 3; 

    // Multiply row by 128 (<< 7) to push it in the correct place Y position in the buffer (now at (0,Y)). Add X to push it to the correct column (X,Y)
    int buf_coord = (row << 7) + x;

    // We want to know which bit of that int we want to modify, so we get the last three bits (0-7) which tell us the bit offset aka modulo 8
    row = y & 7;

    // We push a one with that many steps forward in that int in the buffer and or it to make it 1 at the specific bit
    display_buffer[buf_coord] |= 1 << row;
}

// Given a x, y coordinate, set that pixel OFF on the board
void pixoff(const BYTE x, const BYTE y)
{
    // Determine which row the bit is (there are 8 bits in each row so we divide by 8)
    BYTE row = y >> 3; 

    // Multiply row by 128 (<< 7) to push it in the correct place Y position in the buffer (now at (0,Y)). Add X to push it to the correct column (X,Y)
    int buf_coord = (row << 7) + x;

    // We want to know which bit of that int we want to modify, so we get the last three bits (0-7) which tell us the bit offset aka modulo 8
    row = y & 7;

    // We push a one with that many steps forward in that int in the buffer and and it with the inverse of that int to make it 0 at the specific bit
    display_buffer[buf_coord] &= ~(1 << row);
}
/**
 * Drawing a line using Bresenham's algorithm 
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void line_low(const int x0, const int y0, const int x1, const int y1, int dx, int dy) 
{
    int yi = 1;
    if(dy < 0) 
    {
        int yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = y0;

    int x;
    for(x = x0; x <= x1; x++) 
    {
        // plot(x, y)
        int row = y >> 3; 
        int buf_coord = (row << 7) + x;
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

void line_high(const int x0, const int y0, const int x1, const int y1, int dx, const int dy) 
{
    int xi = 1;
    if(dx < 0) 
    {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x0;

    int y;
    for(y = y0; y <= y1; y++) 
    {
        // plot(x, y)
        int row = y >> 3; 
        int buf_coord = (row << 7) + x;
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
 * Draws a line between the points (x0, y0) and (x1, y1) using Bresenham's line algorithm .
 */
void draw_line(const int x0, const int y0, const int x1, const int y1) 
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int sub_y = dy > 0 ? dy : -dy;
    int sub_x = dx > 0 ? dx : -dx;
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

// Clears the buffer by making all its values to 0
void clear_buf() {
    int i;
    for (i = 0; i < OLED_BUF_SIZE; i++)
        display_buffer[i] = 0;
}

void draw_rectangle(const rect r)
{
    draw_line(r.x, r.y, r.x + r.w, r.y); // Top
    draw_line(r.x, r.y + r.h, r.x + r.w, r.y + r.h); // Bottom
    draw_line(r.x, r.y, r.x, r.y + r.h); // Left
    draw_line(r.x + r.w, r.y, r.x + r.w, r.y + r.h); // Right
}

// Draws the given rectangle transformed by a given matrix at the specified origin
void draw_rectangle_m(const rect r, const m2x2 m, const v2 o)
{
    v2 ul = {r.x - o._1,        r.y - o._2},
       ur = {r.x + r.w - o._1,  r.y - o._2},
       bl = {r.x - o._1,        r.y + r.h - o._2},
       br = {r.x + r.w - o._1,  r.y + r.h - o._2};

    ul = vmulm(m, ul);
    ur = vmulm(m, ur);
    bl = vmulm(m, bl);
    br = vmulm(m, br);

    draw_line(ul._1 + o._1, ul._2 + o._2, ur._1 + o._1, ur._2 + o._2); // Top
    draw_line(bl._1 + o._1, bl._2 + o._2, br._1 + o._1, br._2 + o._2); // Bottom
    draw_line(ul._1 + o._1, ul._2 + o._2, bl._1 + o._1, bl._2 + o._2); // Left
    draw_line(ur._1 + o._1, ur._2 + o._2, br._1 + o._1, br._2 + o._2); // Right
}
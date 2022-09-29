#include "helpers.h"

// Given a x, y coordinate, set that pixel ON on the board
void pixon(const BYTE x, const BYTE y)
{
    // Determine which row the bit is (there are 8 bits in each row so we divide by 8)
    BYTE row = y >> 3; 

    // Multiply row by 128 (<< 7) to push it in the correct place Y position in the buffer (now at (0,Y)). Add X to push it to the correct column (X,Y)
    int buf_coord = (row << 7) + x;

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
    int buf_coord = (row << 7) + x;

    // We want to know which bit of that byte we want to modify, so we get the last three bits (0-7) which tell us the bit offset aka modulo 8
    row = y & 7;

    // We push a one with that many steps forward in that byte in the buffer and and it with the inverse of that byte to make it 0 at the specific bit
    display_buffer[buf_coord] &= ~(1 << row);
}
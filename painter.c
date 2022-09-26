#include "helpers.h"

// Given a x, y coordinate, set that pixel ON on the board
void pixon(const BYTE x, const BYTE y)
{
    BYTE bit_offset = y >> 3;
    int buf_coord = (bit_offset << 7) + x;
    bit_offset = y - (bit_offset << 3);
    display_buffer[buf_coord] |= 1 << bit_offset;
}

// Given a x, y coordinate, set that pixel OFF on the board
void pixoff(const BYTE x, const BYTE y)
{
    BYTE bit_offset = y >> 3;
    int buf_coord = (bit_offset << 7) + x;
    bit_offset = y - (bit_offset << 3);
    display_buffer[buf_coord] &= ~(1 << bit_offset);
}
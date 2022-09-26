#include "helpers.h"

void pixon(BYTE x, BYTE y) {
    BYTE bit_offset = y >> 3;
    int buf_coord = (bit_offset << 7) + x;
    bit_offset = y - (bit_offset << 3);
    displayBuffer[buf_coord] |= 1 << bit_offset;
}

void pixoff(BYTE x, BYTE y) {
    BYTE bit_offset = y >> 3;
    int buf_coord = (bit_offset << 7) + x;
    bit_offset = y - (bit_offset << 3);
    displayBuffer[buf_coord] &= ~(1 << bit_offset);
}
#include "helpers.h"

UBYTE display_buffer[512];

typedef struct Car {
    UBYTE car_arr[14];
} Car;
Car car = {{0x70, 0xc8, 0xe8, 0xfe, 0x79, 0x49, 0x4b, 0x4b, 0x49, 0x79, 0xfe, 0xe8, 0xc8, 0x70}};

void draw_car(const UBYTE x, const UBYTE y) 
{
    // Check validity of coordinates (Could be made faster?)
    if(x < 0 || x > 114 || y < 0 || y > 31) return;
    UBYTE bit = 1;
    for(int i = 0; i < 14; i++) 
    {
        for(int j = 0; j < 8; j++) 
        {
            int row = (j + y) >> 3; 
            int buf_coord = (row << 7) + i + x;  
            row = (y + j) & 7;

            display_buffer[buf_coord] |= (1 << row) & car.car_arr[i];
            bit = bit >> 1;
        } 
        bit = 1;
        printf("\n");
    }
}

int main(void) 
{
    draw_car(0, 0);

    printf("\n");
    for(int i = 0; i < 512; i++) 
    {
        printf("0x%x, ", display_buffer[i]);
    }

    return 0;
}
#include "helpers.h"

Car car = {{0x70, 0xc8, 0xe8, 0xfe, 0x79, 0x49, 0x4b, 0x4b, 0x49, 0x79, 0xfe, 0xe8, 0xc8, 0x70}};

void init_car() 
{
    car.pos._1 = 60;
    car.pos._2 = 23;
    car.turn_speed = 0.001f;
}

void draw_car() 
{
    // Check validity of coordinates (Could be made faster?)
    if(car.pos._1  < 0 || car.pos._1  > 114 || car.pos._2 < 0 || car.pos._2 > 31) return;
    int i, j;
    for(i = 0; i < 14; i++) 
    {
        UBYTE col = car.car_arr[i];
        for(j = 0; j < 8; j++) 
        {
            if (col & 1)
                pixon(car.pos._1 + i, car.pos._2 + j);
            else
                pixoff(car.pos._1  + i, car.pos._2 + j);
            
            col = col >> 1;
        } 
    }
}

void turn_right(const float speed) 
{
    float new_pos = car.pos._1 + speed;
    if(new_pos > 113) {
        car.pos._1 = 113;
        return;
    }
    car.pos._1 = new_pos;
}
void turn_left(const float speed) 
{
    float new_pos = car.pos._1 - speed;    
    if(new_pos < 0) {
        car.pos._1 = 0;
        return;
    }
    car.pos._1 = new_pos;
}
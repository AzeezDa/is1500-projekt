#include "helpers.h"

Car car;

void init_car() 
{
    car.pos._1 = 60;
    car.pos._2 = 23;
    car.turn_speed = 0.001f;
    car.texture = &frame_car;
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
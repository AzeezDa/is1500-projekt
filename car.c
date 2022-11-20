#include "helpers.h"

typedef struct _npc_car 
{
    Texture *frame1;
    Texture *frame2;
    Texture *frame3;
    Texture *frame3_l;
    Texture *frame3_r;
    v2 pos;
    float speed;
} npc_car;
v2 pos = {0.0, 0.0};
float speed = 0;
npc_car npc = {frame1, frame2, frame3, frame3_l, frame3_r, pos, speed};

void draw_npc() 
{
    float new_pos = car.pos._1 + car.turn_speed;
    if(new_pos > 113) {
        car.pos._1 = 113;
        return;
    }
    npc.pos._1 += npc.speed;
    nps.pos._2 += npc.speed;
}
void turn_left() 
{
    float new_pos = car.pos._1 - car.turn_speed;    
    if(new_pos < 0) {
        car.pos._1 = 0;
        return;
    }
    car.pos._1 = new_pos;
}
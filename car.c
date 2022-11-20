#include "helpers.h"

npc_car npc;

Car car;

void init_cars()
{
    npc.texture = &frame1;
    npc.speed = 0.001f;
    npc.lane = 20;
    npc.pos._1 = 60;
    npc.pos._2 = 0; 
}

void update_npc()
{
    npc.pos._2 += npc.speed;
    int i;
    for (i = 7; i >= 0; --i)
    {
        if (npc.pos._2 > i * 4) {
            float inv_persp0 = 1.0 - PERSP[i];
            float mid0 = 0.5 + road_curve * inv_persp0 * inv_persp0 * inv_persp0;
            int center0 = mid0 * SCREEN_X_MAX;
            
            int dx0 = npc.lane * PERSP[i];

            npc.pos._1 = center0 + dx0;
            break;
        }
    }
    
    if (npc.pos._2 > 16.0)
        npc.texture = &frame3;
    else if (npc.pos._2 > 10.0)
        npc.texture = &frame2;

    if (npc.pos._2 > 32.0) {
        npc.pos._2 = UFRAND * -20.0;
        npc.texture = &frame1;
        npc.lane = rand() % 40 - 20;
    }
        
}

void init_player() 
{
    car.pos._1 = 60;
    car.pos._2 = 23;
    car.turn_speed = 0.005f;
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
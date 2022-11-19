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
    if(y <= 4) {
        draw(npc.pos, npc.frame1);
    } else if(y <= 14) {
        draw(npc.pos, npc.frame2);
    } else {
        // Need to add different frames for turning
        draw(npc.pos, npc.frame3);
    }
    npc.pos._1 += npc.speed;
    nps.pos._2 += npc.speed;
}

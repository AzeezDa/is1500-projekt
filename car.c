#include "helpers.h"

// A pool of the npcs to be recycles when they exit the screen
npc_car npcs[CARS_AMOUNT];
// Player's car.. VROOM VROOM
Car car;

// Inits the npcars with a random position and speed
void init_npcs()
{
    int i;
    for (i = 0; i < CARS_AMOUNT; i++)
    {
        npcs[i].texture = &frame1; // Smallest car texture
        npcs[i].speed = UFRAND * 0.0008f + 0.001f;

        // Random deviation from center line in [-20, 20]
        npcs[i].lane =  rand() % 40 - 20;
        npcs[i].pos._1 = 0.0;

        // Negative position outside the screen. It gives some interval between each incoming car rather 
        // than immediately spawning a new one after it exits from bottom
        npcs[i].pos._2 = -50.0; 
    }
}

// Draws the npcars at their given positions
void draw_npcs()
{
    int i;
    for (i = 0; i < CARS_AMOUNT; i++)
        draw(npcs[i].pos, npcs[i].texture);
}

// Update the npcars positions
void update_npc()
{
    int i;
    for (i = 0; i < CARS_AMOUNT; i++)
    {   
        
        npcs[i].pos._2 += npcs[i].speed;

        // Adding this will flucuate the clock cycles / main loop making the speed of other things faster
        // TODO: FIX WITH DELTA TIME?
        // if (npcs[i].pos._2 < 0.0)
        //     continue;

        // Calculate deviation from center using cubic interpolation (same as in the road)
        float persp = PERSPECTIVE_CONSTANT + npcs[i].pos._2 / SCREEN_Y_MAX;
        float inv_persp = 1.0 - persp;
        float mid = 0.5 + road_curve * inv_persp * inv_persp * inv_persp;
        int center = mid * SCREEN_X_MAX;

        // Deviation from center
        int dx = npcs[i].lane * persp;
        npcs[i].pos._1 = center + dx;

        // Update texture based on closeness to bottom of screen
        // BIG CAR
        if (npcs[i].pos._2 > 16.0) 
        {
            // Back view
            npcs[i].texture = &frame3;

            // Display side ways view of car based on curvature
            if (current_curve._1 > 0.2)
                npcs[i].texture = &frame3_l;
            else if (current_curve._1 < -0.2)
                npcs[i].texture = &frame3_r;
        }
        else if (npcs[i].pos._2 > 10.0) // MEDIUM
            npcs[i].texture = &frame2;

        // If car exists the screen generate new values for it
        if (npcs[i].pos._2 > 32.0)
        {      
            // Generate new random distance and clamp it due to some bug :(
            npcs[i].pos._2 = UFRAND * -100.0;
            npcs[i].pos._2 = npcs[i].pos._2 < -100.0 ? -100.0 : npcs[i].pos._2;
            npcs[i].texture = &frame1; 
            npcs[i].lane = rand() % 40 - 20;
        }
    }
}

void init_player()
{
    car.pos._1 = 60;
    car.pos._2 = 23;
    car.turn_speed = 0.005f;
    car.texture = &frame_car;
}

// Both functions below can be reduced into one for the future cuz going outside crashes the car?

void turn_right(const float speed)
{
    float new_pos = car.pos._1 + speed;
    if (new_pos > 113)
    {
        car.pos._1 = 113;
        return;
    }
    car.pos._1 = new_pos;
}

void turn_left(const float speed)
{
    float new_pos = car.pos._1 - speed;
    if (new_pos < 0)
    {
        car.pos._1 = 0;
        return;
    }
    car.pos._1 = new_pos;
}
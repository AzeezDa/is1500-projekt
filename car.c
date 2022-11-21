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

// Update the npcars positions and returns 1 if a car crashed into the player
UBYTE update_npc()
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

        // Return 1 if cars overlap
        if (npcs[i].pos._2 > 20.0 && fabs(npcs[i].pos._1 - car.pos._1) < 14.0)
            return 1;

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

    return 0;
}

void init_player()
{
    car.pos._1 = 60;
    car.pos._2 = 23;
    car.turn_speed = 0.005f;
    car.texture = &frame_car;
}

// Turns (in the x direction) the car into the given velocity
inline void turn_car(const float velocity)
{
    car.pos._1 = car.pos._1 + velocity;
}
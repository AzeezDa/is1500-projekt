#include "helpers.h"

// A pool of the npcs to be recycles when they exit the screen
npc_car npcs[CARS_AMOUNT];
// Player's car.. VROOM VROOM
Car car;

#define PENDING_TARGET_LANE -1000000.0f
#define NO_TARGET_LANE -200000.0f

// Tuneable constants
#define ACCELERATION 0.00002f
#define FRICTION 0.000005f
#define NPC_LANE_SWITCH_RATIO 10 // 1/10 npcs change cars
#define LANE_CHANGING_SPEED 0.05f

// Inits the npcars with a random position and speed
void init_npcs()
{
    int i;
    for (i = 0; i < CARS_AMOUNT; i++)
    {
        npcs[i].texture = &frame1;                  // Smallest car texture
        npcs[i].speed = UFRAND * 0.0003f + 0.0005f; // Might need fine tuning
        npcs[i].speed *= CARS_AMOUNT;               // More cars on the road increase speed to handle the loses in clock cycles

        // Random deviation from center line in [-30, 30]
        npcs[i].lane = UFRAND * 60.0 - 30.0;
        npcs[i].target_lane = PENDING_TARGET_LANE;  
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
        npcs[i].pos._2 += npcs[i].speed + car.speed; // If the player moves fast, then npcs move faster from player POV (RELATIVITY BABY!!)

        // Calculate deviation from center using cubic interpolation (same as in the road)
        float persp = PERSPECTIVE_CONSTANT + npcs[i].pos._2 / SCREEN_Y_MAX;
        float inv_persp = 1.0 - persp;
        float mid = 0.5 + road_curve * inv_persp * inv_persp * inv_persp;
        float center = mid * SCREEN_X_MAX;

        // Deviation from center
        float dx = npcs[i].lane * persp;
        npcs[i].pos._1 = center + dx;

        // Lane changing of NPCars
        if (npcs[i].pos._2 > UFRAND * 10.0f && npcs[i].target_lane == PENDING_TARGET_LANE) // If within [0, 10] and still able to change lane, try to change lane
        {
            if (rand() % NPC_LANE_SWITCH_RATIO == 0) // Randomly choose to change lane
            {
                // Change to other lane based on position on road
                if (npcs[i].lane < 0.0)
                    npcs[i].target_lane = UFRAND * 30.0;
                else
                    npcs[i].target_lane = UFRAND * -30.0;
            }
            else
                npcs[i].target_lane = NO_TARGET_LANE; // If no succeed, never change lane for this NPC 
        }
        else if (npcs[i].target_lane != NO_TARGET_LANE || npcs[i].target_lane != PENDING_TARGET_LANE)
        {
            // Interpolate change from current to target
            float lane_diff = (npcs[i].target_lane - npcs[i].lane) * LANE_CHANGING_SPEED * CARS_AMOUNT;
            npcs[i].lane += lane_diff;
        }

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

            npcs[i].speed = UFRAND * 0.0003f + 0.0005f;
            npcs[i].speed *= CARS_AMOUNT;

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
    car.turn_speed = 0.004f * CARS_AMOUNT;
    car.speed = 0.0005f * CARS_AMOUNT; // Might need fine-tuning
    car.texture = &frame_car;
}

void update_player(const inputs i) // Inlineable?
{
    if (fabs(current_curve._1) > 0.1)
    {
        if (current_curve._1 > 0.0)
            turn_car(-car.turn_speed * current_curve._1);
        if (current_curve._1 < 0.0)
            turn_car(-car.turn_speed * current_curve._1);
    }

    if (i.b4)
        turn_car(-car.turn_speed);
    if (i.b3)
        turn_car(car.turn_speed);
    if (i.b2)
        car.speed += ACCELERATION * CARS_AMOUNT;
    if (i.b1)
        car.speed -= ACCELERATION * CARS_AMOUNT;

    car.speed -= FRICTION * CARS_AMOUNT;

    car.speed = clamp(car.speed, 0.0, PLAYER_MAX_SPEED * CARS_AMOUNT);
}

// Turns (in the x direction) the car into the given velocity
inline void turn_car(const float velocity)
{
    car.pos._1 = car.pos._1 + velocity;
}
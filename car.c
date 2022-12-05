#include "helpers.h"

// A pool of the npcs to be recycles when they exit the screen
npc_car npcs[CARS_AMOUNT];
// Player's car.. VROOM VROOM
Car car;

float distance_traveled = 0.0;

// Constants used for generating random npc lane changing
#define PENDING_TARGET_LANE -100000.0f
#define NO_TARGET_LANE -200000.0f

// Tuneable constants
#define ACCELERATION 0.00000002f
#define FRICTION 0.00000001f
#define CAR_TURN_SPEED 0.004f
#define NPC_SPEED_LOWER 0.0003f // Also initial speed of player's car
#define NPC_SPEED_UPPER 0.0008f
#define NPC_LANE_SWITCH_RATIO 3 // 1/10 npcs change lanes
#define LANE_CHANGING_SPEED 0.00005f

// Misc constants
#define SPEEDOMETER_BASE (~0x7FF)


// Inits the npcars with a random position and speed
void init_npcs()
{
    int i;
    for (i = 0; i < CARS_AMOUNT; i++)
    {
        npcs[i].texture = &frame1;                  // Smallest car texture
        npcs[i].speed = UFRAND * NPC_SPEED_LOWER + (NPC_SPEED_UPPER - NPC_SPEED_LOWER); // Might need fine tuning
        npcs[i].speed *= -CARS_AMOUNT;               // More cars on the road increase speed to handle the loses in clock cycles

        // Random deviation from center line in [-30, 30]
        npcs[i].lane = UFRAND * 60.0 - 30.0;
        npcs[i].target_lane = PENDING_TARGET_LANE;  
        npcs[i].pos._1 = 0.0;

        // Negative position outside the screen. It gives some interval between each incoming car rather
        // than immediately spawning a new one after it exits from bottom
        npcs[i].pos._2 = -10.0;
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
        float persp = PERSPECTIVE_CONSTANT + min(npcs[i].pos._2 / SCREEN_Y_MAX, 1.0);
        float inv_persp = 1.0 - persp;
        float mid = 0.5 + road_curve * inv_persp * inv_persp * inv_persp;
        float center = mid * SCREEN_X_MAX;

        // Deviation from center
        float dx = npcs[i].lane * persp;
        npcs[i].pos._1 = center + dx;

        // Lane changing of NPCars
        if (6.0 * UFRAND < npcs[i].pos._2 && npcs[i].pos._2 < 10.0 + 6.0 * UFRAND && npcs[i].target_lane == PENDING_TARGET_LANE) // If within [0, 10] and still able to change lane, try to change lane
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
        else if (npcs[i].target_lane != NO_TARGET_LANE && npcs[i].target_lane != PENDING_TARGET_LANE)
        {
            // Interpolate change from current to target
            float lane_diff = (npcs[i].target_lane - npcs[i].lane) * LANE_CHANGING_SPEED * CARS_AMOUNT;
            npcs[i].lane += lane_diff;
        }

        // Update texture based on closeness to bottom of screen
        if (npcs[i].pos._2 < 10.0)
            npcs[i].texture = &frame1;
        else if (npcs[i].pos._2 < 16.0)
            npcs[i].texture = &frame2;
        else {
            if (road_curve > 0.2)
                npcs[i].texture = &frame3_l;
            else if (road_curve < -0.2)
                npcs[i].texture = &frame3_r;
            else
                npcs[i].texture = &frame3;
        }

        // Return 1 if cars overlap
        if (20.0 < npcs[i].pos._2 && npcs[i].pos._2 < 33.0 && fabs(npcs[i].pos._1 - car.pos._1) < 14.0)
            return 1;

        // Have cars from behind always spawn not directly behind car
        if (npcs[i].pos._2 > 34.0) {
            float diff_to_center = car.pos._1 - SCREEN_X_MAX / 2.0;
            
            if (diff_to_center > 0.0)
                npcs[i].lane = -30.0 + diff_to_center * UFRAND;
            else
                npcs[i].lane = 30.0 + diff_to_center * UFRAND;

            npcs[i].target_lane = PENDING_TARGET_LANE;
        }

        // If car exists the screen generate new values for it
        if (npcs[i].pos._2 > 50.0 || npcs[i].pos._2 < -20.0)
        {
            // Generate new random distance
            if (npcs[i].speed + car.speed > 0)
                npcs[i].pos._2 = UFRAND * -20.0;
            else
                npcs[i].pos._2 = 40.0 + UFRAND * 10.0;

            npcs[i].speed = UFRAND * NPC_SPEED_LOWER + (NPC_SPEED_UPPER - NPC_SPEED_LOWER);
            npcs[i].speed *= -CARS_AMOUNT;
            npcs[i].target_lane = PENDING_TARGET_LANE;

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
    car.turn_speed = CAR_TURN_SPEED * CARS_AMOUNT;
    car.speed = NPC_SPEED_LOWER * CARS_AMOUNT; // Might need fine-tuning
    car.texture = &frame_car;
}

// Updates the player car. Includes curve inertia, steering, accelerating, braking, friction and speedometer
void update_player(const inputs i) // Inlineable?
{   
    // When car moves slow, it also steers slower
    const float steer_modulation = min(1.0, PLAYER_SPEED_RATIO * 2.0);

    // Simulate inertia by moving the car sideways when curving
    if (fabs(current_curve._1) > 0.1)
    {
        if (current_curve._1 > 0.0)
            turn_car(-car.turn_speed * current_curve._1 * steer_modulation);
        if (current_curve._1 < 0.0)
            turn_car(-car.turn_speed * current_curve._1 * steer_modulation);
    }

    // Sideways steering
    if (i.b4)
        turn_car(-car.turn_speed * steer_modulation);
    if (i.b3)
        turn_car(car.turn_speed * steer_modulation);

    // Forward speed
    if (i.b2)
        car.speed += ACCELERATION * CARS_AMOUNT;
    if (i.b1)
        car.speed -= ACCELERATION * CARS_AMOUNT;

    // Reduce speed if player is not accelerating
    car.speed -= FRICTION * CARS_AMOUNT;

    // Clamp the speed to [0, MAX]
    car.speed = clamp(car.speed, 0.0, PLAYER_MAX_SPEED * CARS_AMOUNT);
    distance_traveled += car.speed;

    // Simulate speedometer on chip leds
    int speedometer_full = SPEEDOMETER_BASE >> (int)(8 * PLAYER_SPEED_RATIO);
    leds l;
    l._all = speedometer_full & 0xFF;
    set_leds(l);
}

// Turns (in the x direction) the car into the given velocity
inline void turn_car(const float velocity)
{
    car.pos._1 = car.pos._1 + velocity;
}
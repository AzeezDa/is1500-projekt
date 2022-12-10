#include "helpers.h"

#define SCENARY_MIN_DISTANCE 200.0f
#define SCENARY_MAX_DISTANCE 400.0f
#define OBJECT_AMOUNT_MAX 8
#define FOREST_X_POS_MIN 55.0f
#define FOREST_X_POS_MAX 80.0f
#define DONKEN_X_POS_MIN 55.0f
#define DONKEN_X_POS_MAX 80.0f
#define FOREST_SPAWN -40.0f
#define DONKEN_SPAWN -100.0f

// If true, then the scenary is forest
UBYTE is_forest = 0;

// Determines how long the scenary goes on
float scenary_distance = 0.0;

// Used to have lamps in a uniform placement
float lamp_y = 0.0;

// Pool of objects in the scene
v2 object_positions[OBJECT_AMOUNT_MAX];

// Difference bettwen two lamps in the y axis
const float lamp_difference = SCREEN_Y_MAX / 3.0;

void init_scenary()
{
    // Randomly choose first scene
    is_forest = rand() % 2;

    scenary_distance = SCENARY_MIN_DISTANCE + UFRAND * (SCENARY_MAX_DISTANCE - SCENARY_MIN_DISTANCE);
    int i;
    for (i = 0; i < OBJECT_AMOUNT_MAX; i++)
    {
        object_positions[i]._2 = UFRAND * SCREEN_Y_MAX;
        if (is_forest)
            object_positions[i]._1 = FOREST_X_POS_MIN + UFRAND * (FOREST_X_POS_MAX - FOREST_X_POS_MIN);
        else
            object_positions[i]._1 = DONKEN_X_POS_MIN + UFRAND * (DONKEN_X_POS_MAX - DONKEN_X_POS_MIN);

        // Randomly choose side for the item
        if (rand() % 2)
            object_positions[i]._1 *= -1;
    }
}

void update_side()
{
    // Scenary changes based on how much the player car travels
    scenary_distance -= car.speed;
    lamp_y += car.speed;
    if (lamp_y > lamp_difference)
        lamp_y = -1.0;

    int i,
        outside_counter = 0; // Used to switch scenary after all current objects exit the screen
    for (i = 0; i < OBJECT_AMOUNT_MAX; i++)
    {
        object_positions[i]._2 += car.speed;

        // If scenary is finished but items are still on the scene, increment counter and don't give items new positions
        if (scenary_distance < 0.0 && object_positions[i]._2 > SCREEN_Y_MAX + 2.0)
        {
            outside_counter++;
            continue;
        }

        if (object_positions[i]._2 > SCREEN_Y_MAX + 10.0)
        {
            if (is_forest)
                object_positions[i]._2 = UFRAND * FOREST_SPAWN;
            else
                object_positions[i]._2 = UFRAND * DONKEN_SPAWN;

            if (is_forest)
                object_positions[i]._1 = FOREST_X_POS_MIN + UFRAND * (FOREST_X_POS_MAX - FOREST_X_POS_MIN);
            else
                object_positions[i]._1 = DONKEN_X_POS_MIN + UFRAND * (DONKEN_X_POS_MAX - DONKEN_X_POS_MIN);

            // Randomly choose which side of the road
            if (rand() % 2)
                object_positions[i]._1 *= -1;
        }
    }

    // Wait until all items are outside the screen, then reset scenary distance
    if (outside_counter == OBJECT_AMOUNT_MAX)
    {
        scenary_distance = SCENARY_MIN_DISTANCE + UFRAND * (SCENARY_MAX_DISTANCE - SCENARY_MIN_DISTANCE);
        is_forest = !is_forest; // Switch scenary
    }
}

void draw_side()
{
    v2 lamp_position = {0.0, lamp_y};
    int i;
    for (i = 0; i < 3; i++)
    {
        v2 pos = {ROAD_WIDTH + 10, lamp_y + lamp_difference * i};

        v2 center_dx = calc_persp(pos);

        v2 position = {center_dx._1 + center_dx._2, pos._2};
        int texture_index = 0;

        if (i == 1)
            texture_index = 2;
        else if (i == 2)
            texture_index = 4;

        draw(position, &lamp[texture_index]);
        position._1 = center_dx._1 - center_dx._2;
        draw(position, &lamp[texture_index + 1]);
    }

    // If forest display all items, else if buildings display half of that
    int max_objects = is_forest ? OBJECT_AMOUNT_MAX : OBJECT_AMOUNT_MAX / 2;
    for (i = 0; i < max_objects; i++)
    {
        v2 center_dx = calc_persp(object_positions[i]);

        texture *texture = &tree_f1;
        if (is_forest)
        {
            if (object_positions[i]._2 > 4.0)
                texture = &tree_f2;
            else if (object_positions[i]._2 > 8.0)
                texture = &tree_f3;
        }
        else
        {
            if (object_positions[i]._2 < 8.0)
                texture = &building_1;
            else
                texture = &building_2;
        }

        // - width/2 and - height are used to realign the texture origin to be drawn more "nicely"
        v2 position = {center_dx._1 + center_dx._2 - texture->width / 2.0f, object_positions[i]._2 - texture->height};
        draw(position, texture);
    }
}
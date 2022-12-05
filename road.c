#include "helpers.h"

/*
 CURVE ALGORITHM INSPIRED BY THE C++ LEGEND javidx9
 https://www.youtube.com/c/javidx9
*/

// v1 is how sharp the turn is and in which direction. v2 is how long the turn is
v2 current_curve = {0.0, 200.0};

// Store current road curve to allow interpolation
float road_curve = 0.0;


// Sets the road's curvature settings to default (0, 200)
void init_road()
{
    current_curve._1 = 0.0;
    current_curve._2 = 200.0;
    road_curve = 0.0;
}

void update_road()
{
    // Reduce from the curve length to emulate going through the turn
    current_curve._2 -= 0.3 * PLAYER_SPEED_RATIO;

    // Transition to next target curve from current curve
    float curve_diff = (current_curve._1 - road_curve) * 0.03 * PLAYER_SPEED_RATIO;
    road_curve += curve_diff;

    // Turn is finished, generate a new one!
    if (current_curve._2 < 0.0)
    {
        // Length in [100, 200]
        current_curve._2 = 100.0 + UFRAND * 100.0;

        // Modulate the curve sharpness to be lower for longer turns. I.e sharp turns, short distance. Straighter curves, longer distance.
        float modulation = 1.0 - current_curve._2 * 0.005;
        current_curve._1 = (UFRAND * 2.0 - 1.0) * modulation;
    }
}

void draw_road()
{
    // Interpolation per height. Basically skew the road based on height and curve amount.
    // There are X0, X1 for each value because they draw a line and each value is for line's two points

    float persp     = PERSPECTIVE_CONSTANT,
          inv_persp = 1.0 - persp,
          mid       = 0.5 + road_curve * inv_persp * inv_persp * inv_persp;

    int   center    = mid * SCREEN_X_MAX,
          dx        = ROAD_WIDTH * persp;

    // Based on the distance traveled create an index that is used to mark every fourth line segment and the one after it
    int center_index0 = (int)distance_traveled % 4,
        center_index1 = (center_index0 + 1) % 4;

    // The road is segmented into 32/4 = 8 lines
    int i, j;
    for (i = 0, j = 4; i < 7; i++, j += 4)
    {
        // Calculate new point for current line
        float persp1     = PERSPECTIVE_CONSTANT + (float)j / SCREEN_Y_MAX,
              inv_persp1 = 1.0 - persp1,
              mid1       = 0.5 + road_curve * inv_persp1 * inv_persp1 * inv_persp1;

        int   center1    = mid1 * SCREEN_X_MAX,
              dx1        = ROAD_WIDTH * persp1;

        // Draw left and right sides of the road
        draw_line(center - dx, j - 4, 
                  center1 - dx1, j);

        draw_line(center + dx, j - 4, 
                  center1 + dx1, j);

        // Draw line segements that are in the correct index
        int imod4 = i % 4;
        if (center_index0 == imod4 || center_index1 == imod4)
            draw_line(center, j - 4, center1, j);

        // Store current point for next line
        persp = persp1;
        inv_persp = inv_persp1;
        mid = mid1;
        center = center1;
        dx = dx1;
    }
}
#include "helpers.h"

/*
 CURVE ALGORITHM INSPIRED BY THE C++ LEGEND javidx9
 https://www.youtube.com/c/javidx9
*/

// v1 is how sharp the turn is and in which direction. v2 is how long the turn is
v2 current_curve = {0.0, 200.0};

// Store current road curve to allow interpolation
float road_curve = 0.0;



// Store list of perspective skew per height because they are used each draw routine
const float PERSP[8] = {PERSPECTIVE_CONSTANT,
                        PERSPECTIVE_CONSTANT + 0.125,
                        PERSPECTIVE_CONSTANT + 0.25,
                        PERSPECTIVE_CONSTANT + 0.375,
                        PERSPECTIVE_CONSTANT + 0.5,
                        PERSPECTIVE_CONSTANT + 0.625,
                        PERSPECTIVE_CONSTANT + 0.75,
                        PERSPECTIVE_CONSTANT + 0.875};

void update_road()
{
    // Reduce from the curve length to emulate going through the turn
    current_curve._2 -= 0.3;

    // Transition to next target curve from current curve
    float curve_diff = (current_curve._1 - road_curve) * 0.03;
    road_curve += curve_diff;

    // Turn is finished, generate a new one!
    if (current_curve._2 < 0.0)
    {
        // Length in [100, 200]
        current_curve._2 = 100.0 + UFRAND * 100.0;
        // Freaking RNG generating giga numbers sometimes :(
        current_curve._2 = current_curve._2 > 200.0 ? 200.0 : current_curve._2;

        // Modulate the curve sharpness to be lower for longer turns. I.e sharp turns, short distance. Straighter curves, longer distance.
        float modulation = 1.0 - current_curve._2 * 0.005;
        current_curve._1 = (UFRAND * 2.0 - 1.0) * modulation;

        // Again, wackeroni numbers to be clamped :/
        current_curve._1 = current_curve._1 > 1.0 ? 1.0 : current_curve._1;
        current_curve._1 = current_curve._1 < -1.0 ? -1.0 : current_curve._1;
    }
}

void draw_road()
{

    // The road is segmented into 32/4 = 8 lines
    int i, j;
    for (i = 0, j = 0; i < 7; i++, j += 4)
    {
        // Cubic interpolation per height. Basically skew the road based on height and curve amount.
        // There are X0, X1 for each value because they draw a line and each value is for line's two points
        float inv_persp0 = 1.0 - PERSP[i];
        float inv_persp1 = 1.0 - PERSP[i + 1];
        float mid0 = 0.5 + road_curve * inv_persp0 * inv_persp0 * inv_persp0;
        float mid1 = 0.5 + road_curve * inv_persp1 * inv_persp1 * inv_persp1;

        // Skewed center point of the road
        int center0 = mid0 * SCREEN_X_MAX;
        int center1 = mid1 * SCREEN_X_MAX;

        // Distance from center to each side
        int dx0 = ROAD_WIDTH * PERSP[i],
            dx1 = ROAD_WIDTH * PERSP[i + 1];

        // Draw left and right sides of the road
        draw_line(center0 - dx0, j, 
                  center1 - dx1, j + 4);
        draw_line(center0 + dx0, j, 
                  center1 + dx1, j + 4);
    }
}
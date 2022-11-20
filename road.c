#include "helpers.h"


v2 current_curve = {0.0, 200.0};
float road_curve = 0.0;

#define PERSPECTIVE_CONSTANT 0.3

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
    current_curve._2 -= 0.3;
    float diff = (current_curve._1 - road_curve) * 0.03;
    road_curve += diff;
    if (current_curve._2 < 0.0)
    {
        current_curve._2 = 100.0 + UFRAND * 100.0;

        float modulator = 1.0 - (current_curve._2 / 200.0);
        current_curve._1 = modulator * (UFRAND * 2.0 - 1.0);
    }
}

void draw_road()
{
    int road_width = 50;
    int i, j;
    for (i = 0, j = 0; i < 7; i++, j += 4)
    {
        float inv_persp0 = 1.0 - PERSP[i];
        float inv_persp1 = 1.0 - PERSP[i + 1];
        float mid0 = 0.5 + road_curve * inv_persp0 * inv_persp0 * inv_persp0;
        float mid1 = 0.5 + road_curve * inv_persp1 * inv_persp1 * inv_persp1;

        int center0 = mid0 * SCREEN_X_MAX;
        int center1 = mid1 * SCREEN_X_MAX;
        
        int dx0 = road_width * PERSP[i],
            dx1 = road_width * PERSP[i+1];

        draw_line(center0 - dx0, j, 
                  center1 - dx1, j + 4);
        draw_line(center0 + dx0, j, 
                  center1 + dx1, j + 4);
    }
    
}
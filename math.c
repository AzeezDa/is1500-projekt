#include "helpers.h"

// Represent float as a integer to be able to access its bits
#define FLOAT_AS_INT(N) \
    union               \
    {                   \
        float f;        \
        int i;          \
    } N

    
const v2 VZERO = {0.0, 0.0};

// Returns |x|
float fabs(const float x)
{
    FLOAT_AS_INT(xint);
    xint.f = x;
    xint.i &= 0x7FFFFFFF;
    return xint.f;
}

float clamp(const float x, const float lower, const float upper)
{
    if (x < lower)
        return lower;
    if (x > upper)
        return upper;

    return x;
}

v2 calc_persp(const v2 pos)
{
    float persp = PERSPECTIVE_CONSTANT + pos._2 / SCREEN_Y_MAX,
              inv_persp = 1.0 - persp,
              mid = 0.5 + road_curve * inv_persp * inv_persp * inv_persp;

    v2 center_dx = {mid * SCREEN_X_MAX, pos._1 * persp};

    return center_dx;
}
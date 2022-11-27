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
float fabs(float x)
{
    FLOAT_AS_INT(xint);
    xint.f = x;
    xint.i &= 0x7FFFFFFF;
    return xint.f;
}

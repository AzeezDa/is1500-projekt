#include "helpers.h"

// Represent float as a integer to be able to access its bits
#define FLOAT_AS_INT(N) \
    union               \
    {                   \
        float f;        \
        int i;          \
    } N

// 32-bit float Not A Number according to IEEE 754 standard
#define NAN 0x7ff80000

// Mask to access a 32-bit float's sign bit
#define SIGN_BIT_MASK 0x80000000

// Coefficients used to calculate sine
#define CHEBY_4  0.0287138152563782f
#define CHEBY_3 -0.2035809070988712f
#define CHEBY_2  0.0199652533154854f
#define CHEBY_1  0.9961500530366957f
#define CHEBY_0  0.0001205256774430f

// Identity 2x2 Matrix
const m2x2 IMATRIX2 = {1.0, 0.0, 0.0, 1.0}; 

// Transposes a 2x2 Matrix
m2x2 transpose(m2x2 mat)
{
    float t = mat._12;
    mat._12 = mat._21;
    mat._21 = t;
    return mat;
}

// Applies the reflection-around-x-axis matrix on given matrix and returns that matrix
m2x2 relfectx(m2x2 mat)
{
    mat._22 = -mat._22;
    mat._21 = -mat._21;
    return mat;
}

// Applies the reflection-around-y-axis matrix on given matrix and returns that matrix
m2x2 relfecty(m2x2 mat)
{
    mat._11 = -mat._11;
    mat._12 = -mat._12;
    return mat;
}

// Returns the result of multiplying two matrices m1 * m2 (in that order).
m2x2 mmul(const m2x2 m1, const m2x2 m2)
{
    m2x2 m = {
        m2._11 * m1._11 + m2._21 * m1._12, m2._12 * m1._11 + m2._22 * m1._12,
        m2._11 * m1._21 + m2._21 * m1._22, m2._12 * m1._21 + m2._22 * m1._22};
    return m;
}

// Given a matrix2 m an and a scalar s, return s*m
m2x2 mscale(m2x2 m, const float s)
{
    m._11 *= s;
    m._12 *= s;
    m._21 *= s;
    m._22 *= s;
    return m;
}

// Given a vector2 v an and a scalar s, return s*v
v2 vscale(v2 v, const float s)
{
    v._1 *= s;
    v._2 *= s;
    return v;
}

// Return sqrt(x), accurate up to around x ~= 10^6
float sqrt(float x)
{
    FLOAT_AS_INT(xint);
    xint.f = x;

    // A somewhat-good initial guess is using binary logarithm estimate from the float's exponent bits then multply by 4.
    int x0i = (((xint.i & 0x7F800000) >> 23) - 127) << 2;
    int xi = x;
    float x0 = x0i;

    // 5 iterations of Newton's Method
    x0 = x0 - (x0 * x0 - x) / (2 * x0);
    x0 = x0 - (x0 * x0 - x) / (2 * x0);
    x0 = x0 - (x0 * x0 - x) / (2 * x0);
    x0 = x0 - (x0 * x0 - x) / (2 * x0);
    x0 = x0 - (x0 * x0 - x) / (2 * x0);
}

// Given a vector2 v, return the norm ||v||
float norm(const v2 v)
{
    float sumofsqrs = v._1 * v._1 + v._2 * v._2;
    return sqrt(sumofsqrs);
}

// Given a matrix2 m and a vector2 v, return m*v;
v2 vmulm(const m2x2 m, const v2 v)
{
    v2 vr = {
        v._1 * m._11 + v._2 * m._12,
        v._1 * m._21 + v._2 * m._22};

    return vr;
}

// Returns |x|
float abs(float x)
{
    FLOAT_AS_INT(xint);
    xint.f = x;
    xint.i &= 0x7FFFFFFF;
    return xint.f;
}

// Returns sin(x) of a given function with error of around 10^4 (not entirely tested)
float sin(float x)
{
    FLOAT_AS_INT(xint);
    xint.f = x;
    char sign = (xint.i & SIGN_BIT_MASK) == SIGN_BIT_MASK;
    xint.i &= 0x7FFFFFFF;
    x = xint.f;

    // Reduce to [0, 2pi]
    float flrx = (int)(x / C_2PI);
    x = x - C_2PI * flrx;

    // Reduce to [0, pi]
    if (x > C_PI)
    {
        sign = !sign;
        x -= C_PI;
    }

    // Reduce to [0, pi/2]
    if (x > C_PI_2)
        x = C_PI - x;

    // sinx = x gives error less than machine eps for range below
    if (x < 0.00711379)
        return sign ? -x : x;

    // Error less than ~10^-4 for range below
    if (x < 0.301)
    {
        x = x - (x * x * x) / 6; // Taylor expansion of term 3
        return sign ? -x : x;
    }

    // Use interpolation with Chebychev nodes on the interval [0, pi/2]
    if (x < C_PI_2)
    {
        float cheby = CHEBY_4;
        cheby = x * cheby + CHEBY_3;
        cheby = x * cheby + CHEBY_2;
        cheby = x * cheby + CHEBY_1;
        cheby = x * cheby + CHEBY_0;
        return sign ? -cheby : cheby;
    }

    return NAN; // Should never occur
}

float cos(float x)
{
    return sin(C_PI_2 - x);
}
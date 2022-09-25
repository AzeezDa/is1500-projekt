#define FLOAT_AS_INT(N) union {float f; int i; } N

#define C_3PI   9.4247779607693797153f
#define C_2PI   6.2831853071795864769f
#define C_PI    3.1415926535897932385f
#define C_PI_2  1.5707963267948966192f
#define C_PI_4  0.7853981633974483096f
#define C_SQRT2 1.4142135623730950488f

#define NAN 0x7ff80000

#define SGN_BIT 0x80000000

#define CHEBY_4  0.0287138152563782f
#define CHEBY_3 -0.2035809070988712f
#define CHEBY_2  0.0199652533154854f
#define CHEBY_1  0.9961500530366957f
#define CHEBY_0  0.0001205256774430f

typedef union _matrix2x2 {
    float m[2][2];
    struct {float _11, _12, _21, _22;};
} m2x2;

const m2x2 IDENTMTRX = {1.0, 0.0, 1.0, 0.0};

typedef union _vec2 {
    float m[2];
    struct {float _1, _2};
} v2;

m2x2 transpose(m2x2 mat) {
    float t = mat._12;
    mat._12 = mat._21;
    mat._21 = t;
    return mat;
}

m2x2 mirrorx(m2x2 mat) {
    mat._22 = -mat._22;
    mat._21 = -mat._21;
    return mat;
}

m2x2 mirrory(m2x2 mat) {
    mat._11 = -mat._11;
    mat._12 = -mat._12;
    return mat;
}

m2x2 mmul(const m2x2 *m1, const m2x2 *m2) {
    m2x2 m = {
        m2->_11*m1->_11 + m2->_21*m1->_12, m2->_12*m1->_11 + m2->_22*m1->_12,
        m2->_11*m1->_21 + m2->_21*m1->_22, m2->_12*m1->_21 + m2->_22*m1->_22
    };
    return m;
}

m2x2 mscale(m2x2 m, const float s) {
    m._11 *= s;
    m._12 *= s;
    m._21 *= s;
    m._22 *= s;
    return m;
}

v2 vscale(v2 v, const float s) {
    v._1 *= s;
    v._2 *= s;
    return v; 
}

float sqrt(float x) {
    FLOAT_AS_INT(xint);
    xint.f = x;
    int x0i = (((xint.i & 0x7F800000) >> 23) - 127) << 2;
    int xi = x;
    float x0 = x0i;

    x0 = x0 - (x0 * x0 - x) / (2*x0);
    x0 = x0 - (x0 * x0 - x) / (2*x0);
    x0 = x0 - (x0 * x0 - x) / (2*x0);
    x0 = x0 - (x0 * x0 - x) / (2*x0);
    x0 = x0 - (x0 * x0 - x) / (2*x0); 
}

float vmag(const v2 *v) {
    float sumofsqrs = v->_1 * v->_1 + v->_2 * v->_2;
    return sqrt(sumofsqrs); 
}

v2 vmulm(const m2x2 *m, const v2 *v) {
    v2 vr = {
        v->_1*m->_11 + v->_2*m->_12,
        v->_1*m->_21 + v->_2*m->_22
    };

    return vr;
}

float abs(float x) {
    FLOAT_AS_INT(xint);
    xint.f = x;
    xint.i &= 0x7FFFFFFF;
    return xint.f;
}

float sin(float x) {
    FLOAT_AS_INT(xint);
    xint.f = x;
    char sign = (xint.i & SGN_BIT) == SGN_BIT;
    xint.i &= 0x7FFFFFFF;
    x = xint.f;

    // Reduce to [0, 2pi]
    float flrx = (int)(x/C_2PI);
    x = x - C_2PI * flrx;

    // Reduce to [0, pi]
    if (x > C_PI) {
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
    if (x < 0.301) {
        x = x - (x*x*x)/6; // Taylor expansion of term 3
        return sign ? -x : x;
    }

    // Use interpolation with Chebychev nodes on the interval [0, pi/2]
    if (x < C_PI_2) {
        float cheby = CHEBY_4;
        cheby = x*cheby + CHEBY_3;
        cheby = x*cheby + CHEBY_2;
        cheby = x*cheby + CHEBY_1;
        cheby = x*cheby + CHEBY_0;
        return sign ? -cheby : cheby;
    }

    return NAN; // Should never occur
}

float cos(float x) {
    return sin(C_PI_2 - x);
}
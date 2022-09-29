#ifndef HELPERS
#define HELPERS

// GENERAL DEFINITIONS
#define BYTE char


/*
 * This header file defines functions that should be accessible from outside
 */

/* ==========================================
 * |             OLED HELPERS               |
 * ==========================================
 */
#define OLED_BUF_SIZE 512

#ifndef OLED_FILE
extern BYTE display_buffer[OLED_BUF_SIZE];
#endif

void oled_update();
void oled_put_buffer();
void oled_power_off();
void init();

/* ==========================================
 * |             MATHEMATICS                |
 * ==========================================
 */

// CONSTANTS
#define C_2PI   6.283185307179586476925286766559005768394338798750211641949889184615632812572417997256069650684234136f
#define C_PI    3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068f
#define C_PI_2  1.570796326794896619231321691639751442098584699687552910487472296153908203143104499314017412671058534f
#define C_PI_4  0.785398163397448309615660845819875721049292349843776455243736148076954101571552249657008706335529267f
#define C_SQRT2 1.414213562373095048801688724209698078569671875376948073176679737990732478462107038850387534327641573f

// 2x2 32-bit Float Matrix
typedef union _matrix2x2
{
    float m[2][2];
    struct
    {
        float _11, _12, _21, _22;
    };
} m2x2;

// 32-bit float 2D Vector
typedef union _vec2
{
    float m[2];
    struct
    {
        float _1, _2;
    };
} v2;

const m2x2 IDENTMATRIX2;

m2x2 transpose(m2x2);
m2x2 relfectx(m2x2);
m2x2 relfecty(m2x2);
m2x2 mmul(const m2x2, const m2x2);
m2x2 mscale(m2x2, const float);
v2 vscale(v2, const float);
float sqrt(float);
float norm(const v2);
v2 vmulm(const m2x2, const v2);
float abs(float);
float sin(float);
float cos(float);

/* ==========================================
 * |               PAINTER                  |
 * ==========================================
 */

void pixon(const BYTE, const BYTE);
void pixoff(const BYTE, const BYTE);
void draw_line(const int x0, const int y0, const int x1, const int y1);
void line_high(const int x0, const int y0, const int x1, const int y1, int dx, const int dy); // INTERNAL
void line_low(const int x0, const int y0, const int x1, const int y1, const int dx, int dy); // INTERNAL



#endif // HELPERS
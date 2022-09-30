#ifndef HELPERS
#define HELPERS

// GENERAL DEFINITIONS
#define BYTE char
#define UBYTE unsigned char


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
void oled_init();

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
unsigned rand();

/* ==========================================
 * |               PAINTER                  |
 * ==========================================
 */

void pixon(const BYTE, const BYTE);
void pixoff(const BYTE, const BYTE);
void clear_buf();

/* ==========================================
 * |              IO_DEVICES                |
 * ==========================================
 */

void init();

// Struct that includes buttons and switches
// The 8 bit fields: For x in 1..4: bx is for the buttons and sx are for the buttons
// The buttons and switches fields: a nibble representing the 4 buttons and the 4 switches
// The _all field: a byte of all 8 buttons and switches
typedef union _inputs
{
    struct
    {
        UBYTE b1 : 1;
        UBYTE b2 : 1;
        UBYTE b3 : 1;
        UBYTE b4 : 1;
        UBYTE s1 : 1;
        UBYTE s2 : 1;
        UBYTE s3 : 1;
        UBYTE s4 : 1;
    };

    struct {
        UBYTE buttons  : 4;
        UBYTE switches : 4;
    };

    UBYTE _all;
} inputs;

// The leds struct includes 8 bit fields each representing the LEDs on the chip
// Each fields number is the same as the number written on the chip, i.e _1 is LD1
typedef union _leds {
    struct {
        UBYTE _1 : 1;
        UBYTE _2 : 1;
        UBYTE _3 : 1;
        UBYTE _4 : 1;
        UBYTE _5 : 1;
        UBYTE _6 : 1;
        UBYTE _7 : 1;
        UBYTE _8 : 1;
    };
    UBYTE _all;
} leds;

void bsl_init();
inputs get_inputs();
inline void set_leds(leds);

#endif // HELPERS
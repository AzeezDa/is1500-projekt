#ifndef HELPERS
#define HELPERS

void *stdin, *stdout, *stderr;

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
#define SCREEN_X_MIN 0
#define SCREEN_X_MAX 127
#define SCREEN_Y_MIN 0
#define SCREEN_Y_MAX 31

#define RAND_MAX 0xFFFFFFFF

#define DT 0.03f

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
#define C_3PI_2 4.712388980384689857693965074919254326295754099062658731462416888461724609429313497942052238013175601f
#define C_4PI_3 4.188790204786390984616857844372670512262892532500141094633259456410421875048278664837379767122822757f
#define C_PI    3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068f
#define C_2PI_3 2.094395102393195492308428922186335256131446266250070547316629728205210937524139332418689883561411378f
#define C_PI_2  1.570796326794896619231321691639751442098584699687552910487472296153908203143104499314017412671058534f
#define C_PI_3  1.047197551196597746154214461093167628065723133125035273658314864102605468762069666209344941780705689f
#define C_PI_4  0.785398163397448309615660845819875721049292349843776455243736148076954101571552249657008706335529267f
#define C_PI_6  0.523598775598298873077107230546583814032861566562517636829157432051302734381034833104672470890352844f
#define C_SQRT2 1.414213562373095048801688724209698078569671875376948073176679737990732478462107038850387534327641573f

// Misc Helpers

// Random float in [0, 1]
#define UFRAND ((float)rand() / (float)RAND_MAX)

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

// A rectangle represented by an origin (upper left corner) with width and height
typedef union _rect
{
    struct
    {
        v2 origin;
        v2 size;
    };
    struct
    {
        float x, y, w, h;
    };
} rect;

const m2x2 IMATRIX2;
const v2 VZERO;

m2x2 transpose(m2x2);
m2x2 relfectx(m2x2);
m2x2 relfecty(m2x2);
m2x2 mmul(const m2x2, const m2x2);
m2x2 mscale(m2x2, const float);
m2x2 get_rot_mat(const float);
v2 vscale(v2, const float);
float sqrt(float);
float norm(const v2);
v2 vmulm(const m2x2, const v2);
float fabs(float);
float sin(float);
float cos(float);
UBYTE overlaps(const rect, const rect);
void translate(rect* const, const v2);
v2 center(const rect);

/* ==========================================
 * |               PAINTER                  |
 * ==========================================
 */

void pixon(const BYTE, const BYTE);
void pixoff(const BYTE, const BYTE);
void draw_line(int x0, int y0, const int x1, const int y1);
void clear_buf();
void draw_rectangle(const rect);
void draw_rectangle_m(const rect, const m2x2, const v2);

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

// This stores the amount of milliseconds since the chip has started, it is updated within the interrupt service routine in vectors.S
extern volatile const unsigned int TICKS;

void bsl_init();
void timer_init();
void wait(unsigned int);
inputs get_inputs();
inline void set_leds(leds);

/* ==========================================
 * |              ANIMATION                 |
 * ==========================================
 */
void init_splash();
void draw_menu();
void draw_car();
void turn_left(const float);
void turn_right(const float);

typedef struct Car {
    UBYTE car_arr[14];
    v2 pos;
    float turn_speed;
} Car;

extern v2 current_curve;
extern float road_curve;
extern Car car;
void draw();

/* ==========================================
 * |                 FRAMES                 |
 * ==========================================
 */
extern Texture *frame1;
extern Texture *frame2;
extern Texture *frame3;
extern Texture *frame3_l;
extern Texture *frame3_r;

#endif // HELPERS
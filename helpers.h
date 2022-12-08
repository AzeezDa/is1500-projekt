#ifndef HELPERS
#define HELPERS

#include <stdlib.h>

// To avoid stdlib errors
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
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

// 32-bit float 2D Vector
typedef union _vec2
{
    float m[2];
    struct
    {
        float _1, _2;
    };
} v2;

typedef union _tup2
{
    int m[2];
    struct
    {
        int _1, _2;
    };
} t2;

const v2 VZERO;
float fabs(const float);
float clamp(const float, const float, const float);
t2 calc_persp(const v2);

/* ==========================================
 * |               PAINTER                  |
 * ==========================================
 */

void pixon(const BYTE, const BYTE);
void pixoff(const BYTE, const BYTE);
void draw_line(int x0, int y0, const int x1, const int y1);
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

    struct
    {
        UBYTE buttons : 4;
        UBYTE switches : 4;
    };

    UBYTE _all;
} inputs;

// The leds struct includes 8 bit fields each representing the LEDs on the chip
// Each fields number is the same as the number written on the chip, i.e _1 is LD1
typedef union _leds
{
    struct
    {
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
 * |                GAME STATE              |
 * ==========================================
 */

enum _GAME_STATE {MENU, GAME, SCOREBOARD, DEATH, TRANSITION} GAME_STATE;

/* ==========================================
 * |                 FRAMES                 |
 * ==========================================
 */

// Texture struct that stores a texture and its dimensions
typedef struct _texture
{
    UBYTE width, height;
    const UBYTE *texture;
} texture;

extern texture frame1;
extern texture frame2;
extern texture frame3;
extern texture frame3_l;
extern texture frame3_r;
extern texture frame_car;
extern texture lamp[6];
extern texture building_1;
extern texture building_2;
extern texture tree_f1;
extern texture tree_f2;
extern texture tree_f3;

/* ==========================================
 * |              ANIMATION                 |
 * ==========================================
 */
enum _ARROW_STATE {PLAY=16, SCORE=24} ARROW_STATE;
#define BUTTON_DELAY 500
#define LED_DELAY 100

void init_splash();
void draw_menu();
void display_scoreboard(); 
void draw_arrow();
void draw(v2, const texture *);

/* ==========================================
 * |                CARS                    |
 * ==========================================
 */

// Amount of total cars in on the road
#define CARS_AMOUNT 2

#define PLAYER_MAX_SPEED (0.005f * CARS_AMOUNT)
#define PLAYER_SPEED_RATIO (car.speed / PLAYER_MAX_SPEED)

// Controls how wide the perspective is
#define PERSPECTIVE_CONSTANT 0.3f

// Width from road center
#define ROAD_WIDTH 50

// Struct representing a non-playable car
typedef struct _npc_car
{
    v2 pos;
    float speed;
    float lane; // Deviation from the center line of the road
    float target_lane; // Lane that the car will switch to
    texture *texture;
} npc_car;

// Struct representing the car that the player controls
typedef struct _player_car
{
    v2 pos;
    float turn_speed;
    float speed;
    texture *texture;
} Car;

void init_road();
void init_npcs();
void init_player();

UBYTE update_npc();
inline void turn_car(const float);
void update_player(const inputs i);

extern v2 current_curve;
extern float road_curve;
extern Car car;
extern npc_car npcs[CARS_AMOUNT];
extern float distance_traveled;

/* ==========================================
 * |              GAME OVER                 |
 * ==========================================
 */
enum _UNDERSCORE_STATES {FIRST=60, SECOND=72, THIRD=84} UNDERSCORE_STATE;
void display_game_over();
void death_transition();
void next_letter(int);
void reset_name();
extern char name[6];

/* ==========================================
 * |                SCORE                   |
 * ==========================================
 */
void display_scoreboard();
void add_score(char *, int);


/* ==========================================
 * |                FONT                    |
 * ==========================================
 */
#define LETTER_WIDTH 5
#define LETTER_HEIGHT 6

v2 prints(char*, v2);
v2 printn(int, v2);
v2 printsn(char*, int, v2);

/* ==========================================
 * |               SCENARY                  |
 * ==========================================
 */
void init_scenary();
void update_side();
void draw_side();
#endif // HELPERS
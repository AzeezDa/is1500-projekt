#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"


int main()
{
    init();
    init_player();
    init_npcs();
    bsl_init();

    int start = TICKS;

    init_splash();

    inputs i;

    // Initiate states
    GAME_STATE = MENU;
    ARROW_STATE = PLAY;

    // Keeping track of frame transitions
    int transition_timer;
    // Button pressing delay
    int button_delay = TICKS;

    int menu_led_timer = TICKS;
    UBYTE led_counter;

    
    while (1)
    {
        // FIXED TIME UPDATE ROUTINE
        if (TICKS - start > 33)
        {
            start = TICKS;
            clear_buf();

            switch(GAME_STATE) {
                case MENU:
                    draw_menu();
                    draw_arrow();
                    break;
                case GAME:
                    draw(car.pos, car.texture);
                    draw_npcs();
                    update_road();
                    draw_side();
                    draw_road();
                    display_points();
                    break;
                case SCOREBOARD:
                    display_scoreboard();
                    break;
                case TRANSITION:
                    // Transitioning screen
                    if(TICKS - transition_timer <= 2500) 
                    {
                        death_transition();
                        UNDERSCORE_POS = UNDERSCORE_DEFAULT;

                    } else {
                        GAME_STATE = DEATH;
                    }
                    break;
                case DEATH:
                    display_game_over();
                    break;
            }

            oled_put_buffer();
        }

        i = get_inputs();

        switch(GAME_STATE) {
            case MENU:
                // Start game
                srand(TICKS);
                if (i.b2 && ARROW_STATE == PLAY)
                {
                    GAME_STATE = GAME;
                    init_player();
                    init_road();
                    init_npcs();
                    init_scenary();
                }
                // Show scoreboard
                if (i.b2 && ARROW_STATE == SCORE)
                {
                    GAME_STATE = SCOREBOARD;
                }
                if (TICKS - menu_led_timer > LED_DELAY)
                {
                    leds l;
                    l._all = (0x1 << led_counter) | (0x80 >> led_counter);
                    set_leds(l);
                    led_counter = (led_counter + 1) % 8;
                    menu_led_timer = TICKS;
                }
                // Move arrow
                if (i.b3 || i.b4)
                {
                    // Delay 
                    if((TICKS-button_delay)<BUTTON_DELAY) 
                    {
                        continue;
                    }
                    // Reset delay
                    button_delay = TICKS; 
                    if(ARROW_STATE == SCORE) 
                    {
                        ARROW_STATE = PLAY;
                    }
                    else 
                    {
                        ARROW_STATE = SCORE;
                    }
                }
                break;
            case GAME:
                update_npc();
                update_player(i);
                update_side();

                if (car.pos._1 < 4.0 || car.pos._1 > 110.0 
                    || update_npc() || OVERFLOW) 
                {
                    transition_timer = TICKS;
                    GAME_STATE = TRANSITION;
                }
                break;
            case SCOREBOARD:
                if (i.b1)
                    GAME_STATE = MENU;
                break;
            case DEATH:
                if(i.b1) {
                    if(OVERFLOW) {
                        points = INT_MAX;
                    }
                    // Overflow counts as a "win"
                    add_score(name, (int) points, OVERFLOW);
                    reset_game_variables();
                    GAME_STATE = SCOREBOARD;
                }

                if(i.b2) 
                {        
                    // Delay 
                    if((TICKS-button_delay)<BUTTON_DELAY) 
                    {
                        continue;
                    }
                    // Reset delay
                    button_delay = TICKS;  
                    // Switch between letters
                    UNDERSCORE_POS = UNDERSCORE_DEFAULT + (UNDERSCORE_POS - UNDERSCORE_DEFAULT + UNDERSCORE_STEP) % (3*UNDERSCORE_STEP);            

                }
                if(i.b3) 
                {
                    // Delay 
                    if((TICKS-button_delay) < BUTTON_DELAY) 
                    {
                        continue;
                    }
                    // Reset delay
                    button_delay = TICKS; 
                    next_letter(1);
                }
                    
                if(i.b4) 
                {
                    // Delay 
                    if((TICKS-button_delay) < BUTTON_DELAY) 
                    {
                        continue;
                    }
                    // Reset delay
                    button_delay = TICKS; 
                    next_letter(-1);
                }

                break;
        }

    }

    for (;;)
        ;
    return 0;
}

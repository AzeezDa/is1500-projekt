#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
    init();
    init_car();

    int x = 1, start, framestart = TICKS;
    inputs i;
    leds ld = {0};

    init_splash();

    // Playing or not
    BYTE GAME_STATE = 0;

    while (1)
    {    

        if (TICKS - start > 33) 
        {
            start = TICKS;
            clear_buf();

            if(GAME_STATE) {
                draw_car();
            } else {
                draw_menu();
                draw_arrow();
            }

            oled_put_buffer();
        }


        i = get_inputs();
        /**
         * POLLING INPUT WHILE IN MENU
         */
        if(!GAME_STATE)
        {
            if(i.b2 && !arrow_state()) {
              GAME_STATE = 1;  
            }
            if(i.b3) {
                arrow_down();
            }
            if(i.b4) {
                arrow_up();
            }
        }

        /**
         * POLLING INPUT WHILE INGAME
         */
        if(GAME_STATE) 
        {
            if(i.b3) {
                turn_right();
            }
            if(i.b4) {
                turn_left();
            }
        }

        framestart = TICKS;
    }

    oled_put_buffer();
    
    

    for (;;)
        ;
    return 0;
}
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
    BYTE GAME_STATE = 0;

    while (1)
    {
        // FIXED TIME UPDATE ROUTINE
        if (TICKS - start > 33)
        {
            start = TICKS;
            clear_buf();

            if (GAME_STATE)
            {
                draw(car.pos, car.texture);
                draw_npcs();
                update_road();
                draw_road();
            }
            else
            {
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
            continue;
        }

        /**
         *  IN GAME
         */
        if (fabs(current_curve._1) > 0.1)
        {
            if (current_curve._1 > 0.0)
                turn_left(car.turn_speed * current_curve._1);
            if (current_curve._1 < 0.0)
                turn_right(-car.turn_speed * current_curve._1);
        }

        update_npc();

        if (i.b4)
            turn_left(car.turn_speed);
        if (i.b3)
            turn_right(car.turn_speed);
    }

    for (;;)
        ;
    return 0;
}

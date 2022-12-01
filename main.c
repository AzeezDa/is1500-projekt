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
        if (!GAME_STATE)
        {
            if (i.b2 && !arrow_state())
            {
                GAME_STATE = 1;
                init_player();
                init_road();
                init_npcs();
            }
            if (i.b3)
            {
                arrow_down();
            }
            if (i.b4)
            {
                arrow_up();
            }
            continue;
        }

        /**
         *  IN GAME
         */

        update_player(i);

        if (car.pos._1 < 4.0 || car.pos._1 > 110.0 || update_npc())
            GAME_STATE = 0;
    }

    for (;;)
        ;
    return 0;
}

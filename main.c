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
                    draw_road();
                    break;
                case SCOREBOARD:
                    display_scoreboard();
                    break;
                case DEATH:
                    // Todo
                    break;
            }

            oled_put_buffer();
        }

        i = get_inputs();

        switch(GAME_STATE) {
            case MENU:
                // Start game
                if (i.b2 && ARROW_STATE == PLAY)
                {
                    GAME_STATE = GAME;
                    init_player();
                    init_road();
                    init_npcs();
                }
                // Show scoreboard
                if (i.b2 && ARROW_STATE == SCORE)
                {
                    GAME_STATE = SCOREBOARD;
                }
                // Move arrow
                if (i.b3)
                {
                    ARROW_STATE = SCORE;
                }
                if (i.b4)
                {
                    ARROW_STATE = PLAY;
                }
                break;
            case GAME:
                if (fabs(current_curve._1) > 0.1)
                {
                    if (current_curve._1 > 0.0)
                        turn_car(-car.turn_speed * current_curve._1);
                    if (current_curve._1 < 0.0)
                        turn_car(-car.turn_speed * current_curve._1);
                }

                if (i.b4)
                    turn_car(-car.turn_speed);
                if (i.b3)
                    turn_car(car.turn_speed);

                if (car.pos._1 < 4.0 || car.pos._1 > 110.0 || update_npc())
                    GAME_STATE = 0;
                break;
            case SCOREBOARD:
                if (i.b2)
                    GAME_STATE = MENU;
                break;
            case DEATH:
                // Todo
                break;
        }

    }

    for (;;)
        ;
    return 0;
}

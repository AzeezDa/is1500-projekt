#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
    init();
    init_player();
    init_cars();

    int start = TICKS;

    inputs i;

    while (1)
    {    
        // FIXED TIME UPDATE ROUTINE
        if (TICKS - start > 33) 
        {
            start = TICKS;
            clear_buf();
            draw(car.pos, car.texture);
            draw(npc.pos, npc.texture);
            update_road();
            draw_road();

            oled_put_buffer();
        }


        i = get_inputs();

        if (fabs(current_curve._1) > 0.1) {
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

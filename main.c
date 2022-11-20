#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
    init();
    init_car();

    int start = TICKS;

    inputs i;

    while (1)
    {    
        // FIXED TIME UPDATE ROUTINE
        if (TICKS - start > 33) 
        {
            start = TICKS;
            clear_buf();
            draw_car();
            update_road();
            draw_road();

            oled_put_buffer();
        }


        i = get_inputs();

        if (fabs(current_curve._1) > 0.2) {
            if (current_curve._1 > 0.0)
                turn_left(car.turn_speed * current_curve._1);
            if (current_curve._1 < 0.0)
                turn_right(-car.turn_speed * current_curve._1);
        }

        if (i.b4)
            turn_left(car.turn_speed);
        if (i.b3)
            turn_right(car.turn_speed);
        
    }
    
    

    for (;;)
        ;
    return 0;
}

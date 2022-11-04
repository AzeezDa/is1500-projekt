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

    while (1)
    {    

        if (TICKS - start > 33) 
        {
            start = TICKS;
            clear_buf();

            draw_car();
            oled_put_buffer();
        }
        i = get_inputs();

        if(i.b3) {
            turn_right();
        }
        if(i.b4) {
            turn_left();
        }
        framestart = TICKS;
    }

    oled_put_buffer();
    
    

    for (;;)
        ;
    return 0;
}
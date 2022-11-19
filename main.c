#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
    init();
    init_car();

    int x = 1, start, framestart = TICKS, rups = 0;
    inputs i;
    leds ld = {0};


    while (1)
    {    
        if (TICKS - start > 33) 
        {
            start = TICKS;
            clear_buf();

            //draw_car();
            update_road();
            draw_road();

            oled_put_buffer();
        }
    }
    
    

    for (;;)
        ;
    return 0;
}

#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
	init();

	int x = 1, start;
	while (1)
	{	
		if (TICKS - start > 500) 
		{
			start = TICKS;
			clear_buf();
			draw_car(x, x++);
			oled_put_buffer();
			if (x > 32)
				x = 0;


			// Car movement
			inputs in = get_inputs();
			if (in.b1)
				turn_left();
			if(in.b2) 
				turn_right();
		}
	}

	oled_put_buffer();
	
	

	for (;;)
		;
	return 0;
}

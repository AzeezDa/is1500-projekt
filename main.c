#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
	init();

	int i;
	rect r = {50.0, 12.0, 8.0, 8.0},
		 wall1 = {100.0, 5.0, 20.0, 22.0},
		 wall2 = {2.0, 5.0, 20.0, 22.0};
	v2 dir = {0.2, 0.0};


	volatile unsigned int start, period = 500; // 500ms

	m2x2 rot = get_rot_mat(0.3f);
	// Initialises input device struct
	leds ld = {0};
	inputs in;

	start = TICKS;
	oled_put_buffer();
	while (1)
	{
		
		if (TICKS - start < period)
		{
			clear_buf();
			draw_rectangle_m(wall1, rot, center(wall1));
			draw_rectangle_m(wall2, rot, center(wall2));
			draw_rectangle_m(r, rot, center(r));

			if (overlaps(wall1, r) | overlaps(wall2, r))
				dir._1 *= -1.0;

			translate(&r, dir);
			oled_put_buffer();
			start = TICKS;
		}
		

		in = get_inputs();
		period = 500;
		ld._all = 0b11001100;
		if (in.s1)
			period = 100;
		if (in.b1)
			ld._all = ~ld._all;
		
		set_leds(ld);
	}

	for (;;)
		;
	return 0;
}

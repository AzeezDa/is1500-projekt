#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
	init();

	int i, count = 0;
	volatile unsigned int start, period = 500; // 500ms

	// Initialises input device struct
	leds ld = {0};
	inputs in;

	start = TICKS;
	oled_put_buffer();
	while (1)
	{
		if (TICKS - start > period) {
			clear_buf();
			for(i = 0; i < 32; i++)
				pixon(count%128, i);
			oled_put_buffer();
			count++;
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

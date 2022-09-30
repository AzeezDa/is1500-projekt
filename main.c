#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
	init();

	int i;

	// Initialises input device struct
	leds ld = {0};
	inputs in;

	while (1)
	{
		in = get_inputs();
		clear_buf();

		ld._all = 0; // Clear leds

		if (in.b1)
			ld._1 = 1;

		if (in.b2)
			ld._2 = 1;

		if (in.b3)
			ld._3 = 1;

		if (in.b4)
			ld._4 = 1;

		if (in.s1)
			ld._5 = 1;

		if (in.s2)
			ld._6 = 1;

		if (in.s3)
			ld._7 = 1;
			
		if (in.s4)
			ld._8 = 1;

		if (in.buttons) // Any button is pressed
			pixon(32, 16);

		if (in.switches) // Any switch is on
			pixon(96, 16);

		if (in._all) // Any switch or button is ON
			pixon(64, 16);

		set_leds(ld);

		oled_put_buffer();
	}

	for (;;)
		;
	return 0;
}

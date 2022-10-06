#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
	init();

	int i, ct = 0, start = 0;

	// Initialises input device struct
	leds ld = {0};
	inputs in;

	while (1)
	{
		start = ticks;
		clear_buf();
		for (i = 0; i < 20; i++)
			pixon(ct%20, i);

		oled_put_buffer();

		wait(1000);
		ct++;
	}

	for (;;)
		;
	return 0;
}

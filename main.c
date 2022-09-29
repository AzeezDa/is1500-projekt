#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
	init();

	float x = 16, t = 0;
	int i, j;
	
	while (1)
	{
		// Draw pendulum rope
		x = 64.0 + 20 * sin(t);
		draw_line(64, 1, x, 25);
		t += 0.01;
		
		// Pendulum ball
		for (i = -3; i < 3; i++)
		{
			for (j = -3; j < 3; j++)
				pixon(x + i, 25 + j);
		}
		
		oled_put_buffer();

		for (i = 0; i < 512; i++)
		{
			display_buffer[i] = 0;
		}
		
	}
	

	

	for (;;)
		;
	return 0;
}

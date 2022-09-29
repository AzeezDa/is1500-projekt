#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
	init();

	int i;

	while (1)
	{
		for (i = 0; i < 512; i++)
		{
			display_buffer[i] = rand();
		}
		
		oled_put_buffer();

		for (i = 0; i < 50000; i++);
	}

	for (;;)
		;
	return 0;
}

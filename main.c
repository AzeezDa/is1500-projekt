#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
	init();

	pixon(1, 1);
	pixon(6, 9);
	pixon(4, 20);
	oled_put_buffer();

	for (;;)
		;
	return 0;
}

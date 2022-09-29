#include <pic32mx.h>
#include <stdint.h>
#include "helpers.h"

int main()
{
	init();

	pixon(1, 1);
	oled_put_buffer();
	
	for (;;)
		;
	return 0;
}

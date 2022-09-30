#include <pic32mx.h>
#include "helpers.h"

// Initialises all IO devices (OLED, Buttons, Switches and LEDs) (Timer is WIP)
void init() {
    oled_init();
    bsl_init();
}

// Initialises Buttons, Switches and LEDs
void bsl_init()
{
    TRISF |= 0x2;
    TRISD |= 0xFE0;
    TRISE &= ~0xFF;
    PORTE &= ~0xFF;
}

// Returns the inputs union struct, updated with which buttons and switches are on
inputs get_inputs()
{
    volatile inputs in; // Making it volatile because compiler might optimize stuff here?
    in._all = (PORTD >> 4) & 0xFE;
    in.b1 = (PORTF >> 1) & 0x1;
    return in;
}

// Given the leds struct, turns the LEDs on based on the struct's values
inline void set_leds(leds ls) {
    PORTE &= ~0xFF;
    PORTE |= ls._all;
}
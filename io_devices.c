#include <pic32mx.h>
#include "helpers.h"

// Initialises all IO devices (OLED, Buttons, Switches and LEDs) (Timer is WIP)
void init()
{
    oled_init();
    bsl_init();
    timer_init();
}

// Initialises Buttons, Switches and LEDs
void bsl_init()
{
    TRISF |= 0x2;
    TRISD |= 0xFE0;
    TRISE &= ~0xFF;
    PORTE &= ~0xFF;
}

// Initialize timer 2 with 1 ms time out
void timer_init()
{
    T2CON = 0x10; // Set prescale to 2
    TMR2 = 0x0;
    PR2 = 20000;     // 80 000 000 / 2 / 1000 / 2 CC = 20000
    IEC(0) |= 0x100;
    IPC(2) |= 31;
    asm volatile("ei");
    T2CON |= 0x8000; // Turn on timer
}

void wait(unsigned int ms)
{
    unsigned int start = ticks;
    while (ticks - start < ms);
    return;
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
inline void set_leds(leds ls)
{
    PORTE &= ~0xFF;
    PORTE |= ls._all;
}
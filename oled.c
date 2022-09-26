#define OLED_FILE

#include <pic32mx.h>
#include "helpers.h"

// Written by Herdi Saleh 2022-09-25

#define OLED_MAX_COL 128
#define OLED_MAX_ROWS 32
#define OLED_MAX_PAGE 8
// OLED_BUF_SIZE = 512 (INCLUDED IN HELPERS.H)

// 4 * 128 = 512
BYTE display_buffer[OLED_BUF_SIZE];

BYTE spi_send_receive(BYTE data)
{
    while ((SPI2STAT & 0b1000) == 0)
        ; // Wait for buffer to empty out
    SPI2BUF = data;
    while ((SPI2STAT & 0b01) == 0)
        ; // Wait for data to be received
    BYTE rec = SPI2BUF;
    return rec; // Return received byte
}

void delay(int n)
{
    volatile int i;
    for (i = 0; i < n; i++)
        ;
}

void oled_power_on()
{
    PORTF &= ~0b10000; // Clear Data/cmd RF4 = 0
    delay(10);
    PORTF &= ~0b1000000;    // Apply power to VDD, RF6 = 0;
    delay(1000000);         // Delay for the power to come up
    spi_send_receive(0xAE); // Send display off command

    // Reset
    PORTG &= ~0b1000000000;
    delay(1000000);
    PORTG |= 0b1000000000;

    spi_send_receive(0x8D);
    spi_send_receive(0x14);
    spi_send_receive(0xD9);
    spi_send_receive(0xF1);

    PORTF &= ~0b100000; // Turn on VCC (VBAT_EN = 1)
    delay(10000000);
    spi_send_receive(0xA1);
    spi_send_receive(0xC8);
    spi_send_receive(0xDA);
    spi_send_receive(0x20);

    spi_send_receive(0xAF); // Send display on command
}

void oled_put_buffer()
{

    BYTE junk;
    // Write/Read the data
    int i;
    for (i = 0; i < OLED_BUF_SIZE; i++)
    {
        while ((SPI2STAT & 0b1000) == 0)
            ; // Wait for buffer to empty out
        SPI2BUF = display_buffer[i];
        while ((SPI2STAT & 0b1) == 0)
            ; // Wait for data to be received
        junk = SPI2BUF;
    }
}

void oled_update()
{
    char *pb;
    pb = display_buffer;
    int page;
    for (page = 0; page < OLED_MAX_PAGE; page++)
    {
        PORTF &= ~0b10000;

        // Set page number
        spi_send_receive(0x22);
        spi_send_receive(page);

        spi_send_receive(0x00);
        spi_send_receive(0x10);

        PORTF |= 0b10000;

        oled_put_buffer(128, pb);
        pb += 128;
    }
}

void oled_power_off()
{
    // Send display off command (SPI?)
    PORTFSET &= 0x10;
    spi_send_receive(0xAE);
    // Power off VBAT
    PORTF |= 0x10;
    delay(10000000); // delay 100 ms
    // Power off VDD
    PORTF |= 0x20;
}

void init()
{
    /**
     * Setting up the SPI
     */
    SPI2CON = 0;                   // turn SPI off
    SPI2BRG = 4;                   // Baud rate
    SPI2STAT &= ~0b1000000;        // SPIROV = 0 bit 6
    SPI2CON |= 0b1000000;          // CKP = 1 bit 6
    SPI2CON |= 0b100000;           // put SPI in master mode, MSTEN = 1 bit 5
    SPI2CON |= 0b1000000000000000; // turn SPI on, ON = 1 bit 15

    /**
     * Set outputs
     */
    PORTF |= 0b1110000; // Set RF4, RF5, RF6 as outputs = 1
    TRISF &= ~0b1110000;
    PORTG |= 0b1000000000; // Set RG9 as output = 1s
    TRISG &= ~0b1000000000;

    // Power on sequence
    oled_power_on();

    PORTFCLR = 0x10;
    // Set horizontal adressing mode
    spi_send_receive(0x20);
    spi_send_receive(0);

    // Column address 0:127
    spi_send_receive(0x21);
    spi_send_receive(0);
    spi_send_receive(127);

    // Page addressing 0:7
    spi_send_receive(0x22);
    spi_send_receive(0);
    spi_send_receive(7);

    PORTFSET = 0x10;
}
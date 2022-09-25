#include <pic32mx.h>
#include <stdint.h>

#define OLED_MAX_COL  128;
#define OLED_MAX_ROWS  32;
#define OLED_MAX_PAGE   4;

// 4 * 128 = 512
char displayBuffer[512]; 

int delay(int n) {
	volatile int i;
	for(i = 0; i < n; i++);
}

void oled_power_on() {
	PORTF &= ~0b10000; // Clear Data/cmd RF4 = 0
	PORTF &= ~0b1000000; // Apply power to VDD, RF6 = 0;
	delay(1000000); // Delay for the power to come up
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

void oled_update() {
	char *pb;
	pb = displayBuffer;
	for(int page = 0; page < 4; page++) {
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

void oled_put_buffer(int c, uint8_t *data) {
	uint8_t junk;
	// Write/Read the data
	for(int i = 0; i < c; i++) {
		while((SPI2STAT & 0b1000) == 0); // Wait for buffer to empty out
		SPI2BUF = *data++;
		while((SPI2STAT & 0b1) == 0); // Wait for data to be received
		junk = SPI2BUF;
	}
}

void oled_power_off() {
	// Send display off command (SPI?)

	// Power off VBAT
	PORTF |= 0x10;
	delay(10000000); // delay 100 ms
	// Power off VDD
	PORTF |= 0x20;
}

uint8_t spi_send_receive(uint8_t data) {
	while((SPI2STAT & 0b1000) == 0); // Wait for buffer to empty out
	SPI2BUF = data;
	while((SPI2STAT & 0b01) == 0); // Wait for data to be received
	uint8_t rec = SPI2BUF;
	return rec; // Return received byte
}

int main() {

	/**
	 * Setting up the SPI
	 */
	SPI2CON = 0; // turn SPI off
	SPI2BRG = 4; // Baud rate
	SPI2STAT &= ~0b1000000; // SPIROV = 0 bit 6
	SPI2CON |= 0b1000000; // CKP = 1 bit 6
	SPI2CON |= 0b100000; // put SPI in master mode, MSTEN = 1 bit 5
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
	spi_send_receive(0xA);
	oled_update();
	
	for(;;);
	return 0;
}

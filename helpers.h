#pragma once

/*
 * This header file defines functions that should be accessible from outside
 */

/* ==========================================
 * |             OLED HELPERS               |                              
 * ==========================================
 */
#define OLED_BUF_SIZE 512
#define BYTE char

#ifndef OLED_FILE
extern BYTE displayBuffer[OLED_BUF_SIZE];
void oled_power_off();
void init();
void oled_update();
void oled_put_buffer();
void delay(int);
#endif
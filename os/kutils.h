#ifndef KUTILS_H
#define KUTILS_H

#include "kstdint.h"

//////////////////////////////
////    Generic utils
//////////////////////////////

void delay(uint64_t count);

//////////////////////////////
////    VGA utils
//////////////////////////////

enum VGA_COLORS {
  VGA_LIGHT_GREY = 0x7,
  VGA_WHITE = 0xf,
  VGA_RED = 0x4,
  VGA_GREEN = 0x2,
  VGA_BLACK = 0x0
};

void init_vga(uint8_t f_color, uint8_t b_color);
void vga_putchar(char c);
void vga_write(const char *s);
void vga_clear(void);
void vga_setcolor(uint8_t f_color, uint8_t b_color);
void vga_setpos(uint16_t row, uint16_t col);

#endif
#ifndef KUTILS_H
#define KUTILS_H

#include "kstdint.h"

//////////////////////////////
////    Memory utils
//////////////////////////////

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *a, const void *b, size_t n);

//////////////////////////////
////    Generic utils
//////////////////////////////

void delay(uint64_t count);
uint32_t strlen(const char *s);
char *itoa(int value, char *s, int base);

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
void vga_putc(char c);
void vga_puts(const char *s);
void vga_printf(const char *s);
void vga_println(const char *s);
void vga_clear(void);
void vga_setcolor(uint8_t f_color, uint8_t b_color);
void vga_setpos(size_t row, size_t col);
void vga_setpos_offset(int row, int col);
void vga_newline();

#endif
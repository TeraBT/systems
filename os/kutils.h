#ifndef KUTILS_H
#define KUTILS_H

#include "kstddef.h"
#include "kstdint.h"

#include <stdarg.h>

//////////////////////////////
////    Memory utils
//////////////////////////////

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *a, const void *b, size_t n);

//////////////////////////////
////    Generic utils
//////////////////////////////

void busy_delay(uint64_t count);
uint32_t strlen(const char *s);
char *itoa(int value, char *s, int base);
void panic(const char *msg);

//////////////////////////////
////    Time utils
//////////////////////////////

enum { PIT_COMMAND = 0x43, PIT_CHANNEL0 = 0x40, PIT_BASE_FREQUENCY = 1193182 };

void init_pit(uint32_t frequency);
void pit_increment(void);
uint32_t pit_get_ticks(void);
uint32_t pit_get_secs(void);
void sleep(uint32_t ticks);
void sleep_ms(uint32_t ms);

//////////////////////////////
////    Assembly utils
//////////////////////////////

static inline void cli(void) { __asm__ volatile("cli"); }
static inline void sti(void) { __asm__ volatile("sti"); }
static inline void hlt(void) { __asm__ volatile("hlt"); }

//////////////////////////////
////    IO utils
//////////////////////////////

enum {
  PIC1_COMMAND = 0x20,
  PIC1_DATA = 0x21,
  PIC2_COMMAND = 0xa0,
  PIC2_DATA = 0xa1
};

static inline void outb(uint16_t port, uint8_t value) {
  __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
  uint8_t value;
  __asm__ volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
  return value;
}

void pic_write_eoi(uint32_t int_no);

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

void vga_clear(void);
void vga_setcolor(uint8_t f_color, uint8_t b_color);
void vga_setpos(size_t row, size_t col);
void vga_setpos_rel(int row_steps, int col_steps);
void vga_scroll(int line_count);
void vga_newline();

void vga_putc(char c);
void vga_puts(const char *s);
void vga_printf(const char *s, ...);

#endif
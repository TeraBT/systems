#include "kutils.h"
#include "kstdint.h"

//////////////////////////////
////    Generic utils
//////////////////////////////

void delay(uint64_t count) {
  while (count--) {
    __asm__ volatile("nop");
  }
}

//////////////////////////////
////    VGA utils
//////////////////////////////

enum {
  VGA_WIDTH = 80,
  VGA_HEIGHT = 25,
  VGA_TOTAL_CELL_COUNT = VGA_WIDTH * VGA_HEIGHT,
  VGA_CELL_SIZE = 2,
  VGA_TOTAL_SIZE = VGA_TOTAL_CELL_COUNT * VGA_CELL_SIZE
};

typedef struct VGA {
  uint16_t row;
  uint16_t col;
  uint8_t color;
  volatile uint16_t *buffer;
} VGA;

static VGA vga;

void init_vga(uint8_t f_color, uint8_t b_color) {
  vga.row = 0;
  vga.col = 0;
  vga.color = (b_color << 4) | f_color;
  vga.buffer = (volatile uint16_t *)0xb8000;
}

void vga_putchar(char c) {
  vga.buffer[vga.row * VGA_WIDTH + vga.col++] = (vga.color << 8) | c;

  if (vga.col == VGA_WIDTH) {
    vga.col = 0;

    if (vga.row == VGA_HEIGHT - 1) {
      vga.row = 0;
    } else {
      ++vga.row;
    }
  }
}

void vga_write(const char *s) {
  for (int i = 0; s[i] != '\0'; i++) {
    vga_putchar(s[i]);
  }
}

void vga_clear(void) {
  for (int i = 0; i < VGA_TOTAL_CELL_COUNT; i++) {
    vga.buffer[i] = 0x0000;
  }
}
void vga_setcolor(uint8_t f_color, uint8_t b_color) {
  vga.color = (b_color << 4) | f_color;
}

void vga_setpos(uint16_t row, uint16_t col) {
  vga.row = row;
  vga.col = col;
}

#include "kutils.h"
#include "kstdint.h"

//////////////////////////////
////    Memory utils
//////////////////////////////

void *memcpy(void *dest, const void *src, size_t n) {
  for (size_t i = 0; i < n; i++) {
    ((uint8_t *)dest)[i] = ((const uint8_t *)src)[i];
  }

  return dest;
}

void *memset(void *dest, int value, size_t n) {
  for (size_t i = 0; i < n; i++) {
    ((uint8_t *)dest)[i] = (uint8_t)value;
  }

  return dest;
}

int memcmp(const void *a, const void *b, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (((uint8_t *)a)[i] != ((uint8_t *)b)[i]) {
      return (int)((const uint8_t *)a)[i] - (int)((const uint8_t *)b)[i];
    }
  }

  return 0;
}

//////////////////////////////
////    Generic utils
//////////////////////////////

void delay(uint64_t count) {
  while (count--) {
    __asm__ volatile("nop");
  }
}

size_t strlen(const char *s) {
  size_t l = 0;
  while (s[l] != '\0') {
    ++l;
  }

  return l;
}

void reverse(char *s);

char *itoa(int value, char *s, int base) {
  if (base != 10 && base != 16 && base != 8 && base != 2) {
    return NULL;
  }

  int i, sign;

  if (value < 0)
    sign = -1;
  else
    sign = 1;

  i = 0;
  do {
    uint8_t r = value % base * sign;
    s[i++] = r + (r > 9 ? 'a' - 10 : '0');
  } while ((value /= base) != 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);

  return s;
}

void reverse(char *s) {
  int i, j;
  char c;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
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
  size_t row;
  size_t col;
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

void vga_putc(char c) {
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

void vga_puts(const char *s) {
  for (int i = 0; s[i] != '\0'; i++) {
    vga_putc(s[i]);
  }
}

void vga_newline();

void vga_printf(const char *s) { // TODO
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] == '\n') {
      vga_newline();
      continue;
    }
    vga_putc(s[i]);
  }
}

void vga_println(const char *s) {
  vga_puts(s);
  vga_newline();
}

void vga_clear(void) {
  for (int i = 0; i < VGA_TOTAL_CELL_COUNT; i++) {
    vga.buffer[i] = 0x0000;
  }
}
void vga_setcolor(uint8_t f_color, uint8_t b_color) {
  vga.color = (b_color << 4) | f_color;
}

void vga_setpos(size_t row, size_t col) {
  vga.row = row;
  vga.col = col;
}

void vga_setpos_offset(int row, int col) {

  vga.row += row;
  vga.col += col;
}

void vga_newline() {
  vga.col = 0;
  ++vga.row;
}

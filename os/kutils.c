#include "kutils.h"
#include "kstddef.h"
#include "kstdint.h"

#include <stdarg.h>

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

extern uint8_t _kernel_end;
static uint8_t heap_initialized = 0;
static intptr_t heap_start = 0;
static intptr_t heap_end = 0;
static intptr_t heap_top = 0;

void init_heap() {
  if (heap_initialized) {
    panic("Heap already initialized.");
    return;
  }

  heap_start = ((uintptr_t)&_kernel_end + 15) & ~((uintptr_t)15);
  heap_end = 0x80000;
  if (heap_start >= heap_end) {
    panic("Heap size is zero or negative.");
    return;
  }
  heap_top = heap_start;
  heap_initialized = 1;
}

void *malloc(size_t size) {
  if (heap_initialized == 0) {
    panic("Heap uninitialized.");
    return NULL;
  }

  intptr_t new_top = heap_top + size;
  if (new_top > heap_end) {
    panic("Allocation failure. Out of heap memory.");
    return NULL;
  }

  intptr_t start = heap_top;
  heap_top = new_top;

  return (void *)start;
}

//////////////////////////////
////    Generic utils
//////////////////////////////

void busy_delay(uint64_t count) {
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

void panic(const char *msg) {
  vga_setcolor(VGA_RED, VGA_WHITE);
  vga_printf("PANIC: %s", msg);

  for (;;) {
    cli();
    hlt();
  }
}

//////////////////////////////
////    Time utils
//////////////////////////////

static volatile uint32_t tick_count = 0;
static uint32_t pit_frequency = 0;

void init_pit(uint32_t frequency) {
  if (frequency == 0) {
    return;
  }
  pit_frequency = frequency;

  uint16_t divisor = PIT_BASE_FREQUENCY / pit_frequency;

  outb(PIT_COMMAND, 0x36);
  outb(PIT_CHANNEL0, (uint8_t)(divisor & 0xff));
  outb(PIT_CHANNEL0, (uint8_t)((divisor >> 8) & 0xff));
}

void pit_increment(void) { ++tick_count; }

uint32_t pit_get_ticks(void) { return tick_count; }

uint32_t pit_get_secs(void) { return pit_get_ticks() / pit_frequency; }

void sleep(uint32_t ticks) {
  uint32_t start = pit_get_ticks();
  while ((pit_get_ticks() - start) < ticks) {
    hlt();
  }
}

void sleep_ms(uint32_t ms) { sleep((ms * pit_frequency + 9999) / 1000); }

//////////////////////////////
////    IO utils
//////////////////////////////

void pic_write_eoi(uint32_t int_no) {
  if (int_no >= 40) {
    outb(PIC2_COMMAND, 0x20);
  }
  outb(PIC1_COMMAND, 0x20);
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

void vga_clear(void) {
  for (int i = 0; i < VGA_TOTAL_CELL_COUNT; ++i) {
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

void vga_setpos_rel(int row_steps, int col_steps) {

  vga.row += row_steps;
  vga.col += col_steps;
}

void vga_scroll(int line_count) {

  if (line_count == 0)
    return;

  size_t row, col;

  if (line_count > 0) {
    while (line_count--) {
      for (int i = 0; i < VGA_TOTAL_CELL_COUNT; ++i) {

        row = i / VGA_WIDTH;
        col = i % VGA_WIDTH;

        if (row == VGA_HEIGHT - 1) {
          vga.buffer[i] = (vga.color << 8) | 0x00;
        } else {
          vga.buffer[i] = vga.buffer[(row + 1) * VGA_WIDTH + col];
        }
      }

      if (vga.row != 0) {
        --vga.row;
      } else {

        vga.col = 0;
      }
    }
  } else {
    while (line_count++) {
      for (int i = VGA_TOTAL_CELL_COUNT; i >= 0; --i) {

        row = i / VGA_WIDTH;
        col = i % VGA_WIDTH;

        if (row == 0) {
          vga.buffer[i] = (vga.color << 8) | 0x00;
        } else {
          vga.buffer[i] = vga.buffer[(row - 1) * VGA_WIDTH + col];
        }
      }

      if (vga.row != VGA_HEIGHT - 1) {
        ++vga.row;
      } else {
        vga.col = VGA_WIDTH - 1;
      }
    }
  }
}

void vga_newline() {
  vga.col = 0;

  if (vga.row == VGA_HEIGHT - 1) {
    vga_scroll(1);
  }
  ++vga.row;
}

void vga_putc(char c) {
  if (c == '\n') {
    vga_newline();
    return;
  }

  vga.buffer[vga.row * VGA_WIDTH + vga.col++] = (vga.color << 8) | c;

  if (vga.col == VGA_WIDTH) {
    vga_newline();
  }
}

void vga_puts(const char *s) {
  while (*s) {
    vga_putc(*s++);
  }
}

void vga_newline();

void vga_printf(const char *s, ...) {
  va_list args;
  va_start(args, s);

  char buf[11];
  while (*s) {

    if (*s == '%') {

      ++s;
      switch (*s) {

      case 'd':
        itoa(va_arg(args, int), buf, 10);
        vga_puts(buf);
        break;

      case 's':
        vga_puts(va_arg(args, const char *));
        break;
      }
    } else {
      vga_putc(*s);
    }

    ++s;
  }

  va_end(args);
}

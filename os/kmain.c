#include "kutils.h"

void kmain(void) {
  volatile unsigned short *vga = (volatile unsigned short *)0xb8000;

  const char *const init_msg = "Kernel main routine reached.";

  for (int i = 0; init_msg[i] != '\0'; i++) {
    vga[80 + i] = 0x0400 | init_msg[i];
  }

  init_vga(VGA_GREEN, VGA_BLACK);

  vga_write("Init successful.");

  init_vga(VGA_GREEN, VGA_BLACK);

  for (int i = 0; i < 2000; i++) {
    vga_putchar('n');
  }

  vga_setcolor(VGA_RED, VGA_BLACK);
  vga_putchar('O');
  vga_setpos(2, 1);
  vga_putchar('O');

  delay(100000000ULL);

  vga_clear();
}
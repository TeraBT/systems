#include "kutils.h"

void kmain(void) {

  init_vga(VGA_GREEN, VGA_BLACK);
  vga_clear();

  vga_puts("Kernel init successful.");

  vga_setpos(2, 0);

  vga_printf("Utils test.\n");

  char c[128];
  vga_printf("strlen(\"123\") = ");
  vga_println(itoa(strlen("123"), c, 10));
  vga_newline();

  int n = -16;
  vga_println(itoa(n, c, 10));
  vga_println(itoa(n, c, 16));
  vga_println(itoa(n, c, 2));
  vga_newline();

  vga_printf("Alive counter: ");
  for (int i = 0;; i++) {
    char *output = itoa(i, c, 10);
    vga_puts(output);
    vga_setpos_offset(0, -strlen(output));
    delay(100000000);
  }
}
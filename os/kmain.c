#include "kutils.h"

void kmain(void) {

  init_vga(VGA_GREEN, VGA_BLACK);
  vga_clear();

  vga_puts("Kernel init successful.");

  vga_setpos(2, 0);

  vga_puts("Utils test:\n");
  vga_newline();

  char c[128];
  vga_puts("strlen(\"123\") = ");
  vga_printf("%s\n", itoa(strlen("123"), c, 10));
  vga_newline();

  int n = 17;
  vga_printf("%d = %s\n", n, itoa(n, c, 10));
  vga_printf("%d = %s\n", n, itoa(n, c, 16));
  vga_printf("%d = %s\n", n, itoa(n, c, 2));
  vga_newline();

  return;

  vga_puts("Alive counter: ");
  for (int i = 0;; i++) {
    char *output = itoa(i, c, 10);
    vga_puts(output);
    vga_setpos_rel(0, -strlen(output));
    delay(100000000); // TODO: Make non-busy.
  }
}
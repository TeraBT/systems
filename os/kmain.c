#include "kutils.h"

void kmain(void) {

  init_vga(VGA_GREEN, VGA_BLACK);
  vga_clear();

  vga_write("Kernel init successful.");

  vga_setpos(2, 0);

  vga_write("Utils test.");

  vga_write(strlen("123") == 3 ? "Y" : "N");

  vga_setpos(4, 0);

  vga_write("Alive counter: "); // TODO
}
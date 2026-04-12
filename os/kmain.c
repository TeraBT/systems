#include "kutils.h"

void kmain(void) {

  init_vga(VGA_GREEN, VGA_BLACK);
  vga_clear();

  vga_write("Kernel init successful.");

  delay(100000000ULL);

  init_vga(VGA_GREEN, VGA_BLACK);

  vga_clear();
}
void kmain(void) {
  volatile unsigned short *vga = (volatile unsigned short *)0xb8000;

  const char *const init_msg = "Kernel main routine reached.";

  for (int i = 0; init_msg[i] != '\0'; i++) {
    vga[80 + i] = 0x0400 | init_msg[i];
  }
}
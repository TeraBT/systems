#include "idt.h"
#include "kutils.h"

#define PIT_FREQUENCY 100

void kmain(void) {
  init_vga(VGA_GREEN, VGA_BLACK);
  vga_clear();

  vga_puts("Kernel main routine entered.");
  vga_setpos(2, 0);

  vga_setcolor(VGA_LIGHT_GREY, VGA_BLACK);
  vga_puts("Initializing IDT and interrupt handling...\n");
  init_idt();

  vga_puts("Remapping hardware interrupts...\n");
  remap_pic();

  vga_puts("Initializing interrupt timer...\n");
  init_pit(PIT_FREQUENCY);

  sti();
  vga_puts("Hardware interrupts re-enabled.\n");

  vga_setcolor(VGA_GREEN, VGA_BLACK);
  vga_puts("IDT and interrupt handling successfully initialized.\n\n");

  vga_setcolor(VGA_LIGHT_GREY, VGA_BLACK);
  char buf[128];

  vga_setcolor(VGA_RED, VGA_BLACK);
  vga_puts("Uptime: ");
  for (;;) {
    char output_s_buf[128];
    char output_t_buf[128];

    char *output_s = itoa(pit_get_secs(), output_s_buf, 10);
    char *output_t = itoa(pit_get_ticks(), output_t_buf, 10);

    vga_printf("%s s (%s ticks @ %d Hz).", output_s, output_t, PIT_FREQUENCY);
    vga_setpos_rel(0, -18 - strlen(output_s) - strlen(output_t) -
                          strlen(itoa(PIT_FREQUENCY, buf, 10)));

    sleep_ms(1000);
  }
}
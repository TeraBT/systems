#include "idt.h"
#include "interrupt_definitions.h"
#include "kstdint.h"
#include "kutils.h"

struct idt_entry {
  uint16_t offset_low;
  uint16_t selector;
  uint8_t zero;
  uint8_t flags;
  uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

static struct idt_entry idt[256];
static struct idt_ptr idtp;

void remap_pic(void) {
  outb(PIC1_COMMAND, 0x11);
  outb(PIC2_COMMAND, 0x11);

  outb(PIC1_DATA, 0x20);
  outb(PIC2_DATA, 0x28);

  outb(PIC1_DATA, 0x04);
  outb(PIC2_DATA, 0x02);

  outb(PIC1_DATA, 0x01);
  outb(PIC2_DATA, 0x01);

  outb(PIC1_DATA, 0x00);
  outb(PIC2_DATA, 0x00);
}

void init_idt(void) {
  memset(idt, 0, sizeof(idt));

  for (size_t i = 0; i < 32; i++) {
    idt_set_gate(i, (uintptr_t)isr_table[i], 0x08, 0x8e);
  }

  for (size_t i = 0; i < 16; i++) {
    idt_set_gate(i + 32, (uintptr_t)irq_table[i], 0x08, 0x8e);
  }

  idt_set_gate(0x80, (uintptr_t)syscall_entry, 0x08, 0xee);

  idtp.limit = sizeof(idt) - 1;
  idtp.base = (uintptr_t)idt;

  __asm__ volatile("lidt %0" : : "m"(idtp));
}

void idt_set_gate(uint8_t i, uintptr_t handler, uint16_t selector,
                  uint8_t flags) {
  idt[i].offset_low = handler & 0xFFFF;
  idt[i].selector = selector;
  idt[i].zero = 0;
  idt[i].flags = flags;
  idt[i].offset_high = (handler >> 16) & 0xFFFF;
}

void common_interrupt_handler(struct interrupt_frame *frame) {

  switch (frame->int_no) {
  case 32:
    pit_increment();
    pic_write_eoi(32);
    return;
  }

  vga_setcolor(VGA_RED, VGA_BLACK);
  vga_printf("Interrupt No. %d ", frame->int_no);
  if (frame->int_no < 32) {
    vga_printf("(ISR %d)\n", frame->int_no);
    cli();
    hlt();
  } else if (frame->int_no < 48) {

    vga_printf("(IRQ %d)\n", frame->int_no - 32);
    pic_write_eoi(frame->int_no);

  } else {
    vga_printf("(Syscall %d)\n", frame->int_no - 48);
    cli();
    hlt();
  }
  vga_setcolor(VGA_RED, VGA_BLACK);
}
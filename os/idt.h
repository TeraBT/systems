#ifndef IDT_H
#define IDT_H

#include "kstddef.h"
#include "kstdint.h"

struct interrupt_frame {
  uint32_t int_no;
  uint32_t err_code;
};

void init_idt(void);
void idt_set_gate(uint8_t i, uintptr_t handler, uint16_t selector,
                  uint8_t flags);
void remap_pic(void);

void common_interrupt_handler(struct interrupt_frame *frame);

#endif
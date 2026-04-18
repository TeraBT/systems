#ifndef INTERRUPT_DEFINITIONS_H
#define INTERRUPT_DEFINITIONS_H

extern void isr0_entry(void);
extern void isr1_entry(void);
extern void isr2_entry(void);
extern void isr3_entry(void);
extern void isr4_entry(void);
extern void isr5_entry(void);
extern void isr6_entry(void);
extern void isr7_entry(void);
extern void isr8_entry(void);
extern void isr9_entry(void);
extern void isr10_entry(void);
extern void isr11_entry(void);
extern void isr12_entry(void);
extern void isr13_entry(void);
extern void isr14_entry(void);
extern void isr15_entry(void);
extern void isr16_entry(void);
extern void isr17_entry(void);
extern void isr18_entry(void);
extern void isr19_entry(void);
extern void isr20_entry(void);
extern void isr21_entry(void);
extern void isr22_entry(void);
extern void isr23_entry(void);
extern void isr24_entry(void);
extern void isr25_entry(void);
extern void isr26_entry(void);
extern void isr27_entry(void);
extern void isr28_entry(void);
extern void isr29_entry(void);
extern void isr30_entry(void);
extern void isr31_entry(void);

extern void irq0_entry(void);
extern void irq1_entry(void);
extern void irq2_entry(void);
extern void irq3_entry(void);
extern void irq4_entry(void);
extern void irq5_entry(void);
extern void irq6_entry(void);
extern void irq7_entry(void);
extern void irq8_entry(void);
extern void irq9_entry(void);
extern void irq10_entry(void);
extern void irq11_entry(void);
extern void irq12_entry(void);
extern void irq13_entry(void);
extern void irq14_entry(void);
extern void irq15_entry(void);

static void (*const isr_table[32])(void) = {
    isr0_entry,  isr1_entry,  isr2_entry,  isr3_entry,  isr4_entry,
    isr5_entry,  isr6_entry,  isr7_entry,  isr8_entry,  isr9_entry,
    isr10_entry, isr11_entry, isr12_entry, isr13_entry, isr14_entry,
    isr15_entry, isr16_entry, isr17_entry, isr18_entry, isr19_entry,
    isr20_entry, isr21_entry, isr22_entry, isr23_entry, isr24_entry,
    isr25_entry, isr26_entry, isr27_entry, isr28_entry, isr29_entry,
    isr30_entry, isr31_entry};

static void (*const irq_table[16])(void) = {
    irq0_entry,  irq1_entry,  irq2_entry,  irq3_entry, irq4_entry,  irq5_entry,
    irq6_entry,  irq7_entry,  irq8_entry,  irq9_entry, irq10_entry, irq11_entry,
    irq12_entry, irq13_entry, irq14_entry, irq15_entry};

extern void syscall_entry(void);

#endif
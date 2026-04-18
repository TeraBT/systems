ENTRY(kernel_entry)

PHDRS
{
  text PT_LOAD FLAGS(5);   /* R + X */
  data PT_LOAD FLAGS(6);   /* R + W */
}

SECTIONS
{
  . = 0x10000;

  .text : { *(.text*) } : text
  .rodata : { *(.rodata*) }
  .data : { *(.data*) } : data
  .bss : { *(.bss*) }
}
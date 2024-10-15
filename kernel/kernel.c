#include <kernel/idt.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <stdbool.h>

void kernel_main(void) {
  term_init();
  term_write_str("Hello from Magikaed-OS kernel!\n");

  term_write_str("Loading GDT...\n");

  gdt_init();

  term_write_str("GDT Loaded!\n");

  term_write_str("Loading IDT...\n");

  idt_init();

  term_write_str("IDT Loaded...\n");

  while (true);
}

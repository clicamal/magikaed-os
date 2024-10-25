#include <kernel/drivers/kbd.h>
#include <kernel/pic.h>
#include <kernel/idt.h>
#include <kernel/drivers/vga.h>
#include <kernel/gdt.h>
#include <stdbool.h>

void kernel_main(void) {
  vga_init();
  vga_write_str("Hello from Magikaed-OS kernel!\n");

  vga_write_str("Loading GDT...\n");

  gdt_init();

  vga_write_str("GDT Loaded!\n");

  vga_write_str("Loading IDT...\n");

  idt_init();

  vga_write_str("IDT Loaded...\n");

  vga_write_str("Initializing PIC...\n");

  pic_init();

  vga_write_str("PIC Initialized!\n");

  vga_write_str("Initializing Keyboard Driver...\n");

  kbd_init();

  vga_write_str("Keyboard Driver Initialized. You can start typing!\n");

  while (true) {
    char buffer[256];

    kbd_read(buffer, 256);

    vga_write_str(buffer);
  }
}

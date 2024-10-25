#include <stdio.h>
#include <kernel/drivers/kbd.h>
#include <kernel/pic.h>
#include <kernel/idt.h>
#include <kernel/drivers/vga.h>
#include <kernel/gdt.h>
#include <stdbool.h>

void kernel_main(void) {
  vga_init();
  printf("Hello from Magikaed-OS kernel!\n");

  printf("Loading GDT...\n");

  gdt_init();

  printf("GDT Loaded!\n");

  printf("Loading IDT...\n");

  idt_init();

  printf("IDT Loaded...\n");

  printf("Initializing PIC...\n");

  pic_init();

  printf("PIC Initialized!\n");

  printf("Initializing Keyboard Driver...\n");

  kbd_init();

  printf("Keyboard Driver Initialized. You can start typing!\n");

  printf("This is a test for printf! num = %d, -num = %d\n", 123, -123);

  while (true) {
    char buffer[256];

    kbd_read(buffer, 256);

    printf(buffer);
  }
}

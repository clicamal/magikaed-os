#include <kernel/drivers/ata.h>
#include <kernel/drivers/kbd.h>
#include <kernel/drivers/vga.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void
kernel_main(void)
{
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

  char ata_write_test[] = { "HELLO" };
  char ata_read_test[5];

  ata_write(0, (uint8_t*)ata_write_test, 1);
  ata_read(0, (uint8_t*)ata_read_test, 1);

  printf("This is a test for ata_write/ata_read: %s\n", ata_read_test);

  while (true) {
    char buffer[256];

    kbd_read(buffer, 256);

    printf(buffer);
  }
}

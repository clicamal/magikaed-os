#include <kernel/drivers/fat.h>
#include <kernel/drivers/kbd.h>
#include <kernel/drivers/vga.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

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

  struct fat_bootsector fat_boosector;
  char drive_label[6];

  fat_load_bootsector(&fat_boosector);

  memcpy(drive_label, fat_boosector.fat32_ext.vol_label, 4);

  drive_label[5] = '\0';

  printf("Using drive: %s\n", drive_label);

  while (true) {
    char buffer[256];

    kbd_read(buffer, 256);

    printf(buffer);
  }
}

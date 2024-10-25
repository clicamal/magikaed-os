#include <stdio.h>
#include <kernel/drivers/vga.h>

void putchar(char c) {
  vga_put_char(c);
}

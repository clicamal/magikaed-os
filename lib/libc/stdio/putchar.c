#include <kernel/drivers/vga.h>
#include <stdio.h>

void
putchar(char c)
{
  vga_put_char(c);
}

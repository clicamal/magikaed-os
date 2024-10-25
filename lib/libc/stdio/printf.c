#include <stdio.h>
#include <stdarg.h>
#include <kernel/drivers/vga.h>

void putint(int num) {
  if (num < 0) {
    putchar('-');

    num *= -1;
  }

  if (num / 10) putint(num / 10);

  putchar((num % 10) + '0');
}

void printf(const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);

  while (*fmt) {
    if (*fmt == '%') {
      fmt++;

      if (*fmt == 'd') {
        int num = va_arg(args, int);

        putint(num);
      }

      else if (*fmt == 's') {
        char *s = va_arg(args, char *);

        vga_write_str(s);
      }
    }

    else {
      putchar(*fmt);
    }

    fmt++;
  }

  va_end(args);
}

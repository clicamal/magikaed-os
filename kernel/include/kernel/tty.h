#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

void term_init(void);
void term_set_color(uint8_t color);
void term_put_entry_at(char c, uint8_t color, size_t x, size_t y);
void term_scroll_down(size_t n);
void term_put_char(char c);
void term_write(char *data, size_t size);
void term_write_str(char *data);

#endif


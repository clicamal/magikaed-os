#include <kernel/tty.h>
#include <kernel/drivers/vga.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t term_row;
size_t term_column;
uint8_t term_color;
uint16_t *term_buff;

void term_init(void) {
  term_row = 0;
  term_column = 0;
  term_color = create_vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
  term_buff = (uint16_t *) 0xB8000;

  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;

      term_buff[index] = create_vga_entry(' ', term_color);
    }
  }
}

void term_set_color(uint8_t color) { term_color = color; }

void term_put_entry_at(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;

  term_buff[index] = create_vga_entry(c, color);
}

void term_scroll_down(size_t n) {
  if (n >= VGA_HEIGHT) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
      for (size_t x = 0; x < VGA_WIDTH; x++) term_buff[y * VGA_WIDTH + x] = create_vga_entry(' ', term_color);
    }

    term_row = 0;
  } else {
    for (size_t y = n; y < VGA_HEIGHT; y++) {
      for (size_t x = 0; x < VGA_WIDTH; x++) term_buff[(y - n) * VGA_WIDTH + x] = term_buff[y * VGA_WIDTH + x];
    }

    for (size_t y = VGA_HEIGHT - n; y < VGA_HEIGHT; y++) {
      for (size_t x = 0; x < VGA_WIDTH; x++) term_buff[y * VGA_WIDTH + x] = create_vga_entry(' ', term_color);
    }

    term_row = VGA_HEIGHT - n;
  }
}

void term_put_char(char c) {
  if (c == '\n') {
    term_row++;
    term_column = 0;
  }

  else {
    term_put_entry_at(c, term_color, term_column, term_row);

    if (++term_column == VGA_WIDTH) {
      term_column = 0;

      if (++term_row == VGA_HEIGHT)
        term_row = 0;
    }
  }

  if (term_row == VGA_HEIGHT) term_scroll_down(1);
}

void term_write(char *data, size_t size) {
  for (size_t i = 0; i < size; i++) term_put_char(data[i]);
}

void term_write_str(char *data) { term_write(data, strlen(data)); }


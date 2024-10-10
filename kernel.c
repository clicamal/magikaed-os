#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15
};

static inline uint8_t create_vga_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

static inline uint16_t create_vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(char *str) {
  size_t len = 0;

  while (str[len]) len++;

  return len;
}

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

void term_put_char(char c) {
  term_put_entry_at(c, term_color, term_column, term_row);

  if (++term_column == VGA_WIDTH) {
    term_column = 0;

    if (++term_row == VGA_HEIGHT) term_row = 0;
  }
}

void term_write(char *data, size_t size) {
  for (size_t i = 0; i < size; i++) term_put_char(data[i]);
}

void term_write_str(char *data) { term_write(data, strlen(data)); }

void kernel_main(void) {
  term_init();
  term_write_str("Hello from Magikaed-OS kernel!");
}

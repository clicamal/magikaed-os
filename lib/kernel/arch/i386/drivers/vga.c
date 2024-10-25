#include <kernel/drivers/vga.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t vga_row;
size_t vga_column;
uint8_t vga_color;
uint16_t *vga_buff;

void vga_init(void) {
  vga_row = 0;
  vga_column = 0;
  vga_color = create_vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
  vga_buff = (uint16_t *) 0xB8000;

  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;

      vga_buff[index] = create_vga_entry(' ', vga_color);
    }
  }
}

void vga_set_color(uint8_t color) { vga_color = color; }

void vga_put_entry_at(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;

  vga_buff[index] = create_vga_entry(c, color);
}

void vga_scroll_down(size_t n) {
  if (n >= VGA_HEIGHT) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
      for (size_t x = 0; x < VGA_WIDTH; x++) vga_buff[y * VGA_WIDTH + x] = create_vga_entry(' ', vga_color);
    }

    vga_row = 0;
  } else {
    for (size_t y = n; y < VGA_HEIGHT; y++) {
      for (size_t x = 0; x < VGA_WIDTH; x++) vga_buff[(y - n) * VGA_WIDTH + x] = vga_buff[y * VGA_WIDTH + x];
    }

    for (size_t y = VGA_HEIGHT - n; y < VGA_HEIGHT; y++) {
      for (size_t x = 0; x < VGA_WIDTH; x++) vga_buff[y * VGA_WIDTH + x] = create_vga_entry(' ', vga_color);
    }

    vga_row = VGA_HEIGHT - n;
  }
}

void vga_put_char(char c) {
  if (c == '\t') {
    size_t new_column = vga_column + 4;

    if (vga_column >= VGA_WIDTH) vga_put_char('\n');
    else vga_column = new_column;
  }

  else if (c == '\n') {
    vga_row++;
    vga_column = 0;
  }

  else if (c == '\b') {
    vga_column--;

    vga_put_char(' ');

    vga_column--;
  }

  else {
    vga_put_entry_at(c, vga_color, vga_column, vga_row);

    if (++vga_column == VGA_WIDTH) {
      vga_column = 0;

      if (++vga_row == VGA_HEIGHT)
        vga_row = 0;
    }
  }

  if (vga_row == VGA_HEIGHT) vga_scroll_down(1);
}

void vga_write(char *data, size_t size) {
  for (size_t i = 0; i < size; i++) vga_put_char(data[i]);
}

void vga_write_str(char *data) { vga_write(data, strlen(data)); }


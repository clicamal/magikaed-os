#ifndef IO_H
#define IO_H

#include <stdint.h>

static inline uint8_t inb(uint16_t port) {
  uint8_t res;

  asm volatile ("inb %w1, %b0" : "=a" (res) : "Nd" (port) : "memory");

  return res;
}

static inline void outb(uint16_t port, uint8_t data) {
  asm volatile ("outb %b0, %w1" : : "a" (data), "Nd" (port) : "memory");
}

static inline void io_wait(void) {
  outb(0x80, 0);
}

#endif

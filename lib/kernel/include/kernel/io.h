#ifndef IO_H
#define IO_H

#include <stdint.h>

inline uint8_t
inb(uint16_t port)
{
  uint8_t res;

  asm volatile("inb %w1, %b0" : "=a"(res) : "Nd"(port) : "memory");

  return res;
}

inline void
outb(uint16_t port, uint8_t data)
{
  asm volatile("outb %b0, %w1" : : "a"(data), "Nd"(port) : "memory");
}

inline uint16_t
inw(uint16_t port)
{
  uint16_t res;

  asm volatile("inw %w1, %w0" : "=a"(res) : "Nd"(port) : "memory");

  return res;
}

inline void
outw(uint16_t port, uint16_t data)
{
  asm volatile("outw %w0, %w1" : : "a"(data), "Nd"(port) : "memory");
}

inline void
io_wait(void)
{
  outb(0x80, 0);
}

#endif

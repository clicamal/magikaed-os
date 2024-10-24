#include <kernel/io.h>
#include <kernel/pic.h>
#include <stdint.h>

#define PIC1_DATA (PIC1 + 1)

#define PIC2_DATA (PIC2 + 1)

#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10

#define ICW4_8086 0x01

void pic_init(void) {
  uint8_t a = inb(PIC1_DATA);
  uint8_t b = inb(PIC2_DATA);

  outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
  io_wait();

  outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);
  io_wait();

  outb(PIC1_DATA, 0x20);
  io_wait();

  outb(PIC2_CMD, 0x28);
  io_wait();

  outb(PIC1_DATA, 4);
  io_wait();

  outb(PIC2_DATA, 2);
  io_wait();

  outb(PIC1_DATA, ICW4_8086);
  io_wait();

  outb(PIC2_DATA, ICW4_8086);
  io_wait();

  outb(PIC1_DATA, a);
  outb(PIC2_DATA, b);
}

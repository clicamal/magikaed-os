#ifndef PIC_H
#define PIC_H

#include <kernel/io.h>
#include <stdint.h>

#define PIC1 0x20
#define PIC2 0xA0

#define PIC1_CMD PIC1
#define PIC2_CMD PIC2

#define PIC_EOI 0x20

static inline void pic_sendEOI(uint8_t irq) {
  if (irq >= PIC1 + 8) outb(PIC2_CMD, PIC_EOI);
  outb(PIC1_CMD, PIC_EOI);
}

void pic_init(void);

#endif

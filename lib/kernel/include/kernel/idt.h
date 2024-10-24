#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_entry {
  uint16_t offset_low;
  uint16_t seg_sel;
  uint8_t reserved;
  uint8_t type;
  uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
  uint16_t size;
  uint32_t offset;
} __attribute__((packed));

extern void idt_load(uint32_t);

void idt_set_entry(int index, uint32_t offset, uint16_t seg_sel, uint8_t type);

void idt_init(void);

#endif

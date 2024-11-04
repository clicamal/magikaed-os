#include <kernel/drivers/kbd.h>
#include <kernel/idt.h>
#include <kernel/int.h>
#include <stdint.h>

static struct idt_entry idt[256];
static struct idt_ptr idt_p;

void
idt_set_entry(int index, uint32_t offset, uint16_t seg_sel, uint8_t type)
{
  struct idt_entry* entry = &idt[index];

  entry->offset_low = offset & 0xFFFF;
  entry->offset_high = (offset >> 16) & 0xFFFF;

  entry->seg_sel = seg_sel;
  entry->reserved = 0;
  entry->type = type;
}

void
idt_init(void)
{
  idt_p.size = sizeof(idt) - 1;
  idt_p.offset = (uint32_t)&idt;

  for (int i = 0; i < 256; i++)
    idt_set_entry(i, (uint32_t)default_isr, 0x08, 0x8E);

  idt_set_entry(KBD_INT_I, (uint32_t)kbd_isr, 0x08, 0x8E);

  idt_load((uint32_t)&idt_p);
}

#include <kernel/gdt.h>
#include <stdint.h>

#define GDT_ENTRIES_COUNT 3

static struct gdt_entry gdt[GDT_ENTRIES_COUNT];
static struct gdt_ptr gdt_p;

void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
  struct gdt_entry *entry = &gdt[index];

  entry->base_low = (base & 0xFFFF);
  entry->base_mid = (base >> 16) & 0xFF;
  entry->base_high = (base >> 24) & 0xFF;

  entry->limit_low = (limit & 0xFFFF);
  entry->granularity = (limit >> 16) & 0x0F;

  entry->granularity |= granularity & 0xF0;
  entry->access = access;
}

void gdt_init(void) {
  gdt_p.limit = sizeof(gdt) - 1;
  gdt_p.base = (uint32_t) &gdt;

  gdt_set_entry(0, 0, 0, 0, 0);
  gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  gdt_load((uint32_t) &gdt_p);
}

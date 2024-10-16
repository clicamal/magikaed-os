#include <kernel/gdt.h>
#include <stdint.h>

#define GDT_ENTRIES_COUNT 3

static struct gdt_entry gdt[GDT_ENTRIES_COUNT];
static struct gdt_ptr gdt_p;

void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
  gdt[index].base_low = (base & 0xFFFF);
  gdt[index].base_mid = (base >> 16) & 0xFF;
  gdt[index].base_high = (base >> 24) & 0xFF;

  gdt[index].limit_low = (limit & 0xFFFF);
  gdt[index].granularity = (limit >> 16) & 0x0F;

  gdt[index].granularity |= granularity & 0xF0;
  gdt[index].access = access;
}

void gdt_init(void) {
  gdt_p.limit = (sizeof(struct gdt_entry) * GDT_ENTRIES_COUNT) - 1;
  gdt_p.base = (uint32_t) &gdt;

  gdt_set_entry(0, 0, 0, 0, 0);
  gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

  gdt_load((uint32_t) &gdt_p);
}

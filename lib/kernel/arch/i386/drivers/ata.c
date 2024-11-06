#include <kernel/drivers/ata.h>
#include <kernel/io.h>
#include <stdint.h>

void
ata_read(uint32_t lba, uint8_t nsectors, uint16_t* buffer)
{
  outb(0x1F6, ((lba >> 24) & 0x0F) | 0xE0);
  outb(0x1F2, nsectors);
  outb(0x1F3, lba & 0xFF);
  outb(0x1F4, (lba >> 8) & 0xFF);
  outb(0x1F5, (lba >> 16) & 0xFF);
  outb(0x1F7, 0x20);

  while (!(inb(0x1F7) & 0x08))
    ;

  uint32_t total_words = nsectors * 256;

  for (uint32_t i = 0; i < total_words; i++) {
    buffer[i] = inw(0x1F0);
  }
}

void
ata_lba_write(uint32_t lba, uint8_t nsectors, const uint16_t* buffer)
{
  outb(0x1F6, ((lba >> 24) & 0x0F) | 0xE0);
  outb(0x1F2, nsectors);
  outb(0x1F3, lba & 0xFF);
  outb(0x1F4, (lba >> 8) & 0xFF);
  outb(0x1F5, (lba >> 16) & 0xFF);
  outb(0x1F7, 0x30);

  while (!(inb(0x1F7) & 0x08))
    ;

  uint32_t total_words = nsectors * 256;

  for (uint32_t i = 0; i < total_words; i++) {
    outw(0x1F0, buffer[i]);
  }
}

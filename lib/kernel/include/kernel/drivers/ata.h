#ifndef ATA_H
#define ATA_H

#include <kernel/io.h>
#include <stdbool.h>
#include <stdint.h>

#define ATA_PRIM_IO 0x1F0
#define ATA_SECTOR_SIZE 512

inline bool
ata_ready(void)
{
  return (inb(ATA_PRIM_IO + 7) & 0x40);
}

inline bool
ata_busy(void)
{
  return (inb(ATA_PRIM_IO + 7) & 0x80);
}

inline void
ata_prepare(uint32_t lba, uint32_t nsectors)
{
  while (ata_busy())
    io_wait();

  io_wait();

  outb(ATA_PRIM_IO + 2, nsectors);
  io_wait();

  outb(ATA_PRIM_IO + 3, (uint8_t)lba);
  io_wait();

  outb(ATA_PRIM_IO + 4, (uint8_t)(lba >> 8));
  io_wait();

  outb(ATA_PRIM_IO + 5, (uint8_t)(lba >> 16));
  io_wait();

  outb(ATA_PRIM_IO + 6, 0xE0 | ((lba >> 24) & 0x0F));
  io_wait();
}

void
ata_read(uint32_t lba, uint8_t* buffer, uint32_t nsectors);
void
ata_write(uint32_t lba, uint8_t* buffer, uint32_t nsectors);

#endif

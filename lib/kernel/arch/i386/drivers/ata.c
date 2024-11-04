#include <kernel/io.h>
#include <kernel/drivers/ata.h>
#include <stdint.h>

void ata_read(uint32_t lba, uint8_t *buffer, uint32_t nsectors) {
  ata_prepare(lba, nsectors);

  outb(ATA_PRIM_IO + 7, 0x20);

  for (uint32_t sector = 0; sector < nsectors; sector++) {
    while (!ata_ready());

    for (int i = 0; i < ATA_SECTOR_SIZE / 2; i++) ((uint16_t *) buffer)[i] = inw(ATA_PRIM_IO);
  }

  buffer += ATA_SECTOR_SIZE;
}

void ata_write(uint32_t lba, uint8_t *buffer, uint32_t nsectors) {
  ata_prepare(lba, nsectors);

  outb(ATA_PRIM_IO + 7, 0x30);

  for (uint32_t sector = 0; sector < nsectors; sector++) {
    while (!ata_ready());

    for (int i = 0; i < ATA_SECTOR_SIZE / 2; i++) outw(ATA_PRIM_IO, ((uint16_t *) buffer)[i]);

    buffer += ATA_SECTOR_SIZE;
  }

  buffer += ATA_SECTOR_SIZE;
}

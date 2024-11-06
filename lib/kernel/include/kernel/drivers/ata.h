#ifndef ATA_H
#define ATA_H

#include <kernel/io.h>
#include <stdbool.h>
#include <stdint.h>

void
ata_read(uint32_t lba, uint8_t nsectors, uint16_t* buffer);
void
ata_lba_write(uint32_t lba, uint8_t nsectors, const uint16_t* buffer);
#endif

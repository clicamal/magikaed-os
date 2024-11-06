#include <kernel/drivers/ata.h>
#include <kernel/drivers/fat.h>
#include <stdint.h>

void
fat_load_bootsector(struct fat_bootsector* buffer)
{
  ata_read(0, (uint8_t*)buffer, 1);
}

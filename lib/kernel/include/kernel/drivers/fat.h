#ifndef FAT_H
#define FAT_H

#include <kernel/drivers/ata.h>
#include <stdint.h>

enum fat_entry_type
{
  READ_ONLY = 0x01,
  HIDDEN = 0x02,
  SYSTEM = 0x04,
  VOL_ID = 0x08,
  DIR = 0x10,
  ARCHIVE = 0x20,
  LFN = 0x0F
};

struct fat32_ext_bootrecord
{
  uint32_t nsectors_per_fat;
  uint16_t flags;
  uint16_t fat_version;
  uint32_t root_cluster;
  uint16_t fs_info_sector;
  uint16_t backup_bootsector_sector;
  uint8_t reserved[12];
  uint8_t drive_num;
  uint8_t res_nt;
  uint8_t boot_sig;
  uint32_t vol_ID;
  uint8_t vol_label[11];
  uint8_t sys_ID[8];
  uint8_t zero[420];
  uint16_t signature;
} __attribute__((packed));

struct fat32_fs_info
{
  uint32_t lead_sig;
  uint8_t not_usable[480];
  uint32_t second_sig;
  uint32_t free_cluster;
  uint32_t av_clusters_loc;
  uint8_t reserved[12];
  uint32_t trail_sig;
} __attribute__((packed));

struct fat_bootsector
{
  uint8_t jmp[3];
  uint8_t OEMid[8];
  uint16_t bytes_per_sector;
  uint8_t nsectors_per_cluster;
  uint16_t nres_sectors;
  uint8_t nfats;
  uint16_t nroot_dir_entries;
  uint16_t total_sectors;
  uint8_t type;
  uint16_t nsectors_per_fat;
  uint16_t nsectors_per_track;
  uint16_t nheads;
  uint32_t nhidden_sectors;
  uint32_t nlarge_sector;
  uint8_t ext[476];
} __attribute__((packed));

struct fat_entry
{
  uint8_t name[11];
  uint8_t type;
  uint8_t reserved;
  uint8_t crt_time_hsecs;
  uint16_t crt_time;
  uint16_t crt_date;
  uint16_t last_acc_date;
  uint16_t fcluster_high;
  uint16_t last_mod_time;
  uint16_t last_mod_date;
  uint16_t lcluster_low;
  uint32_t size;
} __attribute__((packed));

typedef uint8_t fat[ATA_SECTOR_SIZE];

void
fat_load_bootsector(struct fat_bootsector* buffer);
void
fat_load(struct fat_bootsector bootsector, fat buffer);

#endif

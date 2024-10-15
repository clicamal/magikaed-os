HOST_ARCH = i386

AS = $(HOST_ARCH)-elf-as
CC = $(HOST_ARCH)-elf-gcc

KERNEL_SRC_ROOT = kernel

BOOT_SRC = boot.s
KERNEL_SRC = $(KERNEL_SRC_ROOT)/kernel.c

BOOT_OBJ = $(BOOT_SRC:%.s=%.o)
KERNEL_OBJ = $(KERNEL_SRC:%.c=%.o)

LIBK_SRC_ROOT = kernel/arch/$(HOST_ARCH)
LIBC_SRC_ROOT = libc

CFLAGS = -I$(KERNEL_SRC_ROOT)/include -I$(LIBC_SRC_ROOT)/include -ffreestanding -std=gnu99 -O2 -Wall -Wextra

LIBK_SRC = $(wildcard $(LIBK_SRC_ROOT)/*.c)
LIBK_AS_SRC = $(wildcard $(LIBK_SRC_ROOT)/as/*.s)
LIBK_OBJ = $(LIBK_SRC:%.c=%.o)
LIBK_AS_OBJ = $(LIBK_AS_SRC:%.s=%.o)

LIBC_SRC = $(wildcard $(LIBC_SRC_ROOT)/string/*.c)
LIBC_OBJ = $(LIBC_SRC:%.c=%.o)

SYSROOT = sysroot
INCLUDE_DIR = $(SYSROOT)/usr/local/include

OS_BIN = magikaed-os.bin

assemble:
	$(AS) $(BOOT_SRC) -o $(BOOT_OBJ)
	$(foreach file, $(LIBK_AS_SRC), $(AS) $(file) -o $(file:%.s=%.o);)

compile-libk:
	$(foreach file, $(LIBK_SRC), $(CC) -c $(file) -o $(file:%.c=%.o) $(CFLAGS);)

compile-libc:
	$(foreach file, $(LIBC_SRC), $(CC) -c $(file) -o $(file:%.c=%.o) $(CFLAGS);)

compile-kernel: compile-libc compile-libk
	$(CC) -c $(KERNEL_SRC) -o $(KERNEL_OBJ) $(CFLAGS)

gen-bin: assemble compile-kernel
	$(CC) -T linker.ld $(BOOT_OBJ) $(KERNEL_OBJ) $(LIBK_OBJ) $(LIBK_AS_OBJ) $(LIBC_OBJ) -o $(OS_BIN) -nostdlib -lgcc

install-libs:
	mkdir -p $(INCLUDE_DIR)
	cp -r $(LIBK_SRC_ROOT)/../../include/kernel $(INCLUDE_DIR)
	cp -r $(LIBC_SRC_ROOT)/include/* $(INCLUDE_DIR)

emulate: gen-bin
	qemu-system-i386 -kernel $(OS_BIN)

clean:
	rm $(BOOT_OBJ) $(KERNEL_OBJ) $(LIBK_OBJ) $(LIBK_AS_OBJ) $(LIBC_OBJ) $(OS_BIN)

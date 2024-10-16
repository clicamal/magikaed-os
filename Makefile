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

BIN_DEPS = $(BOOT_OBJ) $(LIBK_AS_OBJ) $(LIBK_OBJ) $(LIBC_OBJ) $(KERNEL_OBJ)

$(BOOT_OBJ):
	$(AS) $(BOOT_SRC) -o $(BOOT_OBJ)

$(LIBK_AS_OBJ):
	$(foreach file, $(LIBK_AS_SRC), $(AS) $(file) -o $(file:%.s=%.o);)

$(LIBK_OBJ):
	$(foreach file, $(LIBK_SRC), $(CC) -c $(file) -o $(file:%.c=%.o) $(CFLAGS);)

$(LIBC_OBJ):
	$(foreach file, $(LIBC_SRC), $(CC) -c $(file) -o $(file:%.c=%.o) $(CFLAGS);)

$(KERNEL_OBJ): $(LIBC_OBJ) $(LIBK_OBJ)
	$(CC) -c $(KERNEL_SRC) -o $@ $(CFLAGS)

gen-bin: $(BIN_DEPS)
	$(CC) -T linker.ld $^ -o $(OS_BIN) -nostdlib -lgcc

emulate: gen-bin
	qemu-system-i386 -kernel $(OS_BIN)

install-libs:
	mkdir -p $(INCLUDE_DIR)
	cp -r $(LIBK_SRC_ROOT)/../../include/kernel $(INCLUDE_DIR)
	cp -r $(LIBC_SRC_ROOT)/include/* $(INCLUDE_DIR)

clean:
	rm $(BIN_DEPS) $(OS_BIN)

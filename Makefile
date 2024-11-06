HOST_ARCH = i386

AS = $(HOST_ARCH)-elf-as
CC = $(HOST_ARCH)-elf-gcc

LIBK_SRC_ROOT = ./lib/kernel/arch/$(HOST_ARCH)
LIBC_SRC_ROOT = ./lib/libc

CFLAGS = -I$(LIBK_SRC_ROOT)/../../include -I$(LIBC_SRC_ROOT)/include -ffreestanding -std=gnu99 -O2 -Wall -Wextra

SRC = $(shell find . -name "*.c")
HEADERS = $(shell find . -name "*.h")
AS_SRC = $(shell find . -name "*.s")
OBJ = $(AS_SRC:%.s=%.o) $(SRC:%.c=%.o)

OS_BIN = magikaed-os.bin
OS_MEM_SIZE = 4G

DISK_IMG = disk.img
DISK_SIZE = 4G

$(OBJ):
	$(foreach as_file, $(AS_SRC), $(AS) $(as_file) -o $(as_file:%.s=%.o);)
	$(foreach c_file, $(SRC), $(CC) $(CFLAGS) -c $(c_file) -o $(c_file:%.c=%.o);)

$(DISK_IMG):
	qemu-img create -f raw $(DISK_IMG) $(DISK_SIZE)
	sudo mkfs.fat -F 32 -n "MAGIKAED" -v $(DISK_IMG)

$(OS_BIN): $(OBJ)
	$(CC) -T linker.ld $(OBJ) -o $@ -nostdlib -lgcc

emulate: $(OS_BIN) $(DISK_IMG)
	qemu-system-i386 -kernel $(OS_BIN) -drive file=$(DISK_IMG),format=raw -m $(OS_MEM_SIZE)

clean:
	@rm -f $(OBJ) $(OS_BIN)

lint:
	@echo $(SRC) $(HEADERS) | xargs clang-format -style=mozilla -i

test:
	@xargs

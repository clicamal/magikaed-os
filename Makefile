HOST_ARCH = i386

AS = $(HOST_ARCH)-elf-as
CC = $(HOST_ARCH)-elf-gcc

LIBK_SRC_ROOT = ./lib/kernel/arch/$(HOST_ARCH)
LIBC_SRC_ROOT = ./lib/libc

CFLAGS = -I$(LIBK_SRC_ROOT)/../../include -I$(LIBC_SRC_ROOT)/include -ffreestanding -std=gnu99 -O2 -Wall -Wextra

SRC = $(shell find . -name "*.c")
AS_SRC = $(shell find . -name "*.s")
OBJ = $(AS_SRC:%.s=%.o) $(SRC:%.c=%.o)

OS_BIN = magikaed-os.bin

$(OBJ):
	$(foreach as_file, $(AS_SRC), $(AS) $(as_file) -o $(as_file:%.s=%.o);)
	$(foreach c_file, $(SRC), $(CC) $(CFLAGS) -c $(c_file) -o $(c_file:%.c=%.o);)

gen-bin: $(OBJ)
	$(CC) -T linker.ld $(OBJ) -o $(OS_BIN) -nostdlib -lgcc

emulate: gen-bin
	qemu-system-i386 -kernel $(OS_BIN)

clean:
	@rm -f $(OBJ) $(OS_BIN)

test:
	@echo $(SRC)

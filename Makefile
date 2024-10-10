AS = i386-elf-as
CC = i386-elf-gcc

BOOT_SRC = boot.s
KERNEL_SRC = kernel.c

BOOT_OBJ = $(BOOT_SRC:%.s=%.o)
KERNEL_OBJ = $(KERNEL_SRC:%.c=%.o)

OS_BIN = magikaed-os.bin

assemble:
	$(AS) $(BOOT_SRC) -o $(BOOT_OBJ)

compile:
	$(CC) -c $(KERNEL_SRC) -o $(KERNEL_OBJ) -std=gnu99 -ffreestanding -O2 -Wall -Wextra

gen-bin: assemble compile
	$(CC) -T linker.ld -o $(OS_BIN) -ffreestanding -O2 -nostdlib $(BOOT_OBJ) $(KERNEL_OBJ) -lgcc

emulate: gen-bin
	qemu-system-i386 -kernel $(OS_BIN)

clean:
	rm $(BOOT_OBJ) $(KERNEL_OBJ) $(OS_BIN)

.global gdt_load

gdt_load:
  cli

  movl 4(%esp), %edx

  lgdt (%edx)

  jmp $0x08, $reload_seg_regs

reload_seg_regs:
  movw $0x10, %ax
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs
  movw %ax, %ss

  ret

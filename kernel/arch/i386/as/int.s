.global default_isr
.global kbd_isr

default_isr:
  pusha

  cld

  call default_int

  popa

  iret

kbd_isr:
  pusha

  cld

  call kbd_int

  popa

  iret

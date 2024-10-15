.global default_isr

default_isr:
  pusha

  cld

  call default_int

  popa

  iret

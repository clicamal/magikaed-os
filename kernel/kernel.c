#include <kernel/tty.h>

void kernel_main(void) {
  term_init();
  term_write_str("Hello from Magikaed-OS kernel!\n");
  term_write_str("I'm alive!\n");
}

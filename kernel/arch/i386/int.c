#include "kernel/tty.h"
#include <kernel/int.h>

void default_int(void) {
  term_write_str("An interrupt occured!\n");
}